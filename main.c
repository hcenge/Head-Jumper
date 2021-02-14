/*Helen Engelhardt, ICS3U-03, Ms. Cullum, January 13 2017
 * ICS3U Summative Final Project - A simple platform game
 ********************HEAD JUMPER*************************
 * Instructions for play, along with my end of project reflection 
 * and documentation, can be found in the folder "Documentation"
 */
#include <stdio.h>
#include <allegro.h>

#include "animate.h"
#include "draw.h"
#include "prototypes.h"

int draw(sprite *player, sprite NPC[], gameState *currentState);
void animate(sprite *player, sprite NPC[], gameState *currentState);

// timing loop code from wiki.allegro.cc
volatile int ticks=0;
void ticker() {
	ticks++;
}
END_OF_FUNCTION(ticker)
// end of timing loop code

int main(int argc, char **argv){
	allegro_init();
	install_keyboard();
	install_mouse();
	set_color_depth(desktop_color_depth());
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
	
	// timing loop code
	LOCK_VARIABLE(ticks);
	LOCK_FUNCTION(ticker);
	// initialize timer
	install_int(ticker, 10);
	install_int_ex(ticker, BPS_TO_TIMER(100)); // 100 times per second
	// end of timing loop code

	int exit = 1;
	gameState currentState;
		currentState.level = 0;
		currentState.won = 0;
		currentState.screenChoice = CHOOSE_WELCOME;
		currentState.numSprites = 200;
		currentState.lives = 5;
		currentState.score = 0;
		currentState.lvlState.numObstacles = 200;
		currentState.numLvls = 3;

		for(int i = 0; i < currentState.numLvls; i++){
			currentState.lvlSetup[i] = 0;
		}

		currentState.courier = load_font("Courier-New.pcx", currentState.palette, NULL);
		if(!currentState.courier){
			allegro_message("Font not found");
		}
	sprite player;
	sprite NPC[200];


	// game loop; every loop is a frame
	while(!key[KEY_ESC] && exit != 0) {
		while (ticks == 0) {
			rest(1); // rest until a full tick is passed
		}
		while (ticks > 0) {
			int old_ticks = ticks; // store value of volatile 'ticks'
			
			// do the logic of the program here
				if(exit >0){
					if(key[KEY_W]){
						currentState.won = 2;
					}
					animate(&player, NPC, &currentState);
				}
		
			ticks--;
			if (old_ticks <= ticks) { // logic is taking too long, abort and draw a frame
				break;
			}
		}
		// draw stuff
		exit = draw(&player, NPC, &currentState);
	}
	
	// ADD CLEAN UP FUNCTION
	destroy_font(currentState.courier);
	return 0;
}
END_OF_MAIN();

