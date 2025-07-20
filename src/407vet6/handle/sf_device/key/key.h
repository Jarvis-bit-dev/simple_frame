/*
 * button.h
 *
 *  Created on: Jul 20, 2025
 *      Author: Jarvis
 */

#ifndef SF_DEVICE_KEY_KEY_H_
#define SF_DEVICE_KEY_KEY_H_


#include <stdint.h>

typedef enum {
    KEY_EVENT_NONE = 0,
    KEY_EVENT_DOWN,
    KEY_EVENT_UP,
    KEY_EVENT_CLICK,
    KEY_EVENT_DOUBLE,
    KEY_EVENT_LONG,
    KEY_EVENT_REPEAT,
    KEY_EVENT_COMBO,
} key_event_t;

// 状态机枚举
typedef enum {
    KEY_STATE_IDLE = 0,
    KEY_STATE_DEBOUNCE,
    KEY_STATE_PRESSED,
    KEY_STATE_LONG,
    KEY_STATE_WAIT_RELEASE,
	KEY_STATE_WAIT_CLICK
} key_state_t;

struct key_s;

typedef uint8_t (*key_read_fn)(void);
typedef void (*key_event_fn)(struct key_s *key);

typedef struct {
    key_event_fn on_down;
    key_event_fn on_up;
    key_event_fn on_click;
    key_event_fn on_double;
    key_event_fn on_long;
    key_event_fn on_repeat;
    key_event_fn on_combo;
} key_event_handler_t;

typedef struct key_s {
    key_read_fn                read_fn;
    const key_event_handler_t *event_handler;
    uint8_t                    id;
    uint8_t                    group;
    uint8_t                    active_level;
    // 状态机与消抖
    key_state_t    state;
    uint8_t        deb_cnt;
    uint16_t       press_tick;
    uint16_t       last_release_tick;
    uint8_t        click_count;
    struct key_s  *next;
} key_t;

typedef struct {
    uint8_t      key_id;
    key_event_t  event;
} key_evt_t;

// 注册注销
int  key_register(key_t *key);
void key_unregister(key_t *key);

// 检测
void key_scan_all(uint16_t tick_ms);

// 异步事件队列
#define KEY_EVT_QUEUE_SIZE 8
int  key_evt_pop(key_evt_t *evt);
void key_evt_enable(int en);

// 事件分发（动作执行）
void key_evt_dispatch(void);


#endif /* SF_DEVICE_KEY_KEY_H_ */
