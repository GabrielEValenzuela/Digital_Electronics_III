/*
===============================================================================
 Name        : DAC.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>
#include "configdac.h"
#include "config_timer.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_dac.h"


static uint32_t max_value = 1023;

void config_analog_output(void);

/*!
 * Onda diente de sierra con una frecuencia de 100[Hz]
 */

void TIMER0_IRQHandler(){
	TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);

	if(max_value != 0){
		DAC_UpdateValue(LPC_DAC,max_value--);
	}
	else{
		max_value = 1023;
		DAC_UpdateValue(LPC_DAC,max_value);
	}

	return;


}

int main(void) {

	config_dac();

	config_analog_output();

	configTimer0forXuseg(100);

	configMatch0(100);

	DAC_UpdateValue(LPC_DAC,max_value);

	while(1) {
    }

    return 0 ;
}

void config_analog_output(){
	PINSEL_CFG_Type pin_config;

	pin_config.Portnum = PINSEL_PORT_0;
	pin_config.Pinnum  = PINSEL_PIN_26;
	pin_config.Pinmode = PINSEL_PINMODE_PULLUP;
	pin_config.Funcnum = PINSEL_FUNC_2;
	pin_config.OpenDrain = PINSEL_PINMODE_NORMAL;
	PINSEL_ConfigPin(&pin_config);
	return;
}
