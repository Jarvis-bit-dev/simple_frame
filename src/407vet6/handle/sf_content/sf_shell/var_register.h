/*
 * var_register.h
 *
 *  Created on: Jul 18, 2025
 *      Author: Jarvis
 */

#ifndef SF_CONTENT_SF_SHELL_VAR_REGISTER_H_
#define SF_CONTENT_SF_SHELL_VAR_REGISTER_H_

#include <stdint.h>

// 支持的变量类型
typedef enum {
    VAR_TYPE_INT,
    VAR_TYPE_FLOAT,
    VAR_TYPE_BOOL,
    VAR_TYPE_UNKNOWN
} var_type_t;

// 变量信息结构体
typedef struct {
    const char *name;
    void *addr;
    var_type_t type;
} var_entry_t;

#define MAX_VAR_NUM 64

// 注册接口（内部使用宏包装）
int shell_register_var(const char *name, void *addr, var_type_t type);

// 变量操作接口
void shell_set_var(const char *name, const char *value);
void shell_get_var(const char *name);
void shell_list_vars(void);

// 注册宏定义（简化调用）
#define REGISTER_VAR(var, type_enum) \
    shell_register_var(#var, (void *)&var, type_enum)



#endif /* SF_CONTENT_SF_SHELL_VAR_REGISTER_H_ */
