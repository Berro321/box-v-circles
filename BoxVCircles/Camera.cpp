#include "Camera.h"
#include "Arena.h"
#include "Player.h"

Camera::Camera(Arena* arena, Player* focus, int width, int height) {
	m_focus = focus;
	m_width = width;
	m_height = height;
	m_arena = arena;
	m_focus_sx = focus->getCenterX();
	m_focus_sy = focus->getCenterY();
	Update(); //to nitialize offset to focused object
}

//Update camera position to that of the player
//so that the player is in the center of the camera
void Camera::Update() {
	//Change offset of arena so that everything contained in it shifts relative to focus (player)
	int changeX = m_focus->getCenterX() - (m_width / 2);
	int changeY = m_focus->getCenterY() - (m_height / 2);
	m_arena->setOffset(changeX, changeY);
}