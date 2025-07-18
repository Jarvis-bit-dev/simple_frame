/*
 * schedule.h
 *
 *  Created on: Jul 17, 2025
 *      Author: Jarvis
 */

#ifndef SF_CONTENT_SF_SCHEDULER_SCHEDULE_H_
#define SF_CONTENT_SF_SCHEDULER_SCHEDULE_H_
#include <stdint.h>

#define MAX_TASK_NUM      64
#define MAX_TASK_LISTS    4

typedef void (*task_func_t)(void *arg);

typedef struct task_node {
    uint8_t used;
    uint32_t start_tick;       // 起始 tick
    uint32_t next_run_tick;    // 下一次运行时间
    uint32_t period;           // 周期（单位 ms）
    uint32_t remaining_count;  // 剩余运行次数
    task_func_t callback;
    void *arg;
    struct task_node *next;
} task_node_t;

typedef struct {
    task_node_t *head;
} task_list_t;

void task_system_init(void);
void task_system_tick_inc(void);             // 在 1ms 定时器中断调用
uint32_t task_system_get_tick(void);         // 获取当前 tick

int task_add(uint8_t list_id, task_func_t cb, void *arg, uint32_t delay, uint32_t period, uint32_t run_count);
int task_stop(task_func_t cb, void *arg);
void task_execute(uint8_t list_id);
void task_cleanup(void);

#endif /* SF_CONTENT_SF_SCHEDULER_SCHEDULE_H_ */
