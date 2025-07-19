/*
 * sf_protocol.h
 *
 *  Created on: Jul 19, 2025
 *      Author: Jarvis
 */

#ifndef SF_CONTENT_SF_PROTOCOL_SF_PROTOCOL_H_
#define SF_CONTENT_SF_PROTOCOL_SF_PROTOCOL_H_

#include "main.h"
#include <stdint.h>

#define UART_MAX_CHANNELS     4
#define UART_RX_BUFFER_SIZE   256

typedef void (*uart_parse_func_t)(const uint8_t *data, uint16_t len);

typedef struct {
    UART_HandleTypeDef *huart;
    uint8_t rx_buffer[UART_RX_BUFFER_SIZE];  // DMA缓冲区
    uint16_t rx_len;                         // 数据长度
    volatile uint8_t ready;                  // 数据就绪标志
    uart_parse_func_t parser;                // 数据解析函数
} uart_channel_t;


int uart_manager_register(UART_HandleTypeDef *huart, uart_parse_func_t parser);
int uart_manager_unregister(UART_HandleTypeDef *huart);
void uart_manager_idle_callback(UART_HandleTypeDef *huart);
void uart_manager_poll(void);  // 在主循环中调用
int uart_manager_clear(UART_HandleTypeDef *huart);

#endif /* SF_CONTENT_SF_PROTOCOL_SF_PROTOCOL_H_ */
