#ifndef COLORS_H
#define COLORS_H

#include<allegro5\allegro_color.h>

//Colors
struct Colors{
	const ALLEGRO_COLOR WHITE = al_map_rgb(255, 255, 255);
	const ALLEGRO_COLOR BLACK = al_map_rgb(0, 0, 0);
	const ALLEGRO_COLOR BLUE = al_map_rgb(0,0,255);
	const ALLEGRO_COLOR BLUE_VIOLET = al_map_rgb(138, 43, 226);
};
#endif // !COLORS_H
