#include "vector2.h"

const Vector2 Vector2::top = { 0,-1 };
const Vector2 Vector2::left = { -1,0 };
const Vector2 Vector2::right = { 1,0 };
const Vector2 Vector2::bottom = { 0,1 };

Vector2::Vector2(){}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2::~Vector2(){}

//벡터의 크기 공식
float Vector2::magnitude()
{
	return sqrt((x*x) + (y*y));
}

//단위벡터 반환
Vector2 Vector2::normalisze()
{
	float length = sqrt((x*x) + (y*y));
	return Vector2(x / length, y / length);
}

//단위벡터화 시킴
void Vector2::Normalized()
{
	float length = sqrt((x*x) + (y*y));
	x /= length;
	y /= length;
}

//내적
float Vector2::Dot(const Vector2 & vec) const
{
	return x * vec.x + y*vec.y;
}

//외적
float Vector2::Cross(const Vector2 &vec)const
{
	return (x * vec.y) - (y * vec.x);
}

//연산자 오버로딩
Vector2 Vector2::operator*(float value)
{
	return Vector2(x*value, y*value);
}

Vector2 Vector2::operator+(const Vector2 & vec) const
{
	return Vector2(x + vec.x, y + vec.y);
}

Vector2 Vector2::operator-(const Vector2 & vec) const
{
	return Vector2(x - vec.x, y - vec.y);
}

Vector2 operator*(float value, const Vector2 & vec)
{
	return Vector2(vec.x * value, vec.y *value);
}
