#include "Vector2.h"

Vector2::Vector2(int sx, int sy) {
	x = sx;
	y = sy;
}

void Vector2::add(Vector2 V) {
	x += V.x;
	y += V.y;
}

void Vector2::subtract(Vector2 V) {
	x -= V.x;
	y -= V.y;
}

int Vector2::crossProductZ(Vector2 V) {
	return x*V.y - y*V.x;
}