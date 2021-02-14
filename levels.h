#ifndef LEVELONE_H
#define LEVELONE_H

int loadLvl1(sprite *player, sprite NPC[], gameState *currentState);
void properties1(sprite *player, sprite NpcLvl1[], gameState *currentState);

int loadLvl2(sprite *player, sprite NPC[], gameState *currentState);
void properties2(sprite *player, sprite NPC[], gameState *currentState);

int loadLvl3(sprite *player, sprite NPC[], gameState *currentState);
void properties3(sprite *player, sprite NPC[], gameState *currentState);

void createObject(obstacle *object, int x, int y, int w, int h);
#endif
