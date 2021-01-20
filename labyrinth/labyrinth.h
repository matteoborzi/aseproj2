#ifndef _H_LABYRINTH
#define _H_LABYRINTH

/******************************************************************************
**--------------File Info------------------------------------------------------
** File name:			labyrinth.h
**-----------------------------------------------------------------------------
** Created by:			Matteo Borzi 280104
** Created date:		2021-01-20
** Version:					1.3
** Descriptions:		Blind Labyrinth v2 game logic
******************************************************************************/

#define	LENGTH				13
#define	WIDTH 				15
#define	START_X				7
#define	START_Y				7

// Game definitions
enum direction { SOUTH = 0, NORTH, EAST, WEST};
enum mode {EXPLORE = 0, MOVE};

// Game methods
void Game_Init(void);
void Game_Start(void);
void Game_End(void);
void Game_Clear(void);

// Game logic functions
void rotate(unsigned int);
void run(void);
void change_mode(void);

#endif

/******************************************************************************
**                            End Of File
******************************************************************************/
