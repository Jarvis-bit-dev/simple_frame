/*
 * button.c
 *
 *  Created on: Jul 20, 2025
 *      Author: Jarvis
 */
#include "key.h"
#include <string.h>

static key_t *key_head = 0;
static int key_count = 0;
#define MAX_KEY_NUM 16

// 事件队列
static key_evt_t key_evt_queue[KEY_EVT_QUEUE_SIZE];
static int evt_q_head = 0, evt_q_tail = 0;
static int queue_enable = 1;

static void key_evt_push(uint8_t id, key_event_t evt) {
    if (!queue_enable) return;
    int next = (evt_q_tail + 1) % KEY_EVT_QUEUE_SIZE;
    if (next != evt_q_head) {
        key_evt_queue[evt_q_tail].key_id = id;
        key_evt_queue[evt_q_tail].event  = evt;
        evt_q_tail = next;
    }
}
int key_evt_pop(key_evt_t *evt) {
    if (evt_q_head == evt_q_tail) return 0;
    *evt = key_evt_queue[evt_q_head];
    evt_q_head = (evt_q_head + 1) % KEY_EVT_QUEUE_SIZE;
    return 1;
}
void key_evt_enable(int en) { queue_enable = en; }

int key_register(key_t *key) {
    if (key_count >= MAX_KEY_NUM) return -1;
    memset(&key->state, 0, sizeof(key_state_t)); // 安全
    key->deb_cnt = 0;
    key->press_tick = 0;
    key->last_release_tick = 0;
    key->click_count = 0;
    key->was_long_pressed = 0;
    key->next = key_head;
    key_head = key;
    key_count++;
    return 0;
}
void key_unregister(key_t *key) {
    key_t **pp = &key_head;
    while (*pp) {
        if (*pp == key) {
            *pp = key->next;
            key_count--;
            return;
        }
        pp = &((*pp)->next);
    }
}

// === 状态机参数 ===
#define DEBOUNCE_MS      20   // 按下消抖时长(ms)
#define CLICK_INTERVAL   250  // 双击最大间隔(ms)
#define LONG_PRESS_MS    1000 // 长按时长(ms)
#define REPEAT_MS        200  // 连发周期(ms)

