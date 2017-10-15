/*
 * GlobalFunctions.c
 *
 *  Created on: Sep 27, 2017
 *      Author: Andres Hernandez
 */

#include "GlobalFunctions.h"
#include "MK64F12.h"


void delay(uint32 delay){
	volatile uint32 counter;

	for(counter=delay;counter>0;counter--){
	}
}

