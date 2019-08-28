/*
===============================================================================
 Name        : InterrpGPIO.c
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
#include "lpc17xx_gpio.h"
#include "lpc17xx_exti.h"
#include "lpc17xx_pinsel.h"

#define PORT_ZERO	(uint32_t) 0

#define INPUT	(uint8_t) 0
#define OUTPUT	(uint8_t) 1

#define LED		( (uint32_t) (1<<0) )
#define BUZZER	( (uint32_t) (1<<2) )
#define SEGUNDO 1000000

void delay(uint32_t time);

void Configurar_GPIOLed(void);

void Configurar_GPIOBuzzer(void);

void Configurar_GPIOInt(void);

void Prender_Led(void);

void Apagar_Led(void);

void Prender_buzzer(void);

void Apagar_buzzer(void);

void EINT0_IRQHandler(){
	EXTI_ClearEXTIFlag(EXTI_EINT0);

	Prender_Led();
	delay(SEGUNDO);
	Apagar_Led();
	return;

}
void EINT1_IRQHandler(){
	EXTI_ClearEXTIFlag(EXTI_EINT0);
	Prender_buzzer();
	delay(2*SEGUNDO);
	Apagar_buzzer();
	return;
}
int main(void) {

	Configurar_GPIOLed();
	Configurar_GPIOBuzzer();
	Configurar_GPIOInt();

	Apagar_Led();
	Apagar_buzzer();

    while(1) {
    }
    return 0 ;
}

void Configurar_GPIOLed(){
	PINSEL_CFG_Type pin_config;

	pin_config.Portnum = PINSEL_PORT_0;
	pin_config.Pinnum  = PINSEL_PIN_0;
	pin_config.Pinmode = PINSEL_PINMODE_PULLUP;
	pin_config.Funcnum = PINSEL_FUNC_0;
	pin_config.OpenDrain = PINSEL_PINMODE_NORMAL;

	PINSEL_ConfigPin(&pin_config);
	GPIO_SetDir(PORT_ZERO, LED, OUTPUT);
	return;
}

void Configurar_GPIOBuzzer(){
	PINSEL_CFG_Type pin_config;

	pin_config.Portnum = PINSEL_PORT_0;
	pin_config.Pinnum  = PINSEL_PIN_2;
	pin_config.Pinmode = PINSEL_PINMODE_PULLUP;
	pin_config.Funcnum = PINSEL_FUNC_0;
	pin_config.OpenDrain = PINSEL_PINMODE_NORMAL;

	PINSEL_ConfigPin(&pin_config);
	GPIO_SetDir(PORT_ZERO, BUZZER, OUTPUT);
	return;
}

void Configurar_GPIOInt(){
	PINSEL_CFG_Type pin_config;

	pin_config.Portnum = PINSEL_PORT_2;
	pin_config.Pinnum  = PINSEL_PIN_10;
	pin_config.Pinmode = PINSEL_PINMODE_PULLUP;
	pin_config.Funcnum = PINSEL_FUNC_1;
	pin_config.OpenDrain = PINSEL_PINMODE_NORMAL;

	PINSEL_ConfigPin(&pin_config);

	pin_config.Portnum = PINSEL_PORT_2;
	pin_config.Pinnum  = PINSEL_PIN_11;
	pin_config.Pinmode = PINSEL_PINMODE_PULLUP;
	pin_config.Funcnum = PINSEL_FUNC_1;
	pin_config.OpenDrain = PINSEL_PINMODE_NORMAL;

	PINSEL_ConfigPin(&pin_config);

	NVIC_EnableIRQ(EINT0_IRQn);
	NVIC_EnableIRQ(EINT1_IRQn);

	NVIC_SetPriority(EINT0_IRQn, 5);

	NVIC_SetPriority(EINT1_IRQn, 8);

	return;

}
void delay(uint32_t time){
	uint32_t aux = 0;
	for (aux; aux < time; ++aux);
	return;
}

void Prender_Led(){
	GPIO_ClearValue(PORT_ZERO, LED);
	return;
}

void Apagar_Led(){
	GPIO_SetValue(PORT_ZERO, LED);
	return;
}

void Prender_buzzer(){
	GPIO_ClearValue(PORT_ZERO, BUZZER);
	return;
}
void Apagar_buzzer(){
	GPIO_SetValue(PORT_ZERO, BUZZER);
	return;
}
