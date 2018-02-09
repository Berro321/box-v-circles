#include "RectangleCollider.h"
#include "Utilities.h"
RectangleCollider::RectangleCollider(int *sx, int *sy, int *w, int *h) {
	//For static colliders (like walls)
	m_x = sx;
	m_y = sy;
	m_width = w;
	m_height = h;
}

/* Calculates and returns at what time along the velocity path the current collider
 * collides with another rectangle collider
 * Returns 1 if there is a collision, 0 if there is none
*/ 
int RectangleCollider::CollidingTimeWithRect(const RectangleCollider *Other, int cur_speed_x, int cur_speed_y, float &col_time) const {
	//MAYBE ADD
	//Sliding motion
	if (Other == nullptr)
		return 0.0; //No actual collider

	//times of first and last contact
	col_time = 0.0f;
	float last_col_time = 1.0f;

	if (cur_speed_y == 0 && (*m_y + *m_height <= *Other->m_y || *m_y >= *Other->m_y + *Other->m_height)) {
		//moving horizontally across => but below or above object
		col_time = 1.0f;
		return 0;
	}else if (cur_speed_x == 0 && (*m_x + *m_width <= *Other->m_x || *m_x >= *Other->m_x + *Other->m_width)) {
		//moving vertically across -> but to the right or left of object
		col_time = 1.0f;
		return 0;
	}
	
	
	//Do the x-axis
	if (cur_speed_x < 0.0f) {
		if (*m_x + *m_width <= *(Other->m_x)) 
			return 0; //no collision
		if (*(Other->m_x) + *(Other->m_width) < *m_x)
			col_time = max( (*(Other->m_x) + *(Other->m_width) - *m_x) / (1.0f * cur_speed_x), col_time); //time of earliest collision
		if (*m_x + *m_width > *(Other->m_x))
			last_col_time = min( (*(Other->m_x) - (*m_x + *m_width))/(1.0f * cur_speed_x),last_col_time); //time of last collision
	}
	if (cur_speed_x > 0.0f) {
		if (*m_x >= *(Other->m_x) + *(Other->m_width))
			return 0; //no collision
		if (*m_x + *m_width < *(Other->m_x))
			col_time = max((*(Other->m_x) - (*m_x + *m_width)) / (1.0f * cur_speed_x), col_time);
		if((*(Other->m_x) + *(Other->m_width)) > *m_x)
			last_col_time = min(((*(Other->m_x) + *(Other->m_width)) - *m_x) / (1.0f * cur_speed_x), last_col_time);
	}
	if (col_time > last_col_time) return 0;

	//Do the y-axis
	if (cur_speed_y < 0.0f) {
		if (*m_y + *m_height <= *(Other->m_y))
			return 0; //no collision
		if (*(Other->m_y) + *(Other->m_height) < *m_y)
			col_time = max((*(Other->m_y) + *(Other->m_height) - *m_y) / (1.0f * cur_speed_y), col_time); //time of earliest collision
		if (*m_y + *m_height > *(Other->m_y))
			last_col_time = min((*(Other->m_y) - (*m_y + *m_height)) / (1.0f * cur_speed_y), last_col_time); //time of last collision
	}
	if (cur_speed_y > 0.0f) {
		if (*m_y >= *(Other->m_y) + *(Other->m_height))
			return 0; //no collision
		if (*m_y + *m_height < *(Other->m_y))
			col_time = max((*(Other->m_y) - (*m_y + *m_height)) / (1.0f * cur_speed_y), col_time);
		if ((*(Other->m_y) + *(Other->m_height)) > *m_y)
			last_col_time = min(((*(Other->m_y) + *(Other->m_height)) - *m_y) / (1.0f * cur_speed_y), last_col_time);
	}
	if (col_time > last_col_time) return 0;
	
	return 1;
}

//Helper

//returns if the two rectangle colliders collide 
bool RectangleCollider::intersectRect(const RectangleCollider* Other) const{
	if (*m_y + *m_height < *Other->m_y || *m_y > *Other->m_y + *Other->m_height ||
		*m_x + *m_width < *Other->m_x || *m_x > *Other->m_x + *Other->m_width)
		return true;
}