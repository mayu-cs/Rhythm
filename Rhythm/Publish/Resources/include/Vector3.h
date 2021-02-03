#pragma once
class Vector3
{
public:
	double x;
	double y;
	double z;

public:
	//Constructor
	Vector3();
	Vector3(double x, double y, double z);

#pragma region Arithmetic
	//addition
	Vector3 operator + (const Vector3 other) const;
	Vector3 &operator += (const Vector3 other);
	Vector3 &operator += (const double scalar);

	//subtraction
	Vector3 operator - (const Vector3 other) const;
	Vector3 &operator -= (const Vector3 other);
	Vector3 &operator -= (const double scalar);

	//multiplication
	Vector3 operator * (const Vector3 other) const;
	Vector3 &operator *= (const Vector3 other);
	Vector3 &operator *= (const double scalar);

	//division
	Vector3 operator / (const Vector3 other) const;
	Vector3 &operator /= (const Vector3 other);
	Vector3 &operator /= (const double scalar);
#pragma endregion

#pragma region Boolean
	//equal
	bool operator == (const Vector3 other) const;

	//not equal
	bool operator != (const Vector3 other) const;
#pragma endregion
};

