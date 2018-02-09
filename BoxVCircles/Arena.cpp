#include "Arena.h"

Arena::Arena(int w, int h) {
	m_width = w;
	m_height = h;
	m_player = nullptr;
	m_offset_x = 0;
	m_offset_y = 0;
	m_wall_count = 0;
}

Arena::~Arena() {
	delete m_player;
}

void Arena::draw() {
	//Draw arena
	al_draw_filled_rectangle(-1*getOffsetX(), -1*getOffsetY(), -1*getOffsetX() + m_width, -1*getOffsetY() + m_height, m_colors.BLUE_VIOLET);
	//Then draw walls
	drawWalls();

	m_player->draw();
}

void Arena::update() {
	//First update the player's position
	m_player->updatePosition();
}

void Arena::drawWalls() {
	for (int i = 0; i < m_wall_count; i++)
		m_walls[i]->draw(); 
}

void Arena::setPlayer(Player* player) {
	m_player = player;
	m_player->setArena(this);
}

void Arena::setOffset(int nx, int ny) {
	m_offset_x = nx;
	m_offset_y = ny;
}

Player* Arena::getPlayer() {
	return m_player;
}
int Arena::getHeight() {
	return m_height;
}
int Arena::getWidth() {
	return m_width;
}

int Arena::getOffsetX() const {
	return m_offset_x;
}
int Arena::getOffsetY() const {
	return m_offset_y;
}

//returns a pointer to the array of wall pointers
Wall** Arena::getArenaWalls() {
	return m_walls;
}

int Arena::getNumWalls() {
	return m_wall_count;
}

void Arena::addWall(int sx, int sy, int w, int h) {
	m_walls[m_wall_count] = new Wall(sx, sy, w, h, true, this);
	m_wall_count++;
}