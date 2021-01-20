/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2021-01-12
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

void RIT_IRQHandler (void)
{	
	static unsigned int pressed[5] = {0,0,0,0,0};
	static unsigned int distance = 0;
	static unsigned int clear = 0;
	static unsigned int reset = 0;
	static unsigned int start = 0;
	
	unsigned int regValue;	

	if(game_status == 1) {
		regValue = LPC_GPIO1->FIOPIN ;
		regValue = (regValue >> 25) & 0x1F;

		// Joytick SELECT pressed	
		if(regValue == 31 - pins[SEL]){	
			pressed[SEL]++;
			switch(pressed[SEL]){
				case 1:
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
					distance = rotate(NORTH);
					Print_Player(x,y,NORTH,0);
					if(distance <=6){
						Print_Wall(x,y-distance);
					}
					break;
				case 20:
					if(distance > 0xFF){
						distance -= 0xFF;
					}
					if(distance > 1) {
						Remove_Player(x,y,White);
						run();
						Print_Player(x,y, NORTH,0);
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
					distance = rotate(SOUTH);
					Print_Player(x,y, SOUTH,0);
					if(distance <=6){
						Print_Wall(x,y+distance);
					}
					break;
				case 20:
					if(distance > 0xFF){
						distance -= 0xFF;
					}
					if(distance > 1) {
						Remove_Player(x,y,White);
						run();
						Print_Player(x,y, SOUTH,0);
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
					distance = rotate(WEST);
					Print_Player(x,y, WEST,0);
					if(distance <=6){
						Print_Wall(x-distance,y);
					}
					break;
				case 20:
					if(distance > 0xFF){
						distance -= 0xFF;
					}
					if(distance > 1) {
						Remove_Player(x,y,White);
						run();
						Print_Player(x,y, WEST,0);
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
					distance = rotate(EAST);
					Print_Player(x,y, EAST,0);
					if(distance <=6){
						Print_Wall(x+distance,y);
					}
					break;
				case 20:
					if(distance > 0xFF){
						distance -= 0xFF;
					}
					if(distance > 1) {
						Remove_Player(x,y,White);
						run();
						Print_Player(x,y,EAST,0);
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

	// Touch Panel section
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
						game_status = 1;
						PrintMap(240,208,40,White);
						Print_Player(7,7,SOUTH,0);
					}
				
			// Clear button
			} else if(display.x >=8 && display.x<=112 && display.y >=260 && display.y <=304 && game_status == 1){
				clear++;
				if(clear%5==0){	
					PrintMap(240,208,40,White);
					Print_Player(x,y,current_direction,current_mode);
				}
				
			// Restart button
			} else if(display.x >=128 && display.x<=232 && display.y >=260 && display.y <=304){
				reset++;
				if(reset%5==0){
					game_status = 0;
					PrintMap(240,208,40,White);
					GUI_Text(8,96, (uint8_t *) "Touch here", Black, White, 3);
					GUI_Text(32,144, (uint8_t *) "to start", Black, White, 3);
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
