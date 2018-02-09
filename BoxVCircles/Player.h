#ifndef PLAYER_H
#define PLAYER_H

#include <allegro5\allegro_primitives.h>
#include "Colors.h"
#include "Arena.h"
#include "RectangleCollider.h"
#include <stdio.h>

class Arena;

class Player {
public:
	Player(int sx, int sy, int w, int h, int s);
	//Player(int sx, int sy, int w, int h, int s, Arena* arena);
	void draw() const; //draw player
	
	//Mutators
	void updateKeys(ALLEGRO_EVENT &ev); //Take care of keys
	void updatePosition(); //Take care of physics update
	void changeSpeed(int ns);
	void setArena(Arena* arena);

	//Accessors
	int getWidth() const;
	int getHeight() const;
	int getPosX() const;
	int getPosY() const;
	int getMoveSpeed() const;
	int getCenterX() const;
	int getCenterY() const;
	Arena* getArena() const;

private:
	Arena *m_arena;
	int m_pos_x, m_pos_y;
	int m_width;
	int m_height;
	int m_speed;
	Colors m_colors;
	RectangleCollider m_collider;

	//Variables for moving
	const enum MOVE_KEYS { KEY_UP, KEY_RIGHT, KEY_DOWN, KEY_LEFT };;
	bool keys[4]{}; //initialized as false
};


#endif // !PLAYER_H

