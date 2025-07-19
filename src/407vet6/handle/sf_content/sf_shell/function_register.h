/*
 * function_register.h
 *
 *  Created on: Jul 18, 2025
 *      Author: Jarvis
 */

#ifndef SF_CONTENT_SF_SHELL_FUNCTION_REGISTER_H_
#define SF_CONTENT_SF_SHELL_FUNCTION_REGISTER_H_


typedef int (*shell_func_t)(int argc, char **argv);

typedef struct {
    const char *name;
    shell_func_t func;
} func_entry_t;

void shell_register_function(const char *name, shell_func_t func);
int shell_run_function(const char *name, int argc, char **argv);
void shell_func_list(void);

// 宏注册函数
#define SHELL_FUNC_REGISTER(func) \
    shell_register_function(#func, func)


#endif /* SF_CONTENT_SF_SHELL_FUNCTION_REGISTER_H_ */
