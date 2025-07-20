/*
 * sf_err.c
 *
 *  Created on: Jul 20, 2025
 *      Author: Jarvis
 */
#include "sf_err.h"
#include <string.h>
#include "sf_log.h"
#define MAX_ERROR_ITEMS 16

typedef struct {
    const char *name;
    error_level_t level;
    error_check_fn check;
    error_action_fn action;
    error_action_fn recover;
    void *arg;
    uint16_t threshold;
    uint16_t counter;
    uint8_t active;
} error_item_t;

static error_item_t error_table[MAX_ERROR_ITEMS];
static uint8_t error_count = 0;

int error_register(const char *name, error_level_t level,
                  error_check_fn check,
                  error_action_fn action,
                  error_action_fn recover,
                  void *arg, uint16_t threshold)
{
    if (error_count >= MAX_ERROR_ITEMS) return -1;
    error_item_t *item = &error_table[error_count++];
    item->name = name;
    item->level = level;
    item->check = check;
    item->action = action;
    item->recover = recover;
    item->arg = arg;
    item->threshold = threshold;
    item->counter = 0;
    item->active = 0;
    return 0;
}

void error_poll(void)
{
    for (uint8_t i = 0; i < error_count; i++) {
        error_item_t *item = &error_table[i];
        int err = item->check(item->arg);
        if (err) {
            if (item->counter < item->threshold) item->counter++;
        } else {
            item->counter = 0;
        }
        if (item->counter >= item->threshold && !item->active) {
            item->active = 1;
            if (item->action) item->action(item->arg);
        }
        // 错误恢复
        if (item->counter == 0 && item->active) {
            item->active = 0;
            if (item->recover) item->recover(item->arg);
        }
    }
}

int error_query(const char *name, error_level_t *level, uint8_t *active)
{
    for (uint8_t i = 0; i < error_count; i++) {
        error_item_t *item = &error_table[i];
        if (strcmp(item->name, name) == 0) {
            if (level) *level = item->level;
            if (active) *active = item->active;
            return 0;
        }
    }
    return -1;
}

void error_list_print(void)
{
	LOG_INFO("\r\n[Error List]\r\n");
    for (uint8_t i = 0; i < error_count; i++) {
        error_item_t *item = &error_table[i];
        LOG_ERR("%-16s | %-7s | %s\r\n",
            item->name,
            (item->level == ERROR_LEVEL_WARNING) ? "WARN" : "ERROR",
            item->active ? "ACTIVE" : "NORMAL");
    }
}
