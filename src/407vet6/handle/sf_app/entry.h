/*
 * entry.h
 *
 *  Created on: Jul 17, 2025
 *      Author: Jarvis
 */

#ifndef SF_APP_ENTRY_H_
#define SF_APP_ENTRY_H_
typedef enum {
	TASK_REALTIME,
    TASK_SENSOR,           // 传感器采集与处理任务（如温度、加速度、距离）
    TASK_COMM_PROTOCOL,        // 协议处理任务（如Modbus、CAN、BLE协议帧解析）
    TASK_COMM_IO,              // 通信IO任务（如串口/网络收发、驱动）
    TASK_CONTROL_LOOP,         // 控制任务（如PID、电机控制、闭环调节）
    TASK_MONITORING,           // 系统状态监控（电流、电压、运行时间等）
    TASK_DATA_LOGGING,         // 数据记录、日志、趋势曲线采样
    TASK_STORAGE_OP,           // Flash、EEPROM 等非易失存储任务
    TASK_USER_INTERFACE,       // 指示灯、LCD、按键、UI交互相关
    TASK_DIAGNOSTIC,           // 自检、故障检测、状态标志处理
    TASK_MAINTENANCE           // 升级、配置、后台维护类任务
} task_purpose_t;


void sf_entry(void);
void sf_loop(void);

#endif /* SF_APP_ENTRY_H_ */
