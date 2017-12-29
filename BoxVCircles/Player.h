#ifndef PLAYER_H
#define PLAYER_H

#include <allegro5\allegro_primitives.h>
#include "Colors.h"

class Player {
public:
	Player(int sx, int sy, int w, int h, int s);
	void draw();
	
	//Mutators
	void updateKeys(ALLEGRO_EVENT &ev); //Take care of keys
	void updatePosition(); //Take care of physics update
	void changeSpeed(int ns);

	//Accessors
	int getWidth();
	int getHeight();
	int getPosX();
	int getPosY();
	int getMoveSpeed();

private:
	//Arena *m_arena;
	int m_pos_x;
	int m_pos_y;
	int m_width;
	int m_height;
	int m_speed;
	Colors m_colors;
	//TODO: MAKE SQUARE_COLLIDER CLASS
	//Square_Collider *m_collider;

	//Variables for moving
	const enum MOVE_KEYS { KEY_UP, KEY_RIGHT, KEY_DOWN, KEY_LEFT };;
	bool keys[4]{}; //initialized at false
};


#endif // !PLAYER_H

