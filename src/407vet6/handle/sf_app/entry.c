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


int motor_speed = 0;
float temperature = 36.5;
int enabled = 1;
static uint8_t sf_hardware_init(){
	REGISTER_VAR(motor_speed, VAR_TYPE_INT);
	REGISTER_VAR(temperature, VAR_TYPE_FLOAT);
	REGISTER_VAR(enabled, VAR_TYPE_BOOL);
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




