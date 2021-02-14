// prototypes.h
#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#include <allegro.h>
#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 600
#define EASY_XVEL 1
#define MID_XVEL 3
#define HARD_XVEL 5
#define WHITE makecol(255, 255, 255)
#define BLACK makecol(0, 0, 0)
#define JUMP_HEIGHT 4
#define FALL_SPEED 0.55
#define FLOOR_Y 600
#define WIDTH_OFFSET 30
#define NPC_WIDTH_OFFSET 25
#define CHOOSE_EXIT 0
#define CHOOSE_SCORE 1
#define CHOOSE_PLAY 2
#define CHOOSE_WELCOME 3

struct sprite{
	BITMAP *image;
	float x;
	float y;
	float xvel;
	float yvel;
	int rlimit;
	int llimit;
};

struct obstacle{
	int x;
	int y;
	int width;
	int height;
};
struct lvlProperties{
	int numObstacles;
	int floorY;
	obstacle start;
	obstacle end;
	obstacle obs[200];
};

struct gameState{
	int level;
	int won;
	int screenChoice;
	int numSprites;
	int lives;
	int score;
	int lvlSetup[10]; // MUST BE GREATER THAN NUMBER OF LEVELS
	int numLvls;
	BITMAP *background;
	FONT *courier;
	PALETTE palette;
	lvlProperties lvlState;
};

int draw(sprite player, sprite NPC[], gameState *currentState);
int animate(sprite player, sprite NPC[], gameState *currentState);

#endif
