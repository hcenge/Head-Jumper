#include <allegro.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#include "prototypes.h"
#include "draw.h"
#include "levels.h"

int draw(sprite *player, sprite NPC[], gameState *currentState){	
	//int won = 0 if player has not yet won or lost, 1 if player won, 2 if player lost
	if(currentState->won == 0){
		if(currentState->level == 0){
			// draw the right screen
			int newChoice;
			switch (currentState->screenChoice) {
				case CHOOSE_WELCOME :
					newChoice = drawWelcomeScreen();
					if (newChoice != -1) currentState->screenChoice = newChoice;
					break;
				case CHOOSE_EXIT :
					return 0;
					break;
				case CHOOSE_PLAY :
				
					for(int i = 0; i < currentState->numLvls; i++){
						currentState->lvlSetup[i] = 0;
					}
					currentState->level = 1;	
					break;
				case CHOOSE_SCORE :
					newChoice = drawScores(currentState);
					if (newChoice != -1) currentState->screenChoice = newChoice;
					break;
				default :
					break;
			}
		}
		if(currentState->level == 1){
			if(currentState->lvlSetup[0] == 0){
				currentState->lvlSetup[0] = loadLvl1(player, NPC, currentState);
			}
			drawLives(currentState);
		}
		if(currentState->level == 2){
			if(currentState->lvlSetup[1] == 0){
				currentState->lvlSetup[1] = loadLvl2(player, NPC, currentState);
			}
			drawLives(currentState);
		}
		if(currentState->level == 3){
			if(currentState->lvlSetup[2] == 0){
				currentState->lvlSetup[2] = loadLvl3(player, NPC, currentState);
			}
			drawLives(currentState);
		}
	}
	else {
		int newChoice;
		newChoice = drawExitScreen(currentState->won, currentState);
		if (newChoice != -1 ) {
			// we have a new choice and we are back to basics
			currentState->screenChoice = newChoice;
			currentState->won = 0;
			currentState->level = 0;
			currentState->lives = 5;
			for(int i = 0; i < currentState->numLvls; i++){
				currentState->lvlSetup[i] = 0;
			}
		}
	}
	return 1;
}


