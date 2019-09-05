/*
 * config_gpio.h
 *
 *  Created on: 30 ago. 2019
 *      Author: Gabriel Valenzuela
 */

#ifndef CONFIG_GPIO_H_
#define CONFIG_GPIO_H_

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include "lpc17xx_gpio.h"

void config_gpio(void);

void lightOn_greenLED(void);

void lightOn_yellowLED(void);

void lightOn_redLED(void);

void lightOff_greenLED(void);

void lightOff_yellowLED(void);

void lightOff_redLED(void);

void lightOff_All(void);

void toggle_redLED(void);

#endif /* CONFIG_GPIO_H_ */
