/*
 * function_register.c
 *
 *  Created on: Jul 18, 2025
 *      Author: Jarvis
 */
#include "function_register.h"

#include <string.h>
#include <stdio.h>
#define MAX_FUNC_COUNT 32

static func_entry_t func_table[MAX_FUNC_COUNT];
static int func_count = 0;

void shell_register_function(const char *name, shell_func_t func) {
    if (func_count < MAX_FUNC_COUNT) {
        func_table[func_count++] = (func_entry_t){name, func};
    }
}

int shell_run_function(const char *name, int argc, char **argv) {
    for (int i = 0; i < func_count; i++) {
        if (strcmp(func_table[i].name, name) == 0) {
            return func_table[i].func(argc, argv);
        }
    }
    return -1;
}

void shell_func_list(void) {
    printf("Registered functions:\n");
    for (int i = 0; i < func_count; i++) {
        printf(" - %s\n", func_table[i].name);
    }
}

