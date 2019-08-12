/*
===============================================================================
 Name        : main.c
 Author      : $(Gabriel Valenzuela)
 Version     :
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

// TODO: insert other include files here
#define PORT_ZERO	(uint32_t) 0
#define PORT_THREE	(uint32_t) 3


#define INPUT	(uint8_t) 0
#define OUTPUT	(uint8_t) 1

#define RED_LED		( (uint32_t) (1<<22) )
#define BLUE_LED	( (uint32_t) (1<<26) )
#define GREEN_LED	( (uint32_t) (1<<25) )

FunctionalState Cur_State = ENABLE;

uint8_t contador = 0;

void SysTick_Handler(void);

void Configurar_GPIOLedRojo(void);

void Configurar_GPIOLedAzul(void);

void Configurar_GPIOLedVerde(void);

void Prender_LedRojo(void);

void Prender_LedAzul(void);

void Prender_LedVerde(void);

void Apagar_LedRojo(void);

void Apagar_LedAzul(void);

void Apagar_LedVerde(void);

/*!
 * ********************** Funciones de manejo de interrupciones **********************
 */

void SysTick_Handler(void){
	//100ms
	//100ms * 50 = 5000ms = 5s
	SYSTICK_ClearCounterFlag();

	contador++;

	if(contador<50){
		return;
	}
	else{
		contador = 0;

		// Codigo de error solo prende el LED rojo

		while(1){
			Prender_LedRojo();
		}

		return;
	}
}
// TODO: insert other definitions and declarations here

int main(void) {

	/*!
	 * Acordate que los clear prenden los LEDs y los sets los apaga
	 */

    // TODO: insert code here
	Configurar_GPIOLedRojo();

	Configurar_GPIOLedAzul();

	Configurar_GPIOLedVerde();


	SYSTICK_InternalInit(100);

	SYSTICK_IntCmd(ENABLE);

	SYSTICK_Cmd(ENABLE);
    // Force the counter to be placed into memory
    // Enter an infinite loop, just incrementing a counter
    while(1) {
    }
    return 0 ;
}


void Configurar_GPIOLedRojo(){
	PINSEL_CFG_Type pin_config;

	pin_config.Portnum = PINSEL_PORT_0;
	pin_config.Pinnum  = PINSEL_PIN_22;
	pin_config.Pinmode = PINSEL_PINMODE_PULLUP;
	pin_config.OpenDrain = PINSEL_PINMODE_NORMAL;

	PINSEL_ConfigPin(&pin_config);
	GPIO_SetDir(PORT_ZERO, RED_LED, OUTPUT);
	return;

}

void Configurar_GPIOLedAzul(){
	PINSEL_CFG_Type pin_config;

	pin_config.Portnum = PINSEL_PORT_3;
	pin_config.Pinnum  = PINSEL_PIN_26;
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
	pin_config.Pinmode = PINSEL_PINMODE_PULLUP;
	pin_config.OpenDrain = PINSEL_PINMODE_NORMAL;

	PINSEL_ConfigPin(&pin_config);
	GPIO_SetDir(PORT_THREE, GREEN_LED, OUTPUT);
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
