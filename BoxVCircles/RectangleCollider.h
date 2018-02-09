#ifndef RECTANGLECOLLIDER_H
#define RECTANGLECOLLIDER_H


class RectangleCollider {
public:
	//RectangleCollider(int *sx, int *sy, int *w, int *h, int *speed_y, int *speed_x);
	RectangleCollider(int *sx, int *sy, int *w, int *h); //For static colliders
	int CollidingTimeWithRect(const RectangleCollider* Other, int cur_speed_x, int cur_speed_y, float &col_time) const;
	//float CollidingTimeWithCircle(CircleCollider Other);

private:
	//All are pointers since they are bound to one object and use their
	//properties to 
	int *m_x;
	int *m_y;
	int *m_height;
	int *m_width;
	//int *m_speed_x;
	//int *m_speed_y;

	//helper functions
	bool intersectRect(const RectangleCollider* Other) const;
};

#endif // !RECTANGLECOLLIDER_H