//draws the screen a user will see when they first start the game- returns int 0 - quit, 
//1 - continue to game, 2 - show high score, -1 for any other key
int drawWelcomeScreen(){
	BITMAP *welcome = load_bitmap("welcome.pcx", NULL);
	int buttonWidth = 165, buttonHeight = 55;
	
	if(welcome == NULL){
		allegro_message("Image failed to load");
		return 0;
	}
	
	//draws mouse to screen
	poll_mouse();
	drawMouse(welcome);

	blit(welcome, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	if(getMousePos(151, 145, buttonWidth, buttonHeight) == 0){
		//quit game, top corner of button at 151, 145
		destroy_bitmap(welcome);
		return CHOOSE_EXIT;
	}
	else if(getMousePos(583, 145, buttonWidth, buttonHeight) == 0){
		//play game, top corner of button at 583, 145
		destroy_bitmap(welcome);
		return CHOOSE_PLAY;
	}
	else if(getMousePos(367, 145, buttonWidth, buttonHeight) == 0){
		//high scores, top corner of button at 367, 145
		destroy_bitmap(welcome);
		return CHOOSE_SCORE;
	}
	destroy_bitmap(welcome);
	return -1;
}

//draws the mouse pointer
void drawMouse(BITMAP *currentScreen){
	BITMAP *mouse = load_bitmap("mouse.pcx", NULL);
	if(mouse == NULL){
		allegro_message("Image failed to load");
	}
	
	if((mouse_x > 0 || mouse_x < SCREEN_WIDTH) && (mouse_y > 0 || mouse_y < SCREEN_HEIGHT)){
		draw_sprite(currentScreen, mouse, mouse_x, mouse_y);
	}
	
	destroy_bitmap(mouse);
}

//gets the mouse position of a player and determines if the player has clicked on something.
int getMousePos(int topX, int topY, int width, int height){
	if(mouse_b & 1){
		if((mouse_x > topX && mouse_x < topX + width) && (mouse_y > topY && mouse_y < topY + height)){
			return 0;
		}
	}
	return 1;
}

//displays previous high scores from a text file, returns int 0 - quit, int 1 - return to main menu
int drawScores(gameState *currentState){
	if (currentState->background != NULL) {
		destroy_bitmap(currentState->background);
	}
	currentState->background = load_bitmap("highscores.pcx", NULL);
	
	int buttonWidth = 200, buttonHeight = 100, buttonY = 420, textY = 200;
	
	int scores[7];
	int numScores=0;
	
	getScores(scores, &numScores);
	
	// sort scores
	sortScores(scores, numScores);		
	
	// copy scores to background
	if(numScores > 6) numScores = 6;
	for(int i = 0; i < numScores; i++){
		char scoreStr[10]; // declare string
		sprintf(scoreStr, "%d", scores[i]); // format score for printing
		textout_centre_ex(currentState->background, currentState->courier, scoreStr, SCREEN_WIDTH/2, textY + i*30, WHITE, -1 );
	}
	
	poll_mouse();
	drawMouse(currentState->background);
	
	blit(currentState->background, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	
	//code to get mouse position and return a value
	if(getMousePos(75, buttonY, buttonWidth, buttonHeight) == 0){
		return CHOOSE_EXIT;
	}
	else if(getMousePos(350, buttonY, buttonWidth, buttonHeight) == 0){
		return CHOOSE_WELCOME;
		//return CHOOSE_EXIT;
	}
	else if(getMousePos(625, buttonY, buttonWidth, buttonHeight) == 0){
		return CHOOSE_PLAY;
	}
	return -1;
}

//draws an exit screen that shows whether the player won or lost, and has three options to choose from.
//Returns  0 - exit, 1 - show high scores, 2 - play again from start
int drawExitScreen(int won, gameState *currentState){
	int buttonWidth = 200, buttonHeight = 100, buttonY = 356;
		//initialising font
	
	if(won == 1){ // you lost
		BITMAP *lost = load_bitmap("lost.pcx", NULL);
		if(lost == NULL) allegro_message("lost not loaded");
		blit(lost, currentState->background, 0, 0, 0, 0, lost->w, lost->h);
		destroy_bitmap(lost);
	}
	else if(won == 2){ // you won
		BITMAP *pcWon = load_bitmap("won.pcx", NULL);
		if(pcWon == NULL) allegro_message("won not loaded");
		blit(pcWon, currentState->background, 0, 0, 0, 0, pcWon->w, pcWon->h);
		textprintf_centre_ex(currentState->background, currentState->courier, SCREEN_WIDTH/2, 200, WHITE, -1, 
			"Your score: %d", currentState->score); 
		destroy_bitmap(pcWon);
	}
	
	poll_mouse();
	drawMouse(currentState->background);
	
	blit(currentState->background, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	if(getMousePos(75, buttonY, buttonWidth, buttonHeight) == 0){
		return 0;
	}
	if(getMousePos(350, buttonY, buttonWidth, buttonHeight) == 0){
		return 1;
	}
	if(getMousePos(625, buttonY, buttonWidth, buttonHeight) == 0) {
		return 2;
	}

	return -1;
}

//draws the heart symbols to signify how many lives the player has.
void drawLives(gameState *currentState){
	BITMAP *heart = load_bitmap("heart.pcx", NULL);
	int heartX = 125;
	
	if(heart == NULL) allegro_message("life indicator images not loaded");
	textout_ex(currentState->background, currentState->courier, "Lives:", 15, 10, WHITE, -1);
	for(int i = 0; i < currentState->lives; i++){
		draw_sprite(currentState->background, heart, heartX, 15);
		heartX += heart->w + 5;
	}
	destroy_bitmap(heart);
}

// bubble sort based on http://www.programmingsimplified.com/c/source-code/c-program-bubble-sort
// I used this in a previous ICS3U project
void sortScores(int scores[], int numScores){
  int c, d;
  int tempScore;
 
  for (c = 0 ; c < (numScores - 1 ); c++){
    for (d = 0 ; d < numScores - c - 1; d++){
      if (scores[d] < scores[d+1]) {
        //swapping
        tempScore = scores[d];
        scores[d] = scores[d+1];
        scores[d+1] = tempScore;
      }
    }
  }
}

void getScores(int scores[], int *numScores) {
	scores[*numScores];
	FILE *scoreFile = fopen("highscores.txt", "r");
	if(scoreFile == NULL) allegro_message("scoreFile not loaded");

	// read scores from file
	int score = 0;
	while(fscanf(scoreFile, "%d", &score) != EOF){
		scores[*numScores] = score;
		(*numScores)++;
		if ( *numScores > 6) break;
	}
	fclose(scoreFile);
}

void recordScore(int newScore){
	int numScores = 0;
	int scores[8];
	getScores(scores, &numScores);
	scores[numScores] = newScore;
	sortScores(scores, numScores+1);
	
	// write first 6 to file
	FILE *scoreFile = fopen("highscores.txt", "w");
	for(int i = 0; i < 6; i++) {
		fprintf(scoreFile, "%d\n", scores[i]);
	}
	fclose(scoreFile);
	
}

