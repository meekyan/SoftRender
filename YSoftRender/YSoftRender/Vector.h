#pragma once

#include <cmath>
#include "Martix.h"

class Vector
{
public:
	float x;
	float y;
	float z;
	float w; //0向量1点
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
	//向量长度
	float Length() const;
	//归一化
	Vector Normalize();
	//点乘
	float Dot(Vector v) const;
	//叉乘
	Vector Cross(Vector t) const;
	//重载== 
	bool operator==(const Vector& t) const;
	//与变换矩阵相乘
	Vector operator* (const Martix& t) const;
	//与ZCVector分量相乘
	Vector operator* (const Vector& t) const;
	//与float相乘
	Vector operator*(float factor) const;
	//加
	Vector operator+ (const Vector& t) const;
	//减
	Vector operator- (const Vector& t) const;
	//负号
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


//二维向量主要用于表示纹理坐标
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
