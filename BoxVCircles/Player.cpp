#include "Player.h"

Player::Player(int sx, int sy,int w, int h, int s) {
	m_pos_x = sx;
	m_pos_y = sy;
	m_width = w;
	m_height = h;
	m_speed = s;

	//Allegro stuff TODO: ERROR CHECKING
	al_init_primitives_addon();
	if(! al_is_keyboard_installed())
		al_install_keyboard();
}

//Draw the player
void Player::draw() {
	al_draw_filled_rectangle(m_pos_x, m_pos_y, m_pos_x + m_width, m_pos_y + m_height, al_map_rgb(255,255,255));
}

//Mutators

//Update keys so we know where the player is moving
void Player::updateKeys(ALLEGRO_EVENT &ev) {
	if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
		switch (ev.keyboard.keycode) {
		case ALLEGRO_KEY_DOWN:
			keys[KEY_DOWN] = true;
			break;
		case ALLEGRO_KEY_UP:
			keys[KEY_UP] = true;
			break;
		case ALLEGRO_KEY_RIGHT:
			keys[KEY_RIGHT] = true;
			break;
		case ALLEGRO_KEY_LEFT:
			keys[KEY_LEFT] = true;
			break;
		}
	}
	else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
		switch (ev.keyboard.keycode) {
		case ALLEGRO_KEY_DOWN:
			keys[KEY_DOWN] = false;
			break;
		case ALLEGRO_KEY_UP:
			keys[KEY_UP] = false;
			break;
		case ALLEGRO_KEY_RIGHT:
			keys[KEY_RIGHT] = false;
			break;
		case ALLEGRO_KEY_LEFT:
			keys[KEY_LEFT] = false;
			break;
		}
	}
	else
		return;
}

void Player::updatePosition() {
	if (keys[KEY_UP])
		m_pos_y -= m_speed;
	else if (keys[KEY_DOWN])
		m_pos_y += m_speed;
	if (keys[KEY_RIGHT])
		m_pos_x += m_speed;
	else if (keys[KEY_LEFT])
		m_pos_x -= m_speed;

	//TODO: Remove this piece of code when we have the m_collider
	//START
	if (m_pos_x < 0)
		m_pos_x = 0;
	else if (m_pos_x + m_width > 800)
		m_pos_x = 800 - m_width;
	if (m_pos_y < 0)
		m_pos_y = 0;
	else if (m_pos_y + m_height> 600)
		m_pos_y = 600 - m_height;
	//END
}

void Player::changeSpeed(int ns) {
	m_speed = ns;
}

//Accessors
int Player::getWidth() {
	return m_width;
}
int Player::getHeight() {
	return m_height;
}
int Player::getPosX() {
	return m_pos_x;
}
int Player::getPosY() {
	return m_pos_y;
}
int Player::getMoveSpeed() {
	return m_speed;
}