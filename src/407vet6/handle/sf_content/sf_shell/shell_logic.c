/*
 * shell_logic.c
 *
 *  Created on: Jul 18, 2025
 *      Author: Jarvis
 */
#include <string.h>
#include <stdio.h>
#include "shell_logic.h"
#include "var_register.h"
#include "function_register.h"
#include "sf_log.h"
#define MAX_ARGC 8
#define MAX_LINE_LEN 128

void shell_exec(const char *line) {
    char buffer[MAX_LINE_LEN];
    strncpy(buffer, line, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = 0;

    char *argv[MAX_ARGC] = {0};
    int argc = 0;

    char *token = strtok(buffer, " ");
    while (token && argc < MAX_ARGC) {
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }

    if (argc == 0) return;

    if (strcmp(argv[0], "get") == 0 && argc == 2) {
        char output[64];
        if (shell_get_variable(argv[1], output, sizeof(output)) == 0) {
            log_shell_send("%s = %s\n", argv[1], output);
        } else {
            log_shell_send("Variable '%s' not found\n", argv[1]);
        }
    } else if (strcmp(argv[0], "set") == 0 && argc == 3) {
        if (shell_set_variable(argv[1], argv[2]) == 0) {
            log_shell_send("Set %s = %s\n", argv[1], argv[2]);
        } else {
            log_shell_send("Set failed: variable '%s' not found\n", argv[1]);
        }
    } else if (strcmp(argv[0], "run") == 0 && argc >= 2) {
        if (shell_run_function(argv[1], argc - 2, &argv[2]) != 0) {
            log_shell_send("Function '%s' failed or not found\n", argv[1]);
        }
    }
    else if (strcmp(argv[0], "varlist") == 0) {
        shell_var_list();
    } else if (strcmp(argv[0], "funclist") == 0) {
        shell_func_list();
    }

    else {
        log_shell_send("Unknown command: %s\n", argv[0]);
    }
}

