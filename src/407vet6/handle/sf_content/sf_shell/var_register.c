/*
 * var_register.c
 *
 *  Created on: Jul 18, 2025
 *      Author: Jarvis
 */
#include "var_register.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
static var_entry_t var_table[MAX_VAR_ENTRIES];
static int var_table_count = 0;

int register_var(const char *name, void *addr, var_type_t type) {
    if (var_table_count >= MAX_VAR_ENTRIES) return -1;

    var_table[var_table_count++] = (var_entry_t){
        .name = name,
        .addr = addr,
        .type = type
    };
    return 0;
}

static var_entry_t *find_var(const char *name) {
    for (int i = 0; i < var_table_count; ++i) {
        if (strcmp(var_table[i].name, name) == 0) {
            return &var_table[i];
        }
    }
    return NULL;
}

void shell_handle_get_command(const char *input) {
    char var_name[64];
    if (sscanf(input, "get %63s", var_name) != 1) {
        printf("Usage: get var_name\n");
        return;
    }

    var_entry_t *var = find_var(var_name);
    if (!var) {
        printf("Variable '%s' not found\n", var_name);
        return;
    }

    switch (var->type) {
        case VAR_TYPE_INT:
            printf("%s = %d\n", var->name, *(int *)var->addr);
            break;
        case VAR_TYPE_FLOAT:
            printf("%s = %f\n", var->name, *(float *)var->addr);
            break;
        default:
            printf("Unknown type\n");
            break;
    }
}

void shell_handle_set_command(const char *input) {
    char var_name[64], value_str[64];
    if (sscanf(input, "set %63s %63s", var_name, value_str) != 2) {
        printf("Usage: set var_name value\n");
        return;
    }

    var_entry_t *var = find_var(var_name);
    if (!var) {
        printf("Variable '%s' not found\n", var_name);
        return;
    }

    switch (var->type) {
        case VAR_TYPE_INT:
            *(int *)var->addr = atoi(value_str);
            printf("%s set to %d\n", var->name, *(int *)var->addr);
            break;
        case VAR_TYPE_FLOAT:
            *(float *)var->addr = atof(value_str);
            printf("%s set to %f\n", var->name, *(float *)var->addr);
            break;

        default:
            printf("Unknown type\n");
            break;
    }
}
