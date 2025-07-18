/*
 * function_register.h
 *
 *  Created on: Jul 18, 2025
 *      Author: Jarvis
 */

#ifndef SF_CONTENT_SF_SHELL_FUNCTION_REGISTER_H_
#define SF_CONTENT_SF_SHELL_FUNCTION_REGISTER_H_

typedef int (*func_with_args_t)(int argc, char **argv);

typedef struct {
    const char *name;
    func_with_args_t func;
} func_entry_t;

#define FUNC_REG_SECTION  __attribute__((section(".func_table")))

#define FUNC_REGISTER(name) \
    static const func_entry_t FUNC_REG_SECTION __func_entry_##name = { #name, name };

int func_registry_run(int argc, char **argv);
void func_registry_list(void);



#endif /* SF_CONTENT_SF_SHELL_FUNCTION_REGISTER_H_ */
