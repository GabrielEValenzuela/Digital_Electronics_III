/*
===============================================================================
 Name        : main.c
 Author      : $(Gabriel Valenzuela)
 Version     : 2.0
 Copyright   : $(MIT)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif


#include <cr_section_macros.h>
#include "lpc17xx_gpio.h"
#include "lpc17xx_systick.h"
#include <lpc17xx_libcfg_default.h>
#include "lpc17xx_pinsel.h"
#include "lpc17xx_exti.h"

// TODO: insert other include files here
#define PORT_ZERO	(uint32_t) 0
#define PORT_THREE	(uint32_t) 3


#define INPUT	(uint8_t) 0
#define OUTPUT	(uint8_t) 1

#define RED_LED		( (uint32_t) (1<<22) )
#define BLUE_LED	( (uint32_t) (1<<26) )
#define GREEN_LED	( (uint32_t) (1<<25) )

FunctionalState Cur_State = ENABLE;

uint8_t counter = 0;
uint8_t flagOk = 0;
uint8_t flagRGB = 0;

void SysTick_Handler(void);

void Configurar_GPIOLedRojo(void);

void Configurar_GPIOLedAzul(void);

void Configurar_GPIOLedVerde(void);

void Configurar_GPIOSwitch(void);

void Prender_LedRojo(void);

void Prender_LedAzul(void);

void Prender_LedVerde(void);

void Apagar_LedRojo(void);

void Apagar_LedAzul(void);

void Apagar_LedVerde(void);

void Configurar_SwitchInterrupt(void);

BOOL_8 Verificar_LED(uint32_t PORT, uint32_t PIN_SELECT);

void Apagar_todos(void);

void init(void);

/*!
 * ********************** Funciones de manejo de interrupciones **********************
 */

void SysTick_Handler(void){
	//100ms
	//100ms * 100 = 10000ms = 10s
	SYSTICK_ClearCounterFlag();

	switch (flagOk) {
		case 0:
			counter++;
			if(counter<100){
				return;
			}
			else{
				Apagar_todos();
				Prender_LedRojo();
				while(1);
			}
			break;
		case 1:
			if(Verificar_LED(PORT_THREE, GREEN_LED)){
				Prender_LedVerde();
			}
			else {
				Apagar_LedVerde();
			}
			break;
		default:
			break;
	}
	return;
}

void EINT0_IRQHandler (){

	EXTI_ClearEXTIFlag(EXTI_EINT0);

	if(~(Verificar_LED(PORT_ZERO, RED_LED)&Verificar_LED(PORT_THREE, BLUE_LED)&Verificar_LED(PORT_THREE, GREEN_LED))&&flagRGB==0){
		Prender_LedRojo();

		SYSTICK_InternalInit(100);

		SYSTICK_IntCmd(ENABLE);

		SYSTICK_Cmd(ENABLE);

		flagRGB++;

		return;
	}

	switch (flagRGB) {
		case 1:
			Apagar_LedRojo();
			Prender_LedVerde();
			flagRGB++;
			break;
		case 2:
			Apagar_LedVerde();
			Prender_LedAzul();
			flagRGB++;
			break;
		case 3:
			Apagar_LedAzul();
			Prender_LedVerde();
			flagOk=1;
			break;
		default:
			flagRGB=1;
			break;
	}

	return;

}
// TODO: insert other definitions and declarations here

int main(void) {

	/*!
	 * Acordate que los clear prenden los LEDs y los sets los apaga
	 */
	init();
	Apagar_todos();
	while(1){
    }
    return 0;
}

void Apagar_todos(){
	Apagar_LedAzul();
	Apagar_LedRojo();
	Apagar_LedVerde();
	return;
}

