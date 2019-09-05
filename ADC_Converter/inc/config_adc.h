/*
 * config_adc.h
 *
 *  Created on: 29 ago. 2019
 *      Author: Gabriel Valenzuela
 */

#ifndef CONFIG_ADC_H_
#define CONFIG_ADC_H_

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include "lpc17xx_adc.h"

void config_adc(uint32_t freq, uint8_t channel);

void config_input(uint8_t port, uint8_t pin);

#endif /* CONFIG_ADC_H_ */
