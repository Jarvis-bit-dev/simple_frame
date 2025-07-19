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

static var_entry_t var_table[MAX_VAR_NUM];
static int var_count = 0;

int shell_register_var(const char *name, void *addr, var_type_t type) {
    if (var_count >= MAX_VAR_NUM) return -1;
    var_table[var_count++] = (var_entry_t){ name, addr, type };
    return 0;
}

static var_entry_t *find_var(const char *name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(var_table[i].name, name) == 0) {
            return &var_table[i];
        }
    }
    return NULL;
}

void shell_set_var(const char *name, const char *value) {
    var_entry_t *entry = find_var(name);
    if (!entry) {
        printf("Variable '%s' not found\n", name);
        return;
    }

    switch (entry->type) {
        case VAR_TYPE_INT:
            *(int *)entry->addr = atoi(value);
            break;
        case VAR_TYPE_FLOAT:
            *(float *)entry->addr = strtof(value, NULL);
            break;
        case VAR_TYPE_BOOL:
            *(int *)entry->addr = (strcmp(value, "true") == 0 || strcmp(value, "1") == 0) ? 1 : 0;
            break;
        default:
            printf("Unsupported type\n");
            return;
    }

    printf("Set %s = %s\n", name, value);
}

void shell_get_var(const char *name) {
    var_entry_t *entry = find_var(name);
    if (!entry) {
        printf("Variable '%s' not found\n", name);
        return;
    }

    printf("%s = ", name);
    switch (entry->type) {
        case VAR_TYPE_INT:
            printf("%d\n", *(int *)entry->addr);
            break;
        case VAR_TYPE_FLOAT:
            printf("%.3f\n", *(float *)entry->addr);
            break;
        case VAR_TYPE_BOOL:
            printf("%s\n", *(int *)entry->addr ? "true" : "false");
            break;
        default:
            printf("Unsupported type\n");
            break;
    }
}

void shell_list_vars(void) {
    printf("Registered variables:\n");
    for (int i = 0; i < var_count; i++) {
        printf("  %s\n", var_table[i].name);
    }
}
