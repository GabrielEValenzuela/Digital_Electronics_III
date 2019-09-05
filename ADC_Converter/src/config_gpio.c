/*
 * config_gpio.c
 *
 *  Created on: 30 ago. 2019
 *      Author: Gabriel Valenzuela
 */

#include "config_gpio.h"
#include "lpc17xx_pinsel.h"
#include "define.h"
//LED ROJO - P0.18
//LED AMARILLO - P0.17
//LED VERDE - P0.16

#define REDLED 		( (uint32_t) (1<<18) )
#define YELLOWLED 	( (uint32_t) (1<<17) )
#define GREENLED 	( (uint32_t) (1<<16) )
void config_gpio(){
	PINSEL_CFG_Type pin_config;

	pin_config.Portnum = PINSEL_PORT_0;
	pin_config.Pinnum  = PINSEL_PIN_18;
	pin_config.Pinmode = PINSEL_PINMODE_PULLUP;
	pin_config.Funcnum = PINSEL_FUNC_0;
	pin_config.OpenDrain = PINSEL_PINMODE_NORMAL;
	PINSEL_ConfigPin(&pin_config);

	pin_config.Portnum = PINSEL_PORT_0;
	pin_config.Pinnum  = PINSEL_PIN_17;
	pin_config.Pinmode = PINSEL_PINMODE_PULLUP;
	pin_config.Funcnum = PINSEL_FUNC_0;
	pin_config.OpenDrain = PINSEL_PINMODE_NORMAL;
	PINSEL_ConfigPin(&pin_config);

	pin_config.Portnum = PINSEL_PORT_0;
	pin_config.Pinnum  = PINSEL_PIN_16;
	pin_config.Pinmode = PINSEL_PINMODE_PULLUP;
	pin_config.Funcnum = PINSEL_FUNC_0;
	pin_config.OpenDrain = PINSEL_PINMODE_NORMAL;
	PINSEL_ConfigPin(&pin_config);

	GPIO_SetDir(0, REDLED, OUTPUT);
	GPIO_SetDir(0, YELLOWLED, OUTPUT);
	GPIO_SetDir(0, GREENLED, OUTPUT);

	return;
}

void lightOn_greenLED(){
	GPIO_SetValue(0, GREENLED);
}

void lightOn_yellowLED(){
	GPIO_SetValue(0, YELLOWLED);
}

void lightOn_redLED(){
	GPIO_SetValue(0, REDLED);
}

void lightOff_greenLED(){
	GPIO_ClearValue(0, GREENLED);
}

void lightOff_yellowLED(){
	GPIO_ClearValue(0, YELLOWLED);
}

void lightOff_redLED(){
	GPIO_ClearValue(0, REDLED);
}

void lightOff_All(){

	lightOff_greenLED();
	lightOff_yellowLED();
	lightOff_redLED();

}

void toggle_redLED(){

	if(GPIO_ReadValue(0)&REDLED){
		lightOff_redLED();
	}
	else{
		lightOn_redLED();
	}

}
