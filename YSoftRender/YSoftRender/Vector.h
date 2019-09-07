#pragma once

#include <cmath>
#include "Martix.h"

class Vector
{
public:
	float x;
	float y;
	float z;
	float w; //0����1��
public:
	Vector() = default;
	Vector(float x1, float y1, float z1, float w1 = 0) :x(x1), y(y1), z(z1), w(w1) {}
	Vector(const Vector& t) :x(t.x), y(t.y), z(t.z), w(t.w) {}
	Vector& operator= (const Vector& t)
	{
		if (this == &t)
			return *this;
		x = t.x;
		y = t.y;
		z = t.z;
		w = t.w;
		return *this;
	}
	//��������
	float Length() const;
	//��һ��
	Vector Normalize();
	//���
	float Dot(Vector v) const;
	//���
	Vector Cross(Vector t) const;
	//����== 
	bool operator==(const Vector& t) const;
	//��任�������
	Vector operator* (const Martix& t) const;
	//��ZCVector�������
	Vector operator* (const Vector& t) const;
	//��float���
	Vector operator*(float factor) const;
	//��
	Vector operator+ (const Vector& t) const;
	//��
	Vector operator- (const Vector& t) const;
	//����
	Vector operator-() const;
};


class FLOAT3
{
public:
	float x;
	float y;
	float z;
public:
	FLOAT3() = default;
	FLOAT3(float r, float b, float g) :x(r), y(b), z(g) {}
	FLOAT3(const FLOAT3& t) :x(t.x), y(t.y), z(t.z) {}
	FLOAT3& operator= (const FLOAT3& t)
	{
		if (this == &t)
			return *this;
		x = t.x;
		y = t.y;
		z = t.z;
		return *this;
	}
};


//��ά������Ҫ���ڱ�ʾ��������
class FLOAT2
{
public:
	float u;
	float v;
public:
	FLOAT2() = default;
	FLOAT2(float x, float y) :u(x), v(y) {}
	FLOAT2(const FLOAT2& t) :u(t.u), v(t.v) {}
	FLOAT2& operator= (const FLOAT2& t)
	{
		if (this == &t)
			return *this;
		u = t.u;
		v = t.v;
		return *this;
	}
};
