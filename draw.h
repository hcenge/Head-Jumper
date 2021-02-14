#ifndef DRAW_H
#define DRAW_H

#include "prototypes.h"

int drawWelcomeScreen();
void drawMouse(BITMAP *currentScreen);
int getMousePos(int topX, int topY, int width, int height);
int drawScores(gameState *currentState);
int drawLevel(int level);
void saveHighScore(int score);
int drawLevelOne(int levelSetup, sprite player, gameState *currentState);
BITMAP *loadSpriteImage();
void drawLives(gameState *currentState);
int drawExitScreen(int won, gameState *currentState);
void sortScores(int *, int);
void getScores(int *scores, int *numScores);
void recordScore(int newScore);

#endif
