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
/*******************************************/
int aa=10;
static void sf_test(void *arg){
	 int *cnt = (int *)arg;
	printf("this is test:%d\r\n",*cnt);
}


int motor_speed = 1500;
float motor_voltage = 24.5f;
uint32_t system_flags = 0xAABBCCDD;
uint8_t enabled = 1;
static uint8_t sf_hardware_init(){

	//使用串口1 实现  空闲中断接收的功能
	 VAR_REGISTER(motor_speed, VAR_TYPE_INT);
	    VAR_REGISTER(motor_voltage, VAR_TYPE_FLOAT);
	return 0;
}



static uint8_t sf_software_init(){
	task_system_init();
	task_add(0,sf_test,&aa,1000,1000,5);
	return 0;
}


void sf_entry(void){
	 sf_hardware_init();
	 sf_software_init();
 }

/**
 * @brief  执行不同的任务链
 *
 * @param  count     链表个数
 * @param  param1    链表1
 * @param  param2    链表2
 *
 * @return void
 *
 * @note
 */
static void sf_run(int count,...){
	va_list args;
	va_start(args, count);
	for(int i = 0; i < count; i++) {
		task_execute(va_arg(args, int));
	}
	va_end(args);
}
void sf_loop(){
	sf_run(2,
		   TASK_COMM_PROTOCOL,
		   TASK_CONTROL_LOOP);
}




