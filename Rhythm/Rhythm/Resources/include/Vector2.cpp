#include "Vector2.h"
Vector2::Vector2(double x, double y) : x(x), y(y) { }
Vector2::Vector2()
{
	this->x = 0.0;
	this->y = 0.0;
}

#pragma region Addition
Vector2 Vector2::operator+(const Vector2 other) const
{
	Vector2 v;
	v.x = this->x + other.x;
	v.y = this->y + other.y;
	return v;
}

Vector2 &Vector2::operator+=(const Vector2 other)
{
	this->x += other.x;
	this->y += other.y;
	return *this;
}

Vector2 &Vector2::operator+=(const double scalar)
{
	this->x += scalar;
	this->y += scalar;
	return *this;
}
#pragma endregion

#pragma region Substraction
Vector2 Vector2::operator-(const Vector2 other) const
{
	Vector2 v;
	v.x = this->x - other.x;
	v.y = this->y - other.y;
	return v;
}

Vector2 &Vector2::operator-=(const Vector2 other)
{
	this->x -= other.x;
	this->y -= other.y;
	return *this;
}

Vector2 &Vector2::operator-=(const double scalar)
{
	this->x -= scalar;
	this->y -= scalar;
	return *this;
}

#pragma endregion

#pragma region Multiplication
Vector2 Vector2::operator*(const Vector2 other) const
{
	Vector2 v;
	v.x = this->x * other.x;
	v.y = this->y * other.y;
	return v;
}

Vector2 &Vector2::operator*=(const Vector2 other)
{
	this->x *= other.x;
	this->y *= other.y;
	return *this;
}

Vector2 &Vector2::operator*=(const double scalar)
{
	this->x *= scalar;
	this->y *= scalar;
	return *this;
}
#pragma endregion

#pragma region Division
Vector2 Vector2::operator/(const Vector2 other) const
{
	Vector2 v;
	v.x = this->x / other.x;
	v.y = this->y / other.y;
	return v;
}

Vector2 &Vector2::operator/=(const Vector2 other)
{
	this->x /= other.x;
	this->y /= other.y;
	return *this;
}

Vector2 &Vector2::operator/=(const double scalar)
{
	this->x /= scalar;
	this->y /= scalar;
	return *this;
}
#pragma endregion

#pragma region Boolean
bool Vector2::operator==(const Vector2 other) const
{
	return this->x == other.x && this->y == other.y;
}

bool Vector2::operator!=(const Vector2 other) const
{
	return !(*this == other);
}
#pragma endregion