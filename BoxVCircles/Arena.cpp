#include "Arena.h"

Arena::Arena(int w, int h) {
	m_width = w;
	m_height = h;
	m_player = nullptr;
}
/*Arena::Arena(int w, int h, Player* player) {
	Arena(w, h);
	m_player = player;
}*/

Arena::~Arena() {
	delete m_player;
}

void Arena::setPlayer(Player* player) {
	m_player = player;
	m_player->setArena(this);
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