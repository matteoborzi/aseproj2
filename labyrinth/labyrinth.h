#ifndef _H_LABYRINTH
#define _H_LABYRINTH
/*----------------------------------------------------------------------------
	Here the methods and the functions that modify the status of the game
	are defined, with constants like the map matrix and its dimensions
 *----------------------------------------------------------------------------*/

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

unsigned int rotate(unsigned int);
void run(void);

#endif
