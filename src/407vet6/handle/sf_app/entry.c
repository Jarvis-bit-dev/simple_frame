/*
 * entry.c
 *
 *  Created on: Jul 17, 2025
 *      Author: Jarvis
 */
#include "entry.h"
#include "stdio.h"
#include <stdarg.h>
#include "var_register.h"
#include "function_register.h"
#include "usart.h"
#include "tim.h"
#include "sf_log.h"
#include "sf_err.h"
#include "sf_protocol.h"
#include "shell_logic.h"
#include "schedule.h"
#include "key.h"
/*************************************************************************************/

int counter = 0;
float voltage = 3.3f;
char name[32] = "STM32";

typedef struct {
	int age;
	float score;
} student_t;
student_t stu = { 18, 90.0 };

int test_func(int argc, char **argv) {
	printf("test_func called with %d args\n", argc);
	return 0;
}
int arr[5] = { 1, 2, 3, 4, 5 };

int sensor_check(void *arg) {
	return (*(int*) arg > 100);
}
void sensor_action(void *arg) {
	LOG_WARN("Sensor报警: %d", *(int* )arg);
}
void sensor_recover(void *arg) {
	LOG_INFO("Sensor恢复: %d", *(int* )arg);
}

int sensor_val = 0;

uint8_t key1_read(void) {
	uint8_t status = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1);
	return status;
}

void key1_on_click(key_t *key)   { /* 单击处理 */
	LOG_INFO("按键1单击事件触发！");
}

void key1_on_double(key_t *key)  { /* 双击处理 */
	LOG_INFO("按键1双击事件触发！");
}

const key_event_handler_t key1_handlers = {
    .on_click = key1_on_click,
    .on_double = key1_on_double,
};


key_t key1 = {
    .read_fn = key1_read,
    .id = 1,
    .group = 0,
    .active_level = 0, // 低有效
    .event_handler = &key1_handlers,
};


void keys_init(void) {
    key_register(&key1);
}

static void key_app(void) {
	 key_scan_all(5);

}
/*************************************************************************************/

void shell_uart_parser(const uint8_t *data, uint16_t len) {
	shell_exec((const char*) data);
	uart_manager_clear(&huart1);

}

/**
 * @brief 初始化硬件相关资源，如串口解析器注册等。
 *
 * @return uint8_t 返回 0 表示初始化成功，其他值保留为错误码
 */

static uint8_t sf_hardware_init() {
	//搁置
	HAL_TIM_Base_Start_IT(&htim6);
	//real time task
	HAL_TIM_Base_Start_IT(&htim7);
	//shell解析挂载
	uart_manager_register(&huart1, shell_uart_parser);
	//日志系统
	log_init(&huart1);
	//按键检测
	keys_init();
	//错误模块
	error_register("sensor_warn", ERROR_LEVEL_WARNING, sensor_check,
			sensor_action, sensor_recover, &sensor_val, 3);

	return 0;
}

/**
 * @brief 初始化软件相关资源，包括变量、函数注册以及任务系统启动。
 *
 * @return uint8_t 返回 0 表示初始化成功，其他值保留为错误码
 */
static uint8_t sf_software_init() {

	//shell 模块测试
	SHELL_VAR_REGISTER(counter, VAR_TYPE_INT);
	SHELL_VAR_REGISTER(voltage, VAR_TYPE_FLOAT);
	SHELL_VAR_REGISTER(name, VAR_TYPE_STRING);
	SHELL_VAR_REGISTER(sensor_val, VAR_TYPE_INT);
	SHELL_VAR_REGISTER(stu.age, VAR_TYPE_INT);
	SHELL_VAR_REGISTER(stu.score, VAR_TYPE_FLOAT);
	shell_register_array("arr", arr, VAR_TYPE_INT, sizeof(int), 5);

	SHELL_FUNC_REGISTER(test_func);

	//调度器初始化
	task_system_init();

	//串口协议任务
	task_add(TASK_COMM_PROTOCOL, (task_func_t) uart_manager_poll,
		NULL, 0, 100,
		TASK_FOREVER);
	//按键扫描
	task_add(TASK_REALTIME, (task_func_t) key_app,
		NULL, 0, 5,
		TASK_FOREVER);
	//按键执行
	task_add(TASK_USER_INTERFACE, (task_func_t) key_evt_dispatch,
		NULL, 0, 100,
		TASK_FOREVER);
	//错误任务
	task_add(TASK_DIAGNOSTIC, (task_func_t)error_poll,
		NULL, 0, 100,
		TASK_FOREVER);
	return 0;
}

/**
 * @brief 系统统一初始化入口，调用硬件和软件初始化函数。
 */
void sf_entry(void) {
	sf_hardware_init();
	sf_software_init();
}

/**
 * @brief 按顺序执行多个任务（任务 ID 通过可变参数传入）。
 *
 * @param count 要执行的任务数量
 * @param ...   后续是 count 个 int 类型任务 ID
 */
static void sf_run(int count, ...) {
	va_list args;
	va_start(args, count);
	for (int i = 0; i < count; i++) {
		task_execute(va_arg(args, int));
	}
	va_end(args);
}

/**
 * @brief 主循环中调用的用户调度入口。
 *        执行串口通信协议任务、控制任务等。
 */
void sf_loop() {
	sf_run(3,
		TASK_COMM_PROTOCOL,
		TASK_USER_INTERFACE,
		TASK_DIAGNOSTIC
	);

}