void init(){
	Configurar_GPIOLedRojo();
	Configurar_GPIOLedAzul();
	Configurar_GPIOLedVerde();
	Configurar_GPIOSwitch();
	return;
}
void Configurar_GPIOLedRojo(){
	PINSEL_CFG_Type pin_config;

	pin_config.Portnum = PINSEL_PORT_0;
	pin_config.Pinnum  = PINSEL_PIN_22;
	pin_config.Pinmode = PINSEL_PINMODE_PULLUP;
	pin_config.Funcnum = PINSEL_FUNC_0;
	pin_config.OpenDrain = PINSEL_PINMODE_NORMAL;

	PINSEL_ConfigPin(&pin_config);
	GPIO_SetDir(PORT_ZERO, RED_LED, OUTPUT);
	return;

}

void Configurar_GPIOLedAzul(){
	PINSEL_CFG_Type pin_config;

	pin_config.Portnum = PINSEL_PORT_3;
	pin_config.Pinnum  = PINSEL_PIN_26;
	pin_config.Funcnum = PINSEL_FUNC_0;
	pin_config.Pinmode = PINSEL_PINMODE_PULLUP;
	pin_config.OpenDrain = PINSEL_PINMODE_NORMAL;

	PINSEL_ConfigPin(&pin_config);
	GPIO_SetDir(PORT_THREE, BLUE_LED, OUTPUT);
	return;

}

void Configurar_GPIOLedVerde(){
	PINSEL_CFG_Type pin_config;

	pin_config.Portnum = PINSEL_PORT_3;
	pin_config.Pinnum  = PINSEL_PIN_25;
	pin_config.Funcnum = PINSEL_FUNC_0;
	pin_config.Pinmode = PINSEL_PINMODE_PULLUP;
	pin_config.OpenDrain = PINSEL_PINMODE_NORMAL;

	PINSEL_ConfigPin(&pin_config);
	GPIO_SetDir(PORT_THREE, GREEN_LED, OUTPUT);
	return;

}

void Configurar_GPIOSwitch(){
	PINSEL_CFG_Type pin_config;

	pin_config.Portnum = PINSEL_PORT_2;
	pin_config.Pinnum  = PINSEL_PIN_10;
	pin_config.Pinmode = PINSEL_PINMODE_PULLUP;
	pin_config.Funcnum = PINSEL_FUNC_1;
	pin_config.OpenDrain = PINSEL_PINMODE_NORMAL;

	PINSEL_ConfigPin(&pin_config);

	Configurar_SwitchInterrupt();

	return;
}

void Prender_LedRojo(){
	GPIO_ClearValue(PORT_ZERO, RED_LED);
	return;
}

void Prender_LedAzul(){
	GPIO_ClearValue(PORT_THREE, BLUE_LED);
	return;
}

void Prender_LedVerde(){
	GPIO_ClearValue(PORT_THREE, GREEN_LED);
	return;
}

void Apagar_LedRojo(){
	GPIO_SetValue(PORT_ZERO, RED_LED);
	return;
}

void Apagar_LedAzul(){
	GPIO_SetValue(PORT_THREE, BLUE_LED);
	return;
}

void Apagar_LedVerde(){
	GPIO_SetValue(PORT_THREE, GREEN_LED);
	return;
}


void Configurar_SwitchInterrupt(){

	EXTI_InitTypeDef external;

	external.EXTI_Line = EXTI_EINT0;
	external.EXTI_Mode = EXTI_MODE_EDGE_SENSITIVE;
	external.EXTI_Polarity = EXTI_POLARITY_LOW_ACTIVE_OR_FALLING_EDGE;

	EXTI_Config(&external);

	NVIC_EnableIRQ(EINT0_IRQn);

	return;

}

/*!
 * @brief Verifica el estado del LED
 * @return Retorna TRUE si esta apagado el LED y FALSE si esta prendido
 */
BOOL_8 Verificar_LED(uint32_t PORT, uint32_t PIN_SELECT){

	if(GPIO_ReadValue(PORT)&PIN_SELECT){
		return TRUE;
	}
	else{
		return FALSE;
	}
}
