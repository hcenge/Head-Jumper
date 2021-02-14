#ifndef ANIMATE_H
#define ANIMATE_H

#include "prototypes.h"

void npcMove(sprite *NPC, gameState *currentState);
void playerPos(sprite *player, gameState *currentState);
void calcGravEffect(sprite *player, gameState *currentState);
int checkOverlap(sprite *player, sprite NPC[], gameState *currentState);
void drawSprites(sprite player, sprite NPC[], gameState *currentState);
int calcScore(sprite *player, gameState *currentState);
void showSkeleton(sprite *player, sprite NPC[], gameState *currentState);

#endif
