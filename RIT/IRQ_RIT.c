/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2021-01-12
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../GLCD/GLCD.h"

enum directions {SEL=0, DOWN, LEFT, RIGHT, UP};
unsigned int pins[5] = {0x1, 0x2, 0x4, 0x8, 0x10};

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:	None
**
******************************************************************************/

void RIT_IRQHandler (void)
{	
	static int pressed[5] = {0,0,0,0,0};
	unsigned int p = LPC_GPIO1->FIOPIN ;
	unsigned int regValue = (p >> 25) & 0x1F;
	
	// Joytick SELECT pressed	
	if(regValue == 31 - pins[SEL]){	
		pressed[SEL]++;
		switch(pressed[SEL]){
			case 1:
			Clear_Footer();
			GUI_Text(8,256,(uint8_t*) "SELECT", White, Black, 1);
				break;
			default:
				break;
		}
	} else {
			pressed[SEL]=0;
	}
	
	// Joytick UP pressed	
	if(regValue == 31 - pins[UP]){	
		pressed[UP]++;
		switch(pressed[UP]){
			case 1:
				Clear_Footer();
				GUI_Text(8,256,(uint8_t*) "UP", White, Black, 1);
				break;
			case 20:
				GUI_Text(8,272, (uint8_t*) "Step", White, Black, 1);
			default:
				break;
		}
	} else {
			pressed[UP]=0;
	}
	
	// Joytick DOWN pressed	
	if(regValue == 31 - pins[DOWN]){	
		pressed[DOWN]++;
		switch(pressed[DOWN]){
			case 1:
				Clear_Footer();
				GUI_Text(8,256,(uint8_t*) "DOWN", White, Black, 1);
				break;
			case 20:
				GUI_Text(8,272, (uint8_t*) "Step", White, Black, 1);
			default:
				break;
		}
	} else {
			pressed[DOWN]=0;
	}

	// Joytick LEFT pressed	
	if(regValue == 31 - pins[LEFT]){	
		pressed[LEFT]++;
		switch(pressed[LEFT]){
			case 1:
			Clear_Footer();
			GUI_Text(8,256,(uint8_t*) "LEFT", White, Black, 1);
				break;
			case 20:
				GUI_Text(8,272, (uint8_t*) "Step", White, Black, 1);
			default:
				break;
		}
	} else {
			pressed[LEFT]=0;
	}	

	// Joytick RIGHT pressed	
	if(regValue == 31 - pins[RIGHT]){	
		pressed[RIGHT]++;
		switch(pressed[RIGHT]){
			case 1:
				Clear_Footer();
				GUI_Text(8,256,(uint8_t*) "RIGHT", White, Black, 1);
				break;
			case 20:
				GUI_Text(8,272, (uint8_t*) "Step", White, Black, 1);
			default:
				break;
		}
	} else {
			pressed[RIGHT]=0;
	}
	
	if(regValue == 0x1F){
		Clear_Footer();
	}
	
  LPC_RIT->RICTRL |= 0x1;
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
