/*
 * sf_log.c
 *
 *  Created on: Jul 20, 2025
 *      Author: Jarvis
 */
#include "sf_log.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>


#define LOG_BUF_SIZE        1024
#define LOG_LINE_MAX        256

static const char *log_level_color[] = {
    [LOG_LEVEL_INFO] = "\x1b[32m",
    [LOG_LEVEL_WARN] = "\x1b[33m",
    [LOG_LEVEL_ERR]  = "\x1b[31m",
};
#define LOG_COLOR_RESET "\x1b[0m"

static uint8_t log_buf[LOG_BUF_SIZE];
static volatile uint16_t log_head = 0; // 读指针
static volatile uint16_t log_tail = 0; // 写指针
static volatile uint8_t log_dma_busy = 0;
static UART_HandleTypeDef *log_uart = NULL;
static log_level_t log_level_limit = LOG_LEVEL_INFO;

// 新增：记录当前发送长度，回调推进用
static uint16_t log_last_tx_len = 0;

// 剩余空间
static uint16_t log_buf_free(void) {
    return (log_tail >= log_head) ?
        (LOG_BUF_SIZE - (log_tail - log_head) - 1) :
        (log_head - log_tail - 1);
}

// 覆盖最旧数据写入
static void log_buf_write(const uint8_t *data, uint16_t n) {
    // 空间不够，推进head
    while (log_buf_free() < n) {
        log_head = (log_head + 1) % LOG_BUF_SIZE;
    }
    for (int i = 0; i < n; i++) {
        log_buf[log_tail] = data[i];
        log_tail = (log_tail + 1) % LOG_BUF_SIZE;
    }
}

// 启动DMA异步发送（每次只发一段连续空间）
static void log_start_tx(void) {
    if (log_dma_busy || log_head == log_tail || log_uart == NULL) return;
    uint16_t len;
    if (log_tail > log_head) {
        len = log_tail - log_head;
    } else {
        len = LOG_BUF_SIZE - log_head;
    }
    log_last_tx_len = len;
    log_dma_busy = 1;
    HAL_UART_Transmit_DMA(log_uart, &log_buf[log_head], len);
}

// 串口DMA完成回调，继续下一段
void log_uart_dma_tx_cplt_callback(void) {
    // 推进head指针
    log_head = (log_head + log_last_tx_len) % LOG_BUF_SIZE;
    log_dma_busy = 0;
    // 有数据继续发送
    log_start_tx();
}

void log_init(UART_HandleTypeDef *huart) {
    log_uart = huart;
    log_head = log_tail = 0;
    log_dma_busy = 0;
    log_level_limit = LOG_LEVEL_INFO;
}

void log_set_level(log_level_t level) {
    log_level_limit = level;
}

void log_output(log_level_t level, const char *file, int line, const char *fmt, ...) {
    if (level < log_level_limit) return;
    char msg[LOG_LINE_MAX];
    int n = 0;
    n += snprintf(msg+n, sizeof(msg)-n, "%s[%s][%s:%d] ",
        log_level_color[level],
        (level==LOG_LEVEL_INFO)?"INFO":(level==LOG_LEVEL_WARN)?"WARN":"ERR",
        file, line);
    va_list ap;
    va_start(ap, fmt);
    n += vsnprintf(msg+n, sizeof(msg)-n, fmt, ap);
    va_end(ap);
    n += snprintf(msg+n, sizeof(msg)-n, "%s\r\n", LOG_COLOR_RESET);
    if (n > sizeof(msg)) n = sizeof(msg);

    log_buf_write((uint8_t *)msg, n);
    log_start_tx();
}

// printf风格shell输出
void log_shell_send(const char *fmt, ...) {
    char msg[LOG_LINE_MAX];
    va_list ap;
    va_start(ap, fmt);
    int n = vsnprintf(msg, sizeof(msg), fmt, ap);
    va_end(ap);
    if (n > sizeof(msg)) n = sizeof(msg);

    log_buf_write((uint8_t *)msg, n);
    log_start_tx();
}
