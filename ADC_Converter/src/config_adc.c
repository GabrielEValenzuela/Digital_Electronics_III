/*
 * config_adc.c
 *
 *  Created on: 29 ago. 2019
 *      Author: Gabriel Valenzuela
 */

#include "config_adc.h"
#include "lpc17xx_pinsel.h"

#define MAX_FREQ 200000

void config_adc(uint32_t freq, uint8_t channel){
	if(freq > MAX_FREQ || channel > 7){
		while(1);
	}
	ADC_Init(LPC_ADC, freq);

	ADC_ChannelCmd(LPC_ADC, channel, ENABLE);

	ADC_IntConfig(LPC_ADC, channel, ENABLE);

	return;
}

void config_input(uint8_t port, uint8_t pin){
	uint8_t pin_func;
	switch (port) {
		case 0:
			pin_func = PINSEL_FUNC_1;
			break;
		case 1:
			pin_func = PINSEL_FUNC_3;
			break;
		case 2:
			pin_func = PINSEL_FUNC_2;
			break;
		default:
			break;
	}
	PINSEL_CFG_Type PinCfg;
	PinCfg.Funcnum = (uint8_t) pin_func;
	PinCfg.OpenDrain = (uint8_t) 0;
	PinCfg.Pinmode = (uint8_t) 0;
	PinCfg.Pinnum = (uint8_t) pin;
	PinCfg.Portnum = (uint8_t) port;

	PINSEL_ConfigPin(&PinCfg);

	return;
}
