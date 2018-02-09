#ifndef CAMERA_H
#define CAMERA_H

class Player;
class Arena;

class Camera {
public:
	Camera(Arena* arena, Player* focus, int width, int height);
	void Update();
private:
	Player* m_focus;
	Arena* m_arena;
	int m_focus_sx, m_focus_sy;
	int m_width;
	int m_height;
};

#endif // !CAMERA_H
