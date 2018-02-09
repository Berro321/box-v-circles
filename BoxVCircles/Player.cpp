#include "Player.h"


Player::Player(int sx, int sy,int w, int h, int s)
	:m_collider(&m_pos_x, &m_pos_y, &m_width, &m_height)
{
	m_pos_x = sx;
	m_pos_y = sy;
	m_width = w;
	m_height = h;
	m_speed = s;

	m_arena = nullptr;

	//Allegro stuff TODO: ERROR CHECKING
	al_init_primitives_addon();
	if(! al_is_keyboard_installed())
		al_install_keyboard();
}

//Draw the player
void Player::draw() const {
	int offsetedX = m_pos_x  - m_arena->getOffsetX();
	int offsetedY = m_pos_y - m_arena->getOffsetY();

	//Draw it along the offset of the arena
	al_draw_filled_rectangle(offsetedX, offsetedY, offsetedX + m_width, offsetedY + m_height, al_map_rgb(255,255,255));
}

//Mutators

//Update keys so we know where the player is moving
void Player::updateKeys(ALLEGRO_EVENT &ev) {
	if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
		switch (ev.keyboard.keycode) {
		case ALLEGRO_KEY_S:
			keys[KEY_DOWN] = true;
			//keys[KEY_UP] = false;
			break;
		case ALLEGRO_KEY_W:
			keys[KEY_UP] = true;
			//keys[KEY_DOWN] = false;
			break;
		case ALLEGRO_KEY_D:
			keys[KEY_RIGHT] = true;
			//keys[KEY_LEFT] = false;
			break;
		case ALLEGRO_KEY_A:
			keys[KEY_LEFT] = true;
			//keys[KEY_RIGHT] = false;
			break;
		}
	}
	else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
		switch (ev.keyboard.keycode) {
		case ALLEGRO_KEY_S:
			keys[KEY_DOWN] = false;
			break;
		case ALLEGRO_KEY_W:
			keys[KEY_UP] = false;
			break;
		case ALLEGRO_KEY_D:
			keys[KEY_RIGHT] = false;
			break;
		case ALLEGRO_KEY_A:
			keys[KEY_LEFT] = false;
			break;
		}
	}
	else
		return;
}

void Player::updatePosition() {
	//Move based on input
	int inc_pos_y = (-1 * keys[KEY_UP] * m_speed ) + (keys[KEY_DOWN] * m_speed );
	int inc_pos_x = (-1 * keys[KEY_LEFT] * m_speed ) + (keys[KEY_RIGHT] * m_speed );

	float timeToCollision = 1.0f;

	//Check collision against every wall in the arena
	for (int i = 0; i < m_arena->getNumWalls(); i++) {
		RectangleCollider* tempCollider = (*(m_arena->getArenaWalls() + i))->getRectCollider();
		if (tempCollider == nullptr)
			continue;
		float tempColTime = 1.0f;
		if (!m_collider.CollidingTimeWithRect(tempCollider, inc_pos_x, inc_pos_y, tempColTime)) { //no Collision
			//fprintf(stdout, "No Collision\n");
			continue;
		}
		//fprintf(stdout, "%f\n", tempColTime);

		if (tempColTime < timeToCollision)
			timeToCollision = tempColTime;
	}

	//fprintf(stdout, "time to Collision: %f\n", timeToCollision);

	m_pos_x += static_cast<int>(inc_pos_x * timeToCollision);
	m_pos_y += static_cast<int>(inc_pos_y * timeToCollision);
	//fprintf(stdout, "x: %d, y: %d\n", m_pos_x, m_pos_y);

	//TODO: Remove this piece of code when we have the proper m_collider
	//START
	if (m_pos_x < 0)
		m_pos_x = 0;
	else if (m_pos_x + m_width > m_arena->getWidth())
		m_pos_x = m_arena->getWidth() - m_width;
	if (m_pos_y < 0)
		m_pos_y = 0;
	else if (m_pos_y + m_height > m_arena->getHeight())
		m_pos_y = m_arena->getHeight() - m_height;
	//END
}

void Player::changeSpeed(int ns) {
	m_speed = ns;
}

void Player::setArena(Arena* arena) {
	m_arena = arena;
}

//Accessors
int Player::getWidth() const{
	return m_width;
}
int Player::getHeight() const{
	return m_height;
}
int Player::getPosX() const{
	return m_pos_x;
}
int Player::getPosY() const{
	return m_pos_y;
}
int Player::getMoveSpeed() const{
	return m_speed;
}
Arena* Player::getArena() const{
	return m_arena;
}

int Player::getCenterX() const{
	return m_pos_x + (m_width / 2);
}

int Player::getCenterY() const {
	return m_pos_y + (m_height / 2);
}