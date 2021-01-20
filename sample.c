/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"
#include "timer/timer.h"
#include "RIT/RIT.h"
#include "labyrinth/labyrinth.h"

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif

unsigned int game_status = 0;
unsigned int current_mode = 0;

int main(void)
{

  SystemInit();
  LCD_Initialization();
	TP_Init();
	//init_RIT(0x004C4B40);									
	init_RIT(0x1312D0);
	TouchPanel_Calibrate();
	
	LCD_Clear(Black);
	GUI_Text(16,4, (uint8_t *) "Blind Labyrinth", Yellow, Black, 2);
		
	PrintMap(240,208,40,White);
	
	Print_Button(8,260,44,104,(uint8_t*) "Clear",Yellow, Black,16,6);
	Print_Button(128,260,44,104, (uint8_t*) "Restart", Yellow, Black,2,6);
	GUI_Text(8,96, (uint8_t *) "Touch here", Black, White, 3);
	GUI_Text(32,144, (uint8_t *) "to start", Black, White, 3);

	enable_RIT();

/*
	LCD_DrawLine(8,260,112,260,Yellow);
	LCD_DrawLine(8,260,8,304,Yellow);
	LCD_DrawLine(112,260,112,304,Yellow);
	LCD_DrawLine(8,304,112,304,Yellow);
	GUI_Text(24,266, (uint8_t*) "Clear",Yellow, Black,2);
	
	LCD_DrawLine(128,260,232,260,Yellow);
	LCD_DrawLine(128,260,128,304,Yellow);
	LCD_DrawLine(232,260,232,304,Yellow);
	LCD_DrawLine(128,304,232,304,Yellow);
	GUI_Text(130,266, (uint8_t*) "Restart",Yellow, Black,2);
*/
		
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
