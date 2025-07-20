/*
 * sf_err.h
 *
 *  Created on: Jul 20, 2025
 *      Author: Jarvis
 */

#ifndef SF_CONTENT_SF_ERR_SF_ERR_H_
#define SF_CONTENT_SF_ERR_SF_ERR_H_


#include <stdint.h>

typedef enum {
    ERROR_LEVEL_WARNING,
    ERROR_LEVEL_ERROR,
} error_level_t;

typedef int (*error_check_fn)(void *arg);
typedef void (*error_action_fn)(void *arg);

int error_register(const char *name, error_level_t level,
                  error_check_fn check,
                  error_action_fn action,
                  error_action_fn recover, // 增加恢复动作
                  void *arg, uint16_t threshold);

void error_poll(void);
int error_query(const char *name, error_level_t *level, uint8_t *active);
void error_list_print(void);



#endif /* SF_CONTENT_SF_ERR_SF_ERR_H_ */
