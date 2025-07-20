/*
 * var_register.c
 *
 *  Created on: Jul 18, 2025
 *      Author: Jarvis
 */
#include "var_register.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "sf_log.h"
#define MAX_VAR_COUNT 64

static var_entry_t var_table[MAX_VAR_COUNT];
static int var_count = 0;

void shell_register_variable(const char *name, void *addr, var_type_t type) {
	if (var_count < MAX_VAR_COUNT) {
		var_table[var_count++] = (var_entry_t )
				{ name, addr, type, 0, 0, 0 };
	}
}

// 数组变量注册
void shell_register_array(const char *name, void *addr, var_type_t elem_type,
		int elem_size, int elem_count) {
	if (var_count < MAX_VAR_COUNT) {
		var_table[var_count++] =
				(var_entry_t )
						{ name, addr, VAR_TYPE_ARRAY, elem_type, elem_size,
								elem_count };
	}
}

static var_entry_t*
find_var(const char *name) {
	for (int i = 0; i < var_count; i++) {
		if (strcmp(var_table[i].name, name) == 0) {
			return &var_table[i];
		}
	}
	return NULL;
}

static int parse_array(const char *name, char *base, int *idx) {
	const char *lb = strchr(name, '[');
	const char *rb = strchr(name, ']');
	if (!lb || !rb || lb > rb)
		return 0;
	int nlen = lb - name;
	strncpy(base, name, nlen);
	base[nlen] = 0;
	*idx = atoi(lb + 1);
	return 1;
}

int shell_get_variable(const char *name, char *output, int max_len) {
	char base[32];
	int idx;
	if (parse_array(name, base, &idx)) { // arr[3] 形式
		var_entry_t *var = find_var(base);
		if (!var || var->type != VAR_TYPE_ARRAY)
			return -1;
		if (idx < 0 || idx >= var->elem_count)
			return -2;
		uint8_t *elem_addr = (uint8_t*) var->addr + idx * var->elem_size;
		switch (var->elem_type) {
		case VAR_TYPE_INT:
			snprintf(output, max_len, "%d", *(int*) elem_addr);
			break;
		case VAR_TYPE_FLOAT:
			snprintf(output, max_len, "%f", *(float*) elem_addr);
			break;
		case VAR_TYPE_STRING:
			snprintf(output, max_len, "%s", (char*) elem_addr);
			break;
		case VAR_TYPE_BOOL:
			snprintf(output, max_len, "%s",
					(*(int*) elem_addr) ? "true" : "false");
			break;
		default:
			return -3;
		}
		return 0;
	} else { // 标量
		var_entry_t *var = find_var(name);
		if (!var)
			return -1;
		switch (var->type) {
		case VAR_TYPE_INT:
			snprintf(output, max_len, "%d", *(int*) var->addr);
			break;
		case VAR_TYPE_FLOAT:
			snprintf(output, max_len, "%f", *(float*) var->addr);
			break;
		case VAR_TYPE_STRING:
			snprintf(output, max_len, "%s", (char*) var->addr);
			break;
		case VAR_TYPE_BOOL:
			snprintf(output, max_len, "%s",
					(*(int*) var->addr) ? "true" : "false");
			break;
		default:
			return -3;
		}
		return 0;
	}
}

int shell_set_variable(const char *name, const char *value_str) {
	char base[32];
	int idx;
	if (parse_array(name, base, &idx)) {
		var_entry_t *var = find_var(base);
		if (!var || var->type != VAR_TYPE_ARRAY)
			return -1;
		if (idx < 0 || idx >= var->elem_count)
			return -2;
		uint8_t *elem_addr = (uint8_t*) var->addr + idx * var->elem_size;
		switch (var->elem_type) {
		case VAR_TYPE_INT:
			*(int*) elem_addr = atoi(value_str);
			break;
		case VAR_TYPE_FLOAT:
			*(float*) elem_addr = atof(value_str);
			break;
		case VAR_TYPE_STRING:
			strncpy((char*) elem_addr, value_str, var->elem_size - 1);
			((char*) elem_addr)[var->elem_size - 1] = 0;
			break;
		case VAR_TYPE_BOOL:
			*(int*) elem_addr = (strcmp(value_str, "true") == 0);
			break;
		default:
			return -3;
		}
		return 0;
	} else {
		var_entry_t *var = find_var(name);
		if (!var)
			return -1;
		switch (var->type) {
		case VAR_TYPE_INT:
			*(int*) var->addr = atoi(value_str);
			break;
		case VAR_TYPE_FLOAT:
			*(float*) var->addr = atof(value_str);
			break;
		case VAR_TYPE_STRING:
			strncpy((char*) var->addr, value_str, strlen(value_str) + 1);
			break;
		case VAR_TYPE_BOOL:
			*(int*) var->addr = (strcmp(value_str, "true") == 0);
			break;
		default:
			return -3;
		}
		return 0;
	}
}
void shell_var_list(void) {
	LOG_INFO("Registered variables:\n");
	for (int i = 0; i < var_count; i++) {
		if (var_table[i].type == VAR_TYPE_ARRAY)
			LOG_INFO(" - %s[%d]\n", var_table[i].name, var_table[i].elem_count);
		else
			LOG_INFO(" - %s\n", var_table[i].name);
	}
}
