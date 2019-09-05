/*
 * configdac.c
 *
 *  Created on: Sep 4, 2019
 *      Author: gabrielv
 */

#include "configdac.h"
#include "lpc17xx_dac.h"

void config_dac(){

	DAC_Init(LPC_DAC);

	return;
}


