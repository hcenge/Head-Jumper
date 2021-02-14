#include <stdio.h>
#include <allegro.h>

#include "prototypes.h"
#include "draw.h"
#include "levels.h"

int loadLvl1(sprite *player, sprite NPC[], gameState *currentState){
	currentState->numSprites = 2;
	currentState->score = 0;

	for(int i = 0; i < currentState->numSprites; i++){
		char *npcName = (char *) malloc(10);
		sprintf(npcName, "npc%1d.pcx", i%2);
		NPC[i].image = load_bitmap(npcName, NULL);
		free(npcName);
		if(NPC[i].image == NULL){
			allegro_message("Image nonexistent for NPC %d", i);
		}
	}
	
	player->image = load_bitmap("player.pcx", NULL);
	if(player->image == NULL){
		allegro_message("Image nonexistent for player");
	}
	
	currentState->background = load_bitmap("levelOne.pcx", NULL);
	if(currentState->background == NULL){
		allegro_message("Image nonexistent for background");
	}
	textout_centre_ex(currentState->background, currentState->courier, "< > keys to move, ^ key to jump", SCREEN_WIDTH/2, 150, WHITE, -1);

	properties1(player, NPC, currentState);

	return 1;
}

void properties1(sprite *player, sprite NPC[], gameState *currentState){
	createObject(&currentState->lvlState.start, 0, 410, 90, SCREEN_HEIGHT - 410);
	createObject(&currentState->lvlState.end, 806, 311, SCREEN_WIDTH - 806, SCREEN_HEIGHT - 311);
	currentState->lvlState.numObstacles = 1;
	createObject(&currentState->lvlState.obs[0], 291, 467, 50, SCREEN_HEIGHT - 467);
	
	player->y = currentState->lvlState.start.y;
	player->x = currentState->lvlState.start.x;
	player->xvel = EASY_XVEL;
	player->yvel = 0;
	
	NPC[0].y = SCREEN_HEIGHT - NPC[0].image->h;
	NPC[0].xvel = EASY_XVEL;
	NPC[0].rlimit = currentState->lvlState.obs[0].x;
	NPC[0].llimit = currentState->lvlState.start.width;
	NPC[0].x = NPC[0].llimit;
	
	NPC[1].y = SCREEN_HEIGHT - NPC[1].image->h;
	NPC[1].xvel = EASY_XVEL;
	NPC[1].rlimit = currentState->lvlState.end.x;
	NPC[1].llimit = currentState->lvlState.obs[0].x + currentState->lvlState.obs[0].width;
	NPC[1].x = NPC[1].llimit;
}

int loadLvl2(sprite *player, sprite NPC[], gameState *currentState){
	currentState->numSprites = 2;

	for(int i = 0; i < currentState->numSprites; i++){
		char *npcName = (char *) malloc(10);
		sprintf(npcName, "npc%1d.pcx", i%2);
		NPC[i].image = load_bitmap(npcName, NULL);
		free(npcName);
		if(NPC[i].image == NULL){
			allegro_message("Image nonexistent for NPC %d", i);
		}
	}
	
	player->image = load_bitmap("player.pcx", NULL);
	if(player->image == NULL){
		allegro_message("Image nonexistent for player");
	}
	
	currentState->background = load_bitmap("levelTwo.pcx", NULL);
	if(currentState->background == NULL){
		allegro_message("Image nonexistent for background");
	}

	properties2(player, NPC, currentState);

	return 1;
}

