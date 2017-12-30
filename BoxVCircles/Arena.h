#ifndef ARENA_H
#define ARENA_H

#include "Player.h"
#include "Colors.h"

class Player;

class Arena {
public:
	Arena(int w, int h);
	//Arena(int w, int h, Player* player);
	~Arena();

	//Mutators
	void setPlayer(Player* player);

	//Accessors
	Player* getPlayer();
	int getHeight();
	int getWidth();
private:
	int m_width;
	int m_height;
	Colors m_colors;
	Player *m_player;
	//Enemy *m_enemies[50];
	//int enemy_count;
	//Camera m_camera;

};

#endif // !ARENA_H
