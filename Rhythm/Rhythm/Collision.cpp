#include "Collision.h"
#include <cmath>

Collision::Collision()
{
	this->a = 0;
	this->b = 0;
	this->sum = 0;
	this->__collision_sum = false;
}

bool Collision::CircleCollision(double x1, double y1, double r1, double x2, double y2, double r2)
{
	a = x2 - x1;
	b = y2 - y1;
	sum = sqrt((a * a) + (b * b));

	if (sum <= r1 + r2) {
		this->__collision_sum = true;
	}
	else {
		this->__collision_sum = false;
	}

	return this->__collision_sum;
}

bool Collision::CircleCollision(double x1, double y1, double r1, double x2, double y2, double r2, double *Distance)
{
	a = x2 - x1;
	b = y2 - y1;
	sum = sqrt((a * a) + (b * b));

	if (sum <= r1 + r2) {
		this->__collision_sum = true;
	}
	else {
		this->__collision_sum = false;
	}

	*Distance = sum;
	return this->__collision_sum;
}

bool Collision::BoxCollision(double ax1, double ax2, double ay1, double ay2, double bx1, double bx2, double by1, double by2)
{
	if (bx1 < ax2 && ax1 < bx2 &&
		by1 < ay2 && ay1 < by2) {
		this->__collision_sum = true;
	}
	else {
		this->__collision_sum = false;
	}

	return this->__collision_sum;
}