#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "Player.h"
#include "Colors.h"
#include "Arena.h"
#include "Wall.h"
#include "Camera.h"

//Constants
const int FPS = 60;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

//Size for now
const int ARENA_WIDTH = 2000;
const int ARENA_HEIGHT = 3000;

/*DONE: 12/29/17
 *	1. MAKE ARENA CLASS
 *  2. MAKE PLAYER CLASS
 *  3. MAKE PLAYABLE DEMO WHERE PLAYER CAN MOVE IN ARENA
 *		IMPLEMENT GAME LOOP + CONTROLS
 *		IMPLEMENT TEMPORARY OUT OF BOUNDS COLLISION
 * 
 * COMPLETED: 2/8/18 
 *	1. MAKE RECTANGLE COLLIDER CLASS
 *		TEST IT ON PLACEHOLDERS (walls)
 *		IMPLEMENT TO PLAYER CLASS
 *	2. MAKE CAMERA CLASS AND ADJUST CODE ACCORDINGLY
	3. MAKE PLAYABLE DEMO WHERE CAMERA FOLLOWS CHARACTER MOVEMENT AROUND AND COLLIDES AGAINST A THICK AND THIN WALLS
 *	3. --(OPT) FIND A BETTER WAY TO STORE COLORS GLOBALLY-- *
 *
 * TODO:
 *  1. MAKE A CIRCLE COLLIDER CLASS
 *		TEST IT ON A RECTANGLE COLLIDER AND ANOTHER CIRCLE COLLIDER
 *	2. ADD A CURSOR TO FOLLOW MOUSE
 *	3.
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
	Arena *arena = new Arena(ARENA_WIDTH, ARENA_HEIGHT);
	//NOTE: Entities in the arena are spawned in a location RELATIVE to arena's position
	//not the screen's
	Player *player = new Player(ARENA_WIDTH / 2, ARENA_HEIGHT / 2, 50, 50, 5);
	arena->setPlayer(player);
	//Creating camera to follow the player
	Camera camera(arena, player, SCREEN_WIDTH, SCREEN_HEIGHT);

	//TEMPORARY WALLS:: REMOVE LATER
	arena->addWall(200, 200, 100, 50);
	arena->addWall(1800, 2500, 10, 50);

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
			arena->update();
			
			//Update camera to view objects in world properly
			camera.Update();

			//Draw to the screen
			al_clear_to_color(colors.BLACK);
			arena->draw();
			al_flip_display();
			redraw = false;

			//Debugging stuff
			fprintf(stdout, "Arena: Offset X: %d, Y: %d\n", arena->getOffsetX(), arena->getOffsetY());
		}

	}

	//Take care of garbage (IT'S GARBAGE DAYYY)
	al_destroy_display(display);
	al_destroy_font(font);
	al_destroy_timer(gameTimer);
	//delete player;
	delete arena;

	return 0;

}