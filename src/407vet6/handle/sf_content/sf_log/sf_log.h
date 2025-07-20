/*
 * sf_log.h
 *
 *  Created on: Jul 20, 2025
 *      Author: Jarvis
 */

#ifndef SF_CONTENT_SF_LOG_SF_LOG_H_
#define SF_CONTENT_SF_LOG_SF_LOG_H_

#include "stm32f4xx_hal.h" // 修改为你实际MCU头文件
#include <stdint.h>

typedef enum {
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERR,
} log_level_t;

// 初始化，指定UART
void log_init(UART_HandleTypeDef *huart);
// 设置日志等级
void log_set_level(log_level_t level);
// 日志输出（建议用宏）
void log_output(log_level_t level, const char *file, int line, const char *fmt, ...);

// 自动带文件/行号
#define LOG_INFO(fmt, ...) log_output(LOG_LEVEL_INFO, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...) log_output(LOG_LEVEL_WARN, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_ERR(fmt, ...)  log_output(LOG_LEVEL_ERR,  __FILE__, __LINE__, fmt, ##__VA_ARGS__)

// shell输出，自动异步
void log_shell_send(const char *fmt, ...);

// 串口DMA完成回调
void log_uart_dma_tx_cplt_callback(void);



#endif /* SF_CONTENT_SF_LOG_SF_LOG_H_ */
