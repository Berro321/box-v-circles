#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

//Constants
const int FPS = 60;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char **argv) {
	//Variables
	ALLEGRO_DISPLAY *display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	ALLEGRO_FONT *font = al_create_builtin_font();


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

	//Game loop
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "HI!");
	al_flip_display();
	al_rest(2.0);
	al_destroy_display(display);
	return 0;

}