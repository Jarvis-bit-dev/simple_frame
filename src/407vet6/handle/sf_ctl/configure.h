/*
 * configure.h
 *
 *  Created on: Jul 17, 2025
 *      Author: Jarvis
 */

#ifndef SF_CTL_CONFIGURE_H_
#define SF_CTL_CONFIGURE_H_


#define SIMPLE_FRAME_VERSION "1.0"
#define PROJECT_NAME         "simple_frame"
#define PROJECT_AUTHOR       "Jarvis"
#define BOARD_NAME           "STM32F407"
#define BOOT_VERSION         "B0.0"

const char * const software_version = "V0.0.0";
const char * const build_date = __DATE__;
const char * const build_time = __TIME__;
const char * const build_type =
#ifdef DEBUG
    "DEBUG";
#else
    "RELEASE";
#endif


#endif /* SF_CTL_CONFIGURE_H_ */
