/*
 * entry.c
 *
 *  Created on: Jul 17, 2025
 *      Author: Jarvis
 */
#include "entry.h"
#include "schedule.h"
#include "stdio.h"
#include <stdarg.h>
#include "var_register.h"
#include "function_register.h"
#include "sf_protocol.h"
#include "shell_logic.h"
#include "usart.h"
#include "tim.h"
#include "sf_log.h"
/*************************************************************************************/


int counter = 0;
float voltage = 3.3f;
char name[32] = "STM32";

int test_func(int argc, char **argv) {
    printf("test_func called with %d args\n", argc);
    return 0;
}


void shell_uart_parser(const uint8_t *data, uint16_t len) {
	shell_exec((const char *)data);
	uart_manager_clear(&huart1);

}
/*************************************************************************************/




/**
 * @brief 初始化硬件相关资源，如串口解析器注册等。
 *
 * @return uint8_t 返回 0 表示初始化成功，其他值保留为错误码
 */
static uint8_t sf_hardware_init(){
	HAL_TIM_Base_Start_IT(&htim6);
	HAL_TIM_Base_Start_IT(&htim7);
	uart_manager_register(&huart1, shell_uart_parser);
	log_init(&huart1);
	LOG_INFO("系统启动OK");
	LOG_WARN("温度超限: %d", 100);
	LOG_ERR("通信异常: code=%d", 2000);
	log_shell_send("Hello shell %d, %s\n", 2024, "world");

	return 0;
}


/**
 * @brief 初始化软件相关资源，包括变量、函数注册以及任务系统启动。
 *
 * @return uint8_t 返回 0 表示初始化成功，其他值保留为错误码
 */
static uint8_t sf_software_init(){

	SHELL_VAR_REGISTER(counter, VAR_TYPE_INT);
	SHELL_VAR_REGISTER(voltage, VAR_TYPE_FLOAT);
	SHELL_VAR_REGISTER(name, VAR_TYPE_STRING);
	SHELL_FUNC_REGISTER(test_func);


	task_system_init();
	task_add(TASK_COMM_PROTOCOL,
			 (task_func_t)uart_manager_poll,
			 NULL,
			 0,
			 100,
			 TASK_FOREVER);

	return 0;
}

/**
 * @brief 系统统一初始化入口，调用硬件和软件初始化函数。
 */
void sf_entry(void){
	 sf_hardware_init();
	 sf_software_init();
 }

/**
 * @brief 按顺序执行多个任务（任务 ID 通过可变参数传入）。
 *
 * @param count 要执行的任务数量
 * @param ...   后续是 count 个 int 类型任务 ID
 */
static void sf_run(int count,...){
	va_list args;
	va_start(args, count);
	for(int i = 0; i < count; i++) {
		task_execute(va_arg(args, int));
	}
	va_end(args);
}

/**
 * @brief 主循环中调用的用户调度入口。
 *        执行串口通信协议任务、控制任务等。
 */
void sf_loop(){
	sf_run(2,
			TASK_COMM_PROTOCOL,
		   TASK_CONTROL_LOOP);
}




