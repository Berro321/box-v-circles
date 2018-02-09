#include "Wall.h"

Wall::Wall(int sx, int sy, int w, int h, bool isCollideable, Arena* arena) 
	:m_collider(&m_x, &m_y, &m_w, &m_h)
{
	//Wall position relative to Arena
	m_x = sx;
	m_y = sy;
	m_w = w;
	m_h = h;
	m_isCollideable = isCollideable;
	m_arena = arena;
}

void Wall::draw() const{
	int offsetedX = m_x - m_arena->getOffsetX(),
		offsetedY = m_y - m_arena->getOffsetY();
	//draw the wall offsetted based on focus
	al_draw_filled_rectangle(offsetedX, offsetedY, offsetedX + m_w, offsetedY + m_h, color.BLUE);
	//fprintf(stdout, "Wall: x: %d, y: %d\n", m_x, m_y);
}

RectangleCollider* Wall::getRectCollider(){
	//return nothing if the object is non_collideable
	return ((m_isCollideable) ? &m_collider : nullptr);
}