#include <stdio.h>
#include <allegro.h>

#include "prototypes.h"
#include "animate.h"
#include "levels.h"
#include "draw.h"

void animate(sprite *player, sprite NPC[], gameState *currentState){	
	//function only runs if level is not 0 - player is not on navigation menu
	
	if(currentState->level > 0 && currentState->level <= currentState->numLvls && currentState->won == 0){
		int overlap, doOverlap, npcOverlap;
		
		for(int i = 0; i < currentState->numSprites; i++){
			npcMove(&NPC[i], currentState);
		}
		playerPos(player, currentState);
		overlap = checkOverlap(player, NPC, currentState);
		if(key[KEY_L]){
			overlap = 2;
			rest(100); // this is a hack but for some reason is required...
		}
		//player lost
		if(overlap == 1){
			showSkeleton(player, NPC, currentState);
			if(currentState->lives > 1){
				int placeholder;
				if(currentState->level == 1){
					placeholder = loadLvl1(player, NPC, currentState);
				}
				else if(currentState->level == 2){
					placeholder = loadLvl2(player, NPC, currentState);
				}
				else if(currentState->level == 3){
					placeholder = loadLvl3(player, NPC, currentState);
				}
				currentState->lives = currentState->lives - 1;
			}
			else{
				currentState->level = -1;
				currentState->won = overlap;
				return;
			}
		}
		//player beat level
		else if(overlap == 2){
			currentState->score += calcScore(player, currentState);
			currentState->level++;
			//allegro_message("hi?");

			if(currentState->level == 2){
				int placeholder = loadLvl2(player, NPC, currentState);
			}
			else if(currentState->level == 3){
				int placeholder = loadLvl3(player, NPC, currentState);
			}
			
			if(currentState->level > currentState->numLvls){
				currentState->won = overlap;
				recordScore(currentState->score);
			}
			else{
				currentState->won = 0;
			}
			//allegro_message("score %d; level %d; won %d; numLvls %d", currentState->score, currentState->level, currentState->won, currentState->numLvls);
			return;
		}
		calcGravEffect(player, currentState);
		drawSprites(*player, NPC, currentState);
	}
}

//calculates where the NPC should be in the next frame by adding its x velocity to its x position, and multiplying its 
//x velocity by negative one if the NPC is beyond the limits where it should be walking
void npcMove(sprite *NPC, gameState *currentLevel){
	NPC->x += NPC->xvel;
	if(NPC->x < NPC->llimit || NPC->x + NPC->image->w > NPC->rlimit){
		NPC->xvel *= -1;
	}
}

//takes keyboard input and moves player according to it. Doesn't allow player to press key if they are overlapping with the start
//or end platform.
void playerPos(sprite *player, gameState *currentState){
	if(player->x + player->image->w < currentState->lvlState.end.x || player->y < currentState->lvlState.end.y){
		if(key[KEY_RIGHT]){
			player->x += player->xvel;
		}
	}
	
	if(currentState->lvlState.start.x + currentState->lvlState.start.width < player->x || player->y < currentState->lvlState.start.y){
		if(key[KEY_LEFT]){
			player->x -= player->xvel;
		}
	}
}

//fallspeed and jumpheight are defined in prototypes.h
//calculates the effect gravity has on the player's movement
void calcGravEffect(sprite *player, gameState *currentState){
	if(player->y < currentState->lvlState.floorY){
		player->yvel += .05;//FALL_SPEED;
	}

	else{ // he's on the floor, stop falling
		player->yvel = 0;
			
	// only jump when you are on the floor
		if (key[KEY_UP]){
			player->yvel += JUMP_HEIGHT *-1;
		}
	}

	
	player->y += player->yvel;
}

//checks if player is overlapping with anything, and returns a value based on that overlap
int checkOverlap(sprite *player, sprite NPC[], gameState *currentState){
	int playerBotY = player->y;
	int effectivePlayerX = player->x + WIDTH_OFFSET;
	int effectivePlayerWidth = player->image->w - 2 * WIDTH_OFFSET;
	
	//checks if player is overlapping with a sprite, and determines which sprite that is
	for(int i = 0; i < currentState->numSprites; i++){
		int effectiveNpcX = NPC[i].x + NPC_WIDTH_OFFSET;
		int effectiveNpcWidth = NPC[i].image->w - 2 * NPC_WIDTH_OFFSET;
		if(effectiveNpcX < effectivePlayerX + effectivePlayerWidth && NPC[i].y < player->y && 
				effectivePlayerX <= effectiveNpcX + effectiveNpcWidth) {
			currentState->lvlState.floorY = SCREEN_HEIGHT - NPC[i].image->h;
			player->x += NPC[i].xvel;
			return 0; 
		}
	}
	//checks if player is overlapping with an obstacle
	for(int i = 0; i < currentState->lvlState.numObstacles; i++){
		if(playerBotY > currentState->lvlState.obs[i].y && 
		playerBotY - player->image->h < currentState->lvlState.obs[i].y + currentState->lvlState.obs[i].height&&
		effectivePlayerX + effectivePlayerWidth > currentState->lvlState.obs[i].x && 
		effectivePlayerX < currentState->lvlState.obs[i].x + currentState->lvlState.obs[i].width){
			return 1;
		}
	}
	
	//if player is overlapping with start platform
	if(currentState->lvlState.start.x + currentState->lvlState.start.width >= effectivePlayerX && playerBotY >= currentState->lvlState.start.y){
		currentState->lvlState.floorY = currentState->lvlState.start.y;
		return 0;
	}
	
	//if player is overlapping with ground
	else if(playerBotY >= FLOOR_Y){
		return 1;
	}
	
	//if player is overlapping with end platform
	else if(currentState->lvlState.end.x < effectivePlayerX + effectivePlayerWidth && currentState->lvlState.end.y <= playerBotY){
		return 2;
	}
	//if player is not overlapping with anything
	else{
		//resetting floor location to default
		currentState->lvlState.floorY = FLOOR_Y;
		return -1;
	}
}

//draws all sprites in the correct position corresponding to their x and y locations
void drawSprites(sprite player, sprite NPC[], gameState *currentState){
	BITMAP *buffer = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
	
	if(buffer == NULL){
		allegro_message("buffer did not load in drawSprites");
		return;
	}
		if (player.image == NULL) { allegro_message("player image not loaded");}
	
	blit(currentState->background, buffer, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	draw_sprite(buffer, player.image, player.x, player.y - player.image->h);
	
	for(int i = 0; i < currentState->numSprites; i++){
		draw_sprite(buffer, NPC[i].image, NPC[i].x, NPC[i].y);
	}
	
	blit(buffer, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	
	destroy_bitmap(buffer);
}

int calcScore(sprite *player, gameState *currentState){
	int score = player->x + (currentState->lives * 10);
	return score;
}

void showSkeleton(sprite *player, sprite NPC[], gameState *currentState){
	player->image = load_bitmap("dead.pcx", NULL);
	drawSprites(*player, NPC, currentState);
	rest(500);
}
