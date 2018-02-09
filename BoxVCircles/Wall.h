#ifndef WALL_H
#define WALL_H

#include "RectangleCollider.h"
#include "Arena.h"
#include <allegro5\allegro_primitives.h>
#include "Colors.h"

class Arena;

class Wall {
public:
	Wall(int sx, int sy, int w, int h, bool isCollideable, Arena * arena);
	void draw() const;

	//Accessors
	RectangleCollider* getRectCollider();
private:
	int m_x;
	int m_y;
	int m_w;
	int m_h;
	bool m_isCollideable;
	Colors color;
	Arena *m_arena;
	RectangleCollider m_collider;
};

#endif // !WALL_H
