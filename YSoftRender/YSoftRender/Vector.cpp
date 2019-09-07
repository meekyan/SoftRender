#include "pch.h"
#include "Vector.h"


Vector::Vector()
{
}

float Vector::Length() const
{
	float sq = x * x + y * y + z * z;
	return static_cast<float>(sqrt(sq));
}

//归一化
Vector Vector::Normalize()
{
	float length = Length();
	if (length != 0.0f)
	{
		float inv = 1.0f / length;
		x *= inv;
		y *= inv;
		z *= inv;
	}
	return *this;
}

//点乘
float Vector::Dot(Vector v) const
{
	return x * v.x + y * v.y + z * v.z;
}

//叉乘
Vector Vector::Cross(Vector t) const
{
	float m1 = y * t.z - z * t.y;
	float m2 = z * t.x - x * t.z;
	float m3 = x * t.y - y * t.x;
	return Vector(m1, m2, m3, 0.0f);
}

//v1 == v2 ?
bool Vector::operator==(const Vector& t) const
{
	if (abs(x - t.x) <= 0.000001f
		&& abs(y - t.y) <= 0.000001f
		&& abs(z - t.z) <= 0.000001f
		&& abs(w - t.w) <= 0.000001f)
		return true;
	else
		return false;
}

//v1 = v2 * m
Vector Vector::operator* (const Martix& t) const
{
	return Vector(x*t._00 + y * t._10 + z * t._20 + w * t._30,
		x*t._01 + y * t._11 + z * t._21 + w * t._31,
		x*t._02 + y * t._12 + z * t._22 + w * t._32,
		x*t._03 + y * t._13 + z * t._23 + w * t._33);
}

//分量相乘
Vector Vector::operator*(const Vector& t) const
{
	return Vector(
		x * t.x,
		y * t.y,
		z * t.z,
		w * t.w
	);
}

Vector Vector::operator*(float factor) const
{
	return Vector(
		x * factor,
		y * factor,
		z * factor,
		w
	);
}

//v1 = v2 + v3
Vector Vector::operator+(const Vector& t) const
{
	return Vector(x + t.x, y + t.y, z + t.z, 0.0f);
}

//v1 = v2 - v3
Vector Vector::operator-(const Vector& t) const
{
	return Vector(x - t.x, y - t.y, z - t.z, 0.0f);
}

Vector Vector::operator-() const
{
	return Vector(-x, -y - z, w);
}