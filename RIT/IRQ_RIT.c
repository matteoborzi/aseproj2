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
	static int select=0;
	//static int position=0;	
	
	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){	
		/* Joytick Select pressed */
		select++;
		switch(select){
			case 1:
				GUI_Text(8,240,(uint8_t*) "SELECT", White, Black, 1);
				//position = 0;
				break;
			default:
				break;
		}
	}
	else{
			select=0;
			Clear_Footer();
	}
	
  LPC_RIT->RICTRL |= 0x1;
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
