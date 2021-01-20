/***************************************** File info *****************************************************
** File name:               main.c
** Descriptions:            Blind Labyrinth v2 main function 
**
**--------------------------------------------------------------------------------------------------------
** Created by:              Matteo Borzi 280104
** Created date:            2021-01-20
** Version:                 v1.0
** Descriptions:            Blind Labyrinth game implemented on Landtiger board
**													with HY32D display module
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"
#include "RIT/RIT.h"
#include "labyrinth/labyrinth.h"

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif

unsigned int game_status = 0;
unsigned int current_mode = 0;

int main(void) {
  SystemInit();
  LCD_Initialization();
	TP_Init();
	init_RIT(0x004C4B40);									
	//init_RIT(0x1312D0);									// Debug purposes
	TouchPanel_Calibrate();
	
	Game_Init();
	
	enable_RIT();
		
	LPC_SC->PCON |= 0x1;									// power-down	mode
	LPC_SC->PCON &= ~(0x2);						
	
  while (1)	
  {
		__ASM("wfi");
  }
}
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
