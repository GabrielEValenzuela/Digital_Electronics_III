/*
===============================================================================
 Name        : Timers.c
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

/*!
 * Header files to project. Include library
 */
#include "config_timer.h"
#include "config_adc.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_systick.h"
#include "lpc17xx_timer.h"
#include "lpc_types.h"
#include "define.h"
#include "config_gpio.h"

void init(void);

void compare_and_show(uint32_t measure);

/*!
 * *********************************** HANDLERS *********************************************************
 */

static uint32_t counter_systick = 0;
static uint32_t critic_flag = 0;
const uint32_t counter_convert = 10;
uint32_t max_counter_sys = 3;

void ADC_IRQHandler(){
	static uint32_t adc_result = 0;
	NVIC_DisableIRQ(ADC_IRQn);
	for(int i = 0;i<counter_convert;i++){
	while(ADC_ChannelGetStatus(LPC_ADC,ADC_CHANNEL_0,ADC_DATA_DONE)==RESET);
		adc_result += ADC_GetData(ADC_CHANNEL_0);
		ADC_StartCmd(LPC_ADC, ADC_START_NOW);
	}
	adc_result=adc_result/10;
	compare_and_show(adc_result);
	return;
}

void TIMER0_IRQHandler(){
	TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);

	if (critic_flag) {
		TIM_UpdateMatchValue(LPC_TIM0,0,2*SEGUNDO);
	}

	ADC_StartCmd(LPC_ADC, ADC_START_NOW);

	NVIC_EnableIRQ(ADC_IRQn);

	return;


}

void SysTick_Handler(){
	SYSTICK_ClearCounterFlag();
	counter_systick++;
	if(counter_systick<max_counter_sys){
		return;
	}
	toggle_redLED();
	return;
}

int main(){

	init();
	lightOn_redLED();
	lightOn_greenLED();
	lightOn_yellowLED();
	lightOff_All();

	while(1);

	return 0;
}

void init(){
	config_input(0,23);

	config_gpio();

	configSystick(100);

	configTimer0forXuseg((uint32_t) 100);

	configMatch0(5*SEGUNDO);

	config_adc(200000, 0);


	initSystick();

	initTimer0();

	return;
}

void compare_and_show(uint32_t measure){
	if(measure>=80){
		critic_flag++;
		SYSTICK_IntCmd(ENABLE);
		lightOff_All();
		if(critic_flag==10){
			max_counter_sys = 10;
			lightOff_All();
			ADC_DeInit(LPC_ADC);
		}
	}
	else if(50<=measure && measure<80){
		lightOff_All();
		lightOn_yellowLED();
		SYSTICK_IntCmd(DISABLE);
		critic_flag = 0;
	}
	else if(measure<50){
		lightOff_All();
		lightOn_greenLED();
		SYSTICK_IntCmd(DISABLE);
		critic_flag=0;
	}
	return;
}

