#include "Vector3.h"

Vector3::Vector3(double x, double y, double z) : x(x), y(y), z(z) {}
Vector3::Vector3()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

#pragma region Addition
Vector3 Vector3::operator+(const Vector3 other) const
{
	Vector3 v;
	v.x = this->x + other.x;
	v.y = this->y + other.y;
	v.z = this->z + other.z;
	return v;
}

Vector3 &Vector3::operator+=(const Vector3 other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	return *this;
}

Vector3 &Vector3::operator+=(const double scalar)
{
	this->x += scalar;
	this->y += scalar;
	this->z += scalar;
	return *this;
}
#pragma endregion

#pragma region Subtraction
Vector3 Vector3::operator-(const Vector3 other) const
{
	Vector3 v;
	v.x = this->x + other.x;
	v.y = this->y + other.y;
	v.z = this->z + other.z;
	return v;
}

Vector3 &Vector3::operator-=(const Vector3 other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	return *this;
}

Vector3 &Vector3::operator-=(const double scalar)
{
	this->x -= scalar;
	this->y -= scalar;
	this->z -= scalar;
	return *this;
}
#pragma endregion

#pragma region Multiplication
Vector3 Vector3::operator*(const Vector3 other) const
{
	Vector3 v;
	v.x = this->x * other.x;
	v.y = this->y * other.y;
	v.z = this->z * other.z;
	return v;
}

Vector3 &Vector3::operator*=(const Vector3 other)
{
	this->x *= other.x;
	this->y *= other.y;
	this->z *= other.z;
	return *this;
}
Vector3 &Vector3::operator*=(const double scalar)
{
	this->x *= scalar;
	this->y *= scalar;
	this->z *= scalar;
	return *this;
}
#pragma endregion

#pragma region Division
Vector3 Vector3::operator/(const Vector3 other) const
{
	Vector3 v;
	v.x = this->x / other.x;
	v.y = this->y / other.y;
	v.z = this->z / other.z;
	return v;
}

Vector3 &Vector3::operator/=(const Vector3 other)
{
	this->x /= other.x;
	this->y /= other.y;
	this->z /= other.z;
	return *this;
}

Vector3 &Vector3::operator/=(const double scalar)
{
	this->x /= scalar;
	this->y /= scalar;
	this->z /= scalar;
	return *this;
}
#pragma endregion

#pragma region Boolean
bool Vector3::operator==(const Vector3 other) const
{
	return this->x == other.x && this->y == other.y && this->z == other.z;
}

bool Vector3::operator!=(const Vector3 other) const
{
	return !(*this == other);
}
#pragma endregion
