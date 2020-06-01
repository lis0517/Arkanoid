#pragma once

#include <math.h>

class Vector2
{
public:
	static const Vector2 top;
	static const Vector2 left;
	static const Vector2 right;
	static const Vector2 bottom;
public:
	float x, y;
public:
	Vector2();
	Vector2(float x, float y);
	~Vector2();

	float magnitude();
	Vector2 normalisze();
	void Normalized();
	float Dot(const Vector2 &vec) const;
	float Cross(const Vector2 &vec) const;
public:
	Vector2 operator*(float value);
	friend Vector2 operator *(float value, const Vector2 &vec);
	Vector2 operator+(const Vector2 &vec)const;
	Vector2 operator-(const Vector2 &vec)const;
};


