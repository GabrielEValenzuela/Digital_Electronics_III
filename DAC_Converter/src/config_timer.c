/*
 * config_timer.c
 *
 *  Created on: 29 ago. 2019
 *      Author: Gabriel Valenzuela
 */


#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include "config_timer.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_systick.h"

void configTimer0forXuseg(uint32_t time){

	if(time>1000){
		while(1);
	}

	TIM_TIMERCFG_Type	timer_struct_config;

	timer_struct_config.PrescaleOption	    =	TIM_PRESCALE_USVAL;
	timer_struct_config.PrescaleValue		=	time;

	TIM_Init(LPC_TIM0,TIM_TIMER_MODE,&timer_struct_config);

	return;
}

void initTimer0(){

	TIM_Cmd(LPC_TIM0, ENABLE);

	NVIC_EnableIRQ(TIMER0_IRQn);

	return;
}

void configMatch0(uint32_t matcher){
	if(matcher>0xFFFFFFFF){
		while(1);
	}

	TIM_MATCHCFG_Type	match_ch_struct;

	match_ch_struct.MatchChannel		=	0;
	match_ch_struct.IntOnMatch			=	ENABLE;
	match_ch_struct.ResetOnMatch		=	ENABLE;
	match_ch_struct.StopOnMatch			=	DISABLE;
	match_ch_struct.ExtMatchOutputType	=	TIM_EXTMATCH_NOTHING;
	match_ch_struct.MatchValue			=	matcher;

	TIM_ConfigMatch(LPC_TIM0, &match_ch_struct);

	return;
}

/*!
 * @brief With a CCLK of 100[MHz] the max value of Systick is 167.7[ms]
 */

void configSystick(uint16_t time){
	if(time>165){
		while(1);
	}

	SYSTICK_InternalInit(time);

	return;
}

void initSystick(){
	SYSTICK_Cmd(ENABLE);

	SYSTICK_IntCmd(DISABLE);
	return;
}

