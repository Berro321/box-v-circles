#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "Player.h"
#include "Colors.h"
#include "Arena.h"

//Constants
const int FPS = 60;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

/*DONE: 12/29/17
 *	1. MAKE ARENA CLASS
 *  2. MAKE PLAYER CLASS
 *  3. MAKE PLAYABLE DEMO WHERE PLAYER CAN MOVE IN ARENA
 *		IMPLEMENT GAME LOOP + CONTROLS
 *		IMPLEMENT TEMPORARY OUT OF BOUNDS COLLISION
 * 
 * TODO: 12//17
 *	1. (OPT) FIND A BETTER WAY TO STORE COLORS GLOBALLY 
 *	2. MAKE SQUARE AND CIRCLE COLLIDER CLASS
 *	3. MAKE CAMERA CLASS AND ADJUST CODE ACCORDINGLY
*/


int main(int argc, char **argv) {
	//Setup initializations
	if (!al_init()) {
		fprintf(stderr, "Unable to initialize allegro");
		return -1;
	}
	if (!al_init_font_addon()) {
		fprintf(stderr, "Unable to initialize allegro font addon");
		return -1;
	}
	if (!al_init_image_addon()) {
		fprintf(stderr, "Unable to initialize allegro image addon");
		return -1;
	}
	if (!al_init_primitives_addon()) {
		fprintf(stderr, "Unable to initialize allegro primitives addon");
		return -1;
	}

	//ALLEGRO Variables
	ALLEGRO_DISPLAY *display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	ALLEGRO_FONT *font = al_create_builtin_font();
	ALLEGRO_TIMER *gameTimer = al_create_timer(1.0 / FPS);
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	Colors colors; //contains colors

	//GAME Variables
	bool gameOver = false; //Keeps track if game is over
	bool redraw = false; //Draw game

	//Creating arena (May change so it can support multiple levels)
	Arena *arena = new Arena(SCREEN_WIDTH, SCREEN_HEIGHT);
	Player *player = new Player(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 50, 50, 5);
	arena->setPlayer(player);

	//Registering events + setting up controls/timers
	al_install_keyboard();

	al_register_event_source(event_queue, al_get_timer_event_source(gameTimer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(gameTimer);

	//GAME LOOP
	while (!gameOver) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER && ev.timer.source == gameTimer)
			//Every frame, the game should update
			redraw = true;
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN || ALLEGRO_EVENT_KEY_UP) {
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				gameOver = true;
			//Pass to player to update their movement if keyboard press
			arena->getPlayer()->updateKeys(ev);
		}

		if (redraw) {
			//Update Physics
			arena->getPlayer()->updatePosition();
			
			//Draw
			al_clear_to_color(colors.BLACK);
			arena->getPlayer()->draw();
			al_flip_display();
			redraw = false;
		}

	}

	//Take care of garbage (IT'S GARBAGE DAYYY)
	al_destroy_display(display);
	al_destroy_font(font);
	al_destroy_timer(gameTimer);
	delete player;

	return 0;

}