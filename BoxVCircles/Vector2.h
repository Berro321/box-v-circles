#ifndef VECTOR2_H
#define VECTOR2_H

struct Vector2 {
	int x;
	int y;
	Vector2(int sx, int sy);
	void add(Vector2 V1);
	void subtract(Vector2 V);
	int crossProductZ(Vector2);
};

#endif // !VECTOR2_H