static void key_state_machine(key_t *key, uint16_t tick_ms, uint16_t now_tick)
{
    uint8_t cur_level = key->read_fn ? key->read_fn() : 1;
    uint8_t is_down = (cur_level == key->active_level);

    switch (key->state) {
    case KEY_STATE_IDLE:
        if (is_down) {
            key->state = KEY_STATE_DEBOUNCE;
            key->deb_cnt = 0;
        }
        break;
    case KEY_STATE_DEBOUNCE:
        if (is_down) {
            key->deb_cnt += tick_ms;
            if (key->deb_cnt >= DEBOUNCE_MS) {
                key->state = KEY_STATE_PRESSED;
                key->press_tick = 0;
                key->was_long_pressed = 0;
                key_evt_push(key->id, KEY_EVENT_DOWN);
            }
        } else {
            key->state = KEY_STATE_IDLE;
        }
        break;
    case KEY_STATE_PRESSED:
        if (is_down) {
            key->press_tick += tick_ms;
            if (key->press_tick == LONG_PRESS_MS) {
                key_evt_push(key->id, KEY_EVENT_LONG);
                key->was_long_pressed = 1;
                key->state = KEY_STATE_LONG;
                key->press_tick = 0;
            }
        } else {
            key->state = KEY_STATE_WAIT_RELEASE;
            key->deb_cnt = 0;
        }
        break;
    case KEY_STATE_LONG:
        if (is_down) {
            key->press_tick += tick_ms;
            if (key->press_tick >= REPEAT_MS) {
                key->press_tick = 0;
                key_evt_push(key->id, KEY_EVENT_REPEAT);
            }
        } else {
            key->state = KEY_STATE_WAIT_RELEASE;
            key->deb_cnt = 0;
        }
        break;
    case KEY_STATE_WAIT_RELEASE:
    	 if (!is_down) {
    	            key->deb_cnt += tick_ms;
    	            if (key->deb_cnt >= DEBOUNCE_MS) {
    	                key_evt_push(key->id, KEY_EVENT_UP);

    	                if (key->was_long_pressed) {
    	                    key->state = KEY_STATE_IDLE; // 长按后直接返回，不进入CLICK判断
    	                } else {
    	                    key->state = KEY_STATE_WAIT_CLICK;
    	                    key->press_tick = 0;
    	                }

    	                key->was_long_pressed = 0; // 清除标志
    	            }
    	        } else {
    	            key->state = KEY_STATE_DEBOUNCE;
    	            key->deb_cnt = 0;
    	        }
    	        break;
    case KEY_STATE_WAIT_CLICK:
        key->press_tick += tick_ms;
        if (is_down) {
            key->state = KEY_STATE_DEBOUNCE;
            key->deb_cnt = 0;
            // 记录已按下第二次（本次不计入双击计数）
        } else if (key->press_tick >= CLICK_INTERVAL) {
            // 等待期间未发生第二次按下，确认单击
            key_evt_push(key->id, KEY_EVENT_CLICK);
            key->state = KEY_STATE_IDLE;
        }
        // 还要检测二次完整按下抬起
        if (is_down) {
            key->state = KEY_STATE_DEBOUNCE;
            key->deb_cnt = 0;
            key->click_count = 1;
        } else if (key->click_count == 1 && !is_down) {
            // 第二次抬起，直接判为双击
            key_evt_push(key->id, KEY_EVENT_DOUBLE);
            key->click_count = 0;
            key->state = KEY_STATE_IDLE;
        }
        break;
    default: key->state = KEY_STATE_IDLE; break;
    }
}

void key_scan_all(uint16_t tick_ms) {
    static uint16_t sys_tick = 0;
    sys_tick += tick_ms;
    key_t *k = key_head;
    while (k) {
        key_state_machine(k, tick_ms, sys_tick);
        k = k->next;
    }
    // 组合键检测
    for (uint8_t group = 1; group < 16; group++) {
        int group_count = 0, down_count = 0;
        k = key_head;
        while (k) {
            if (k->group == group) {
                group_count++;
                if (k->state == KEY_STATE_PRESSED || k->state == KEY_STATE_LONG)
                    down_count++;
            }
            k = k->next;
        }
        if (group_count && down_count == group_count) {
            k = key_head;
            while (k) {
                if (k->group == group) {
                    key_evt_push(k->id, KEY_EVENT_COMBO);
                }
                k = k->next;
            }
        }
    }
}

// ========== 事件分发 ==========
void key_evt_dispatch(void)
{
    key_evt_t evt;
    key_t *k;
    while (key_evt_pop(&evt)) {
        for (k = key_head; k; k = k->next) {
            if (k->id == evt.key_id && k->event_handler) {
                switch (evt.event) {
                case KEY_EVENT_DOWN:    if (k->event_handler->on_down)    k->event_handler->on_down(k);    break;
                case KEY_EVENT_UP:      if (k->event_handler->on_up)      k->event_handler->on_up(k);      break;
                case KEY_EVENT_CLICK:   if (k->event_handler->on_click)   k->event_handler->on_click(k);   break;
                case KEY_EVENT_DOUBLE:  if (k->event_handler->on_double)  k->event_handler->on_double(k);  break;
                case KEY_EVENT_LONG:    if (k->event_handler->on_long)    k->event_handler->on_long(k);    break;
                case KEY_EVENT_REPEAT:  if (k->event_handler->on_repeat)  k->event_handler->on_repeat(k);  break;
                case KEY_EVENT_COMBO:   if (k->event_handler->on_combo)   k->event_handler->on_combo(k);   break;
                default: break;
                }
                break; // id唯一，无需继续
            }
        }
    }
}


