/*
 * function_register.c
 *
 *  Created on: Jul 18, 2025
 *      Author: Jarvis
 */
#include "function_register.h"

#include <string.h>
#include <stdio.h>

extern const func_entry_t __start_func_table[];
extern const func_entry_t __stop_func_table[];

int func_registry_run(int argc, char **argv)
{
    if (argc < 1) {
        printf("No function name provided\n");
        return -1;
    }
    const char *func_name = argv[0];
    const func_entry_t *p = __start_func_table;
    while (p < __stop_func_table) {
        if (strcmp(p->name, func_name) == 0) {
            return p->func(argc, argv);
        }
        p++;
    }
    printf("Function not found: %s\n", func_name);
    return -1;
}

void func_registry_list(void)
{
    printf("Available functions:\n");
    const func_entry_t *p = __start_func_table;
    while (p < __stop_func_table) {
        printf("  %s\n", p->name);
        p++;
    }
}
