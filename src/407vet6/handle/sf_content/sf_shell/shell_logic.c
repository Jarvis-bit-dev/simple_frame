/*
 * shell_logic.c
 *
 *  Created on: Jul 18, 2025
 *      Author: Jarvis
 */
#include <string.h>
#include <stdio.h>
#include "var_register.h"
#include "function_register.h"


#define CMD_MAX_ARGS 4

static void trim_whitespace(char *str) {
    char *end;
    while (*str == ' ') str++;
    end = str + strlen(str) - 1;
    while (end > str && (*end == '\r' || *end == '\n' || *end == ' ')) *end-- = '\0';
}
void shell_process_input(const char *input) {
    char buffer[128];
    strncpy(buffer, input, sizeof(buffer));
    buffer[sizeof(buffer)-1] = '\0';
    trim_whitespace(buffer);

    char *argv[CMD_MAX_ARGS] = {0};
    int argc = 0;

    char *token = strtok(buffer, " ");
    while (token && argc < CMD_MAX_ARGS) {
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }

    if (argc == 0) return;

    if (strcmp(argv[0], "get") == 0 && argc == 2) {
    	shell_handle_get_command(argv[1]);
    } else if (strcmp(argv[0], "set") == 0 && argc == 3) {
    } else if (strcmp(argv[0], "list") == 0) {
    } else {
        printf("Unknown command or wrong args\n");
    }
}
