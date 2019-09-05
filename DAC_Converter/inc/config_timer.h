/*
 * config_timer.h
 *
 *  Created on: 29 ago. 2019
 *      Author: Gabriel Valenzuela
 */

#ifndef CONFIG_TIMER_H_
#define CONFIG_TIMER_H_

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

/*!
 * @brief Configure the Timer0 for X micro seconds
 * @param Time
 * @return none
 */
void configTimer0forXuseg(uint32_t time);

void initTimer0(void);

void configMatch0(uint32_t matcher);

void configSystick(uint16_t time);

void initSystick(void);


#endif /* CONFIG_TIMER_H_ */
