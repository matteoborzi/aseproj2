/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2021-01-20
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../labyrinth/labyrinth.h"
#include "../GLCD/GLCD.h"
#include "../TouchPanel/TouchPanel.h"


enum directions {SEL=0, DOWN, LEFT, RIGHT, UP};
unsigned int pins[5] = {0x1, 0x2, 0x4, 0x8, 0x10};

extern unsigned int game_status;
extern unsigned int current_mode;

extern unsigned int x;
extern unsigned int y;
extern unsigned int current_direction;


/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:	None
**
******************************************************************************/

void RIT_IRQHandler (void) {	
	static unsigned int pressed[5] = {0,0,0,0,0};
	static unsigned int clear = 0;
	static unsigned int reset = 0;
	static unsigned int start = 0;
	
	unsigned int regValue;	

	// Joystick section -------------------------------------------------------------
	if(game_status == 1) {
		regValue = LPC_GPIO1->FIOPIN ;
		regValue = (regValue >> 25) & 0x1F;

		// Joytick SELECT pressed	
		if(regValue == 31 - pins[SEL]){	
			pressed[SEL]++;
			switch(pressed[SEL]){
				case 1:
					change_mode();
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
					rotate(NORTH);
					break;
				case 20:
					if(current_mode == MOVE){
						run();
						pressed[UP] = 0;
					}
					break;
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
					rotate(SOUTH);
					break;
				case 20:
					if(current_mode == MOVE){
						run();
						pressed[DOWN] = 0;
					}
					break;
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
					rotate(WEST);
					break;
				case 20:
					if(current_mode == MOVE){
						run();
						pressed[LEFT] = 0;
					}
					break;
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
					rotate(EAST);
					break;
				case 20:
					if(current_mode == MOVE){
						run();
						pressed[RIGHT] = 0;
					}
					break;
				default:
					break;
			}
		} else {
				pressed[RIGHT]=0;
		}
	}	

	// Touch Panel section -------------------------------------------------------------
	getDisplayPoint(&display, Read_Ads7846(), &matrix ) ;
	#ifdef SIMULATOR
		if(display.x <= 240 && display.x > 0 && display.y < 0x013D){
	#else
		if(display.x <= 240 && display.x > 0 && display.y != 0){
	#endif
			
			// New game touch area
			if(display.y >40 && display.y < 208 && game_status == 0){
				start++;
				if(start%2==0){
					Game_Start();
				}
				
			// Clear button
			} else if(display.x >=8 && display.x<=112 && display.y >=260 && display.y <=304 && game_status == 1){
				clear++;
				if(clear%5==0){	
					Game_Clear();
				}
				
			// Restart button
			} else if(display.x >=128 && display.x<=232 && display.y >=260 && display.y <=304){
				reset++;
				if(reset%5==0){
					Game_Init();
				}
			}
			
		} else {
		reset = 0;
		start = 0;
		clear = 0;
	}
	
  LPC_RIT->RICTRL |= 0x1;
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