void properties2(sprite *player, sprite NPC[], gameState *currentState){
	createObject(&currentState->lvlState.start, 0, 410, 90, SCREEN_HEIGHT - 410);
	createObject(&currentState->lvlState.end, 680, 484, 94, 116);
	currentState->lvlState.numObstacles = 5;
	
	createObject(&currentState->lvlState.obs[0], 141, 371, 50, 229); //thing 1 bottom
	createObject(&currentState->lvlState.obs[1], 141, 0, 50, 90); //thing one top
	createObject(&currentState->lvlState.obs[2], 417, 467, 50, 133); //middle obstacle
	createObject(&currentState->lvlState.obs[3], 707, 447, 50, 155); //thing 2 bottom
	createObject(&currentState->lvlState.obs[4], 707, 0, 50, 135); //thing 2 top
	
	player->y = currentState->lvlState.start.y;
	player->x = currentState->lvlState.start.x;
	player->xvel = EASY_XVEL;
	player->yvel = 0;
	
	NPC[0].y = SCREEN_HEIGHT - NPC[0].image->h;
	NPC[0].xvel = EASY_XVEL;
	NPC[0].rlimit = currentState->lvlState.obs[2].x;
	NPC[0].llimit = currentState->lvlState.obs[0].x + currentState->lvlState.obs[0].width;
	NPC[0].x = NPC[0].llimit;
	
	NPC[1].y = SCREEN_HEIGHT - NPC[1].image->h;
	NPC[1].xvel = EASY_XVEL;
	NPC[1].rlimit = currentState->lvlState.obs[3].x;
	NPC[1].llimit = currentState->lvlState.obs[2].x + currentState->lvlState.obs[2].width;
	NPC[1].x = NPC[1].llimit;
}

int loadLvl3(sprite *player, sprite NPC[], gameState *currentState){
	currentState->numSprites = 2;

	for(int i = 0; i < currentState->numSprites; i++){
		char *npcName = (char *) malloc(10);
		sprintf(npcName, "npc%1d.pcx", i%2);
		NPC[i].image = load_bitmap(npcName, NULL);
		free(npcName);
		if(NPC[i].image == NULL){
			allegro_message("Image nonexistent for NPC %d", i);
		}
	}
	
	player->image = load_bitmap("player.pcx", NULL);
	if(player->image == NULL){
		allegro_message("Image nonexistent for player");
	}
	
	currentState->background = load_bitmap("levelThree.pcx", NULL);
	if(currentState->background == NULL){
		allegro_message("Image nonexistent for background");
	}

	properties3(player, NPC, currentState);

	return 1;
}

void properties3(sprite *player, sprite NPC[], gameState *currentState){
	createObject(&currentState->lvlState.start, 0, 410, 90, SCREEN_HEIGHT - 410);
	createObject(&currentState->lvlState.end, 806, 311, 94, 289);
	
	currentState->lvlState.numObstacles = 4;
	
	createObject(&currentState->lvlState.obs[0], 196, 0, 50, 273); // first high barrier
	createObject(&currentState->lvlState.obs[1], 383, 371, 50, 133); // barrier at start of elevated floor
	createObject(&currentState->lvlState.obs[2], 579, 0, 50, 155); // second high barrier
	createObject(&currentState->lvlState.obs[3], 383, 484, 442, 116); // elevated floor
	
	player->y = currentState->lvlState.start.y;
	player->x = currentState->lvlState.start.x;
	player->xvel = EASY_XVEL;
	player->yvel = 0;
	
	NPC[0].y = SCREEN_HEIGHT - NPC[0].image->h;
	NPC[0].xvel = EASY_XVEL;
	NPC[0].rlimit = currentState->lvlState.obs[1].x;
	NPC[0].llimit = currentState->lvlState.start.x + currentState->lvlState.start.width;
	NPC[0].x = NPC[0].llimit;
	
	NPC[1].y = currentState->lvlState.obs[3].y - NPC[1].image->h;
	NPC[1].xvel = EASY_XVEL;
	NPC[1].rlimit = currentState->lvlState.end.x;
	NPC[1].llimit = currentState->lvlState.obs[1].x + currentState->lvlState.obs[1].width;
	NPC[1].x = NPC[1].llimit;
}

void createObject(obstacle *object, int x, int y, int w, int h){
	object->x = x;
	object->y = y;
	object->width = w;
	object->height = h;
}
