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
#define MAX_VAR_COUNT 64

static var_entry_t var_table[MAX_VAR_COUNT];
static int var_count = 0;

void shell_register_variable(const char *name, void *addr, var_type_t type) {
    if (var_count < MAX_VAR_COUNT) {
        var_table[var_count++] = (var_entry_t){name, addr, type};
    }
}

static var_entry_t *find_var(const char *name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(var_table[i].name, name) == 0) {
            return &var_table[i];
        }
    }
    return NULL;
}

int shell_get_variable(const char *name, char *output, int max_len) {
    var_entry_t *var = find_var(name);
    if (!var) return -1;

    switch (var->type) {
        case VAR_TYPE_INT:
            snprintf(output, max_len, "%d", *(int *)var->addr); break;
        case VAR_TYPE_FLOAT:
            snprintf(output, max_len, "%f", *(float *)var->addr); break;
        case VAR_TYPE_STRING:
            snprintf(output, max_len, "%s", (char *)var->addr); break;
        case VAR_TYPE_BOOL:
            snprintf(output, max_len, "%s", *(int *)var->addr ? "true" : "false"); break;
        default:
            return -2;
    }
    return 0;
}

int shell_set_variable(const char *name, const char *value_str) {
    var_entry_t *var = find_var(name);
    if (!var) return -1;

    switch (var->type) {
        case VAR_TYPE_INT:
            *(int *)var->addr = atoi(value_str); break;
        case VAR_TYPE_FLOAT:
            *(float *)var->addr = atof(value_str); break;
        case VAR_TYPE_STRING:
            strncpy((char *)var->addr, value_str, strlen(value_str)+1); break;
        case VAR_TYPE_BOOL:
            *(int *)var->addr = (strcmp(value_str, "true") == 0); break;
        default:
            return -2;
    }
    return 0;
}
void shell_var_list(void) {
    printf("Registered variables:\n");
    for (int i = 0; i < var_count; i++) {
        printf(" - %s\n", var_table[i].name);
    }
}
