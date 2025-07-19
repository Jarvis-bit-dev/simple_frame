/*
 * sf_protovol.c
 *
 *  Created on: Jul 19, 2025
 *      Author: Jarvis
 */
#include "sf_protocol.h"
#include <string.h>

static uart_channel_t uart_channels[UART_MAX_CHANNELS] = {0};

// 注册串口及其解析函数
int uart_manager_register(UART_HandleTypeDef *huart, uart_parse_func_t parser) {
    for (int i = 0; i < UART_MAX_CHANNELS; ++i) {
        if (uart_channels[i].huart == NULL || uart_channels[i].huart == huart) {
            uart_channels[i].huart = huart;
            uart_channels[i].parser = parser;
            uart_channels[i].rx_len = 0;
            uart_channels[i].ready = 0;

            // 启动 DMA 接收
            HAL_UART_Receive_DMA(huart, uart_channels[i].rx_buffer, UART_RX_BUFFER_SIZE);
            __HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);
            return 0;
        }
    }
    return -1;
}

// 注销串口解析器
int uart_manager_unregister(UART_HandleTypeDef *huart) {
    for (int i = 0; i < UART_MAX_CHANNELS; ++i) {
        if (uart_channels[i].huart == huart) {
            uart_channels[i].huart = NULL;
            uart_channels[i].parser = NULL;
            uart_channels[i].ready = 0;
            HAL_UART_AbortReceive(huart);
            return 0;
        }
    }
    return -1;
}


int uart_manager_clear(UART_HandleTypeDef *huart) {
    for (int i = 0; i < UART_MAX_CHANNELS; ++i) {
        if (uart_channels[i].huart == huart) {
            uart_channels[i].rx_len = 0;
            uart_channels[i].ready = 0;
            memset(uart_channels[i].rx_buffer, 0, UART_RX_BUFFER_SIZE);
            return 0;
        }
    }
    return -1;  // 未找到该串口
}

// 空闲中断触发：记录长度、设置就绪标志
void uart_manager_idle_callback(UART_HandleTypeDef *huart) {
    for (int i = 0; i < UART_MAX_CHANNELS; ++i) {
        if (uart_channels[i].huart == huart) {
            __HAL_UART_CLEAR_IDLEFLAG(huart);
            HAL_UART_DMAStop(huart);
            uart_channels[i].rx_len = UART_RX_BUFFER_SIZE - __HAL_DMA_GET_COUNTER(huart->hdmarx);
            uart_channels[i].ready = 1;

            HAL_UART_Receive_DMA(huart, uart_channels[i].rx_buffer, UART_RX_BUFFER_SIZE);
            break;
        }
    }
}

// 主循环中轮询调用此函数
void uart_manager_poll(void) {
    for (int i = 0; i < UART_MAX_CHANNELS; ++i) {
        if (uart_channels[i].ready && uart_channels[i].parser) {
            uart_channels[i].parser(uart_channels[i].rx_buffer, uart_channels[i].rx_len);
            uart_channels[i].ready = 0;
        }
    }
}
