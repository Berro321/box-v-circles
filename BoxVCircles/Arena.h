#ifndef ARENA_H
#define ARENA_H

#include "Player.h"
#include "Colors.h"
#include "Wall.h"

class Player;

class Wall;

class Arena {
public:
	Arena(int w, int h);
	//Arena(int w, int h, Player* player);
	~Arena();
	void draw();
	void update();

	//Mutators
	void setPlayer(Player* player);
	void addWall(int sx, int sy, int w, int h);
	void setOffset(int nx, int ny);
	//Accessors
	Player* getPlayer();
	int getHeight();
	int getWidth();
	int getOffsetX() const;
	int getOffsetY() const;
	Wall** getArenaWalls();
	int getNumWalls();
private:
	int m_width;
	int m_height;
	int m_offset_x;
	int m_offset_y;
	Colors m_colors;
	Player *m_player;

	Wall *m_walls[50];
	int m_wall_count;

	//Helper funcs
	void drawWalls();

	//Enemy *m_enemies[50];
	//int enemy_count;
	//Camera m_camera;

};

#endif // !ARENA_H
