#pragma once

class Vector2
{
public:
	double x;
	double y;

public:
	//Constructor
	Vector2();
	Vector2(double x, double y);

#pragma region Arithmetic
	//addition
	Vector2 operator + (const Vector2 other) const;
	Vector2 &operator += (const Vector2 other);
	Vector2 &operator += (const double scalar);
	
	//subtraction
	Vector2 operator - (const Vector2 other) const;
	Vector2 &operator -= (const Vector2 other);
	Vector2 &operator -= (const double scalar);

	//multiplication
	Vector2 operator * (const Vector2 other) const;
	Vector2 &operator *= (const Vector2 other);
	Vector2 &operator *= (const double scalar);
	
	//division
	Vector2 operator / (const Vector2 other) const;
	Vector2 &operator /= (const Vector2 other);
	Vector2 &operator /= (const double scalar);
#pragma endregion

#pragma region Boolean
	//equal
	bool operator == (const Vector2 other) const;

	//not equal
	bool operator != (const Vector2 other) const;
#pragma endregion
};