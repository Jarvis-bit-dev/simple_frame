/*
 * schedule.c
 *
 *  Created on: Jul 17, 2025
 *      Author: Jarvis
 */
#include "schedule.h"
#include "stddef.h"
static volatile uint32_t sys_tick = 0;
static task_list_t task_lists[MAX_TASK_LISTS];
static task_node_t task_pool[MAX_TASK_NUM];

void task_system_init(void) {
    for (int i = 0; i < MAX_TASK_NUM; i++) {
        task_pool[i].used = 0;
        task_pool[i].next = NULL;
    }
    for (int i = 0; i < MAX_TASK_LISTS; i++) {
        task_lists[i].head = NULL;
    }
    sys_tick = 0;
}

void task_system_tick_inc(void) {
    sys_tick++;
}

uint32_t task_system_get_tick(void) {
    return sys_tick;
}

static task_node_t* alloc_task_node(void) {
    for (int i = 0; i < MAX_TASK_NUM; i++) {
        if (!task_pool[i].used) {
            task_pool[i].used = 1;
            task_pool[i].next = NULL;
            return &task_pool[i];
        }
    }
    return NULL;
}

int task_add(uint8_t list_id, task_func_t cb, void *arg, uint32_t delay, uint32_t period, uint32_t run_count) {
    if (list_id >= MAX_TASK_LISTS || cb == NULL)
        return 0;

    task_node_t *node = alloc_task_node();
    if (!node) return 0;

    uint32_t now = task_system_get_tick();

    node->start_tick = now;
    node->next_run_tick = now + delay;
    node->period = period;
    node->remaining_count = run_count;
    node->callback = cb;
    node->arg = arg;

    node->next = task_lists[list_id].head;
    task_lists[list_id].head = node;
    return 1;
}

int task_stop(task_func_t cb, void *arg) {
    for (int i = 0; i < MAX_TASK_LISTS; i++) {
        task_node_t *node = task_lists[i].head;
        while (node) {
            if (node->used && node->callback == cb && node->arg == arg) {
                node->remaining_count = 0;
                return 1;
            }
            node = node->next;
        }
    }
    return 0;
}

// 溢出安全比较
static inline int32_t tick_elapsed(uint32_t now, uint32_t target) {
    return (int32_t)(now - target);
}

void task_execute(uint8_t list_id) {
    if (list_id >= MAX_TASK_LISTS)
        return;

    uint32_t now = task_system_get_tick();
    task_node_t *node = task_lists[list_id].head;

    while (node) {
        if (node->used && node->remaining_count != 0) {
            if (tick_elapsed(now, node->next_run_tick) >= 0) {
                node->callback(node->arg);
                if (node->remaining_count != TASK_FOREVER) {
                    node->remaining_count--;
                }
                node->next_run_tick += node->period;
            }
        }
        node = node->next;
    }
}

void task_cleanup(void) {
    for (int i = 0; i < MAX_TASK_LISTS; i++) {
        task_node_t **p = &task_lists[i].head;
        while (*p) {
            task_node_t *cur = *p;
            if (cur->used && cur->remaining_count == 0) {
                cur->used = 0;
                *p = cur->next;
            } else {
                p = &(*p)->next;
            }
        }
    }
}
