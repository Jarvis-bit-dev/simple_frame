/*
 * var_register.h
 *
 *  Created on: Jul 18, 2025
 *      Author: Jarvis
 */

#ifndef SF_CONTENT_SF_SHELL_VAR_REGISTER_H_
#define SF_CONTENT_SF_SHELL_VAR_REGISTER_H_


#include <stdint.h>

#define MAX_VAR_ENTRIES 64

typedef enum {
    VAR_TYPE_INT,
    VAR_TYPE_UINT,
    VAR_TYPE_FLOAT,
} var_type_t;

typedef struct {
    const char *name;
    void *addr;
    var_type_t type;
} var_entry_t;





// 注册变量
int register_var(const char *name, void *addr, var_type_t type);

// 注册宏
#define VAR_REGISTER(var_name, type_enum) \
    register_var(#var_name, &var_name, type_enum)

// shell解析函数
void shell_handle_set_command(const char *input);  // 示例：set var1 123
void shell_handle_get_command(const char *input);  // 示例：get var1


#endif /* SF_CONTENT_SF_SHELL_VAR_REGISTER_H_ */
