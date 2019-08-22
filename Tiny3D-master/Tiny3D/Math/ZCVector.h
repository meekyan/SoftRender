#pragma once
#include <cmath>
#include "ZCMatrix.h"

class ZCVector
{
public:
	float x;
	float y;
	float z;
	float w;	//0�������� 1�����

public:
	ZCVector() = default;
	ZCVector(float x1, float y1, float z1, float w1 = 0) :x(x1), y(y1), z(z1), w(w1) {}
	ZCVector(const ZCVector& rhs) :x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w) {}
	ZCVector& operator= (const ZCVector& rhs)
	{
		if (this == &rhs)
			return *this;
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;
		return *this;
	}

public:
	//��������
	float Length() const;	
	//��һ��
	ZCVector Normalize();
	//���
	float Dot(ZCVector v) const;
	//���
	ZCVector Cross(ZCVector rhs) const;
	//����== 
	bool operator==(const ZCVector& rhs) const;
	//��任�������
	ZCVector operator* (const ZCMatrix& rhs) const;
	//��ZCVector�������
	ZCVector operator* (const ZCVector& rhs) const;
	//��float���
	ZCVector operator*(float factor) const;
	//��
	ZCVector operator+ (const ZCVector& rhs) const;
	//��
	ZCVector operator- (const ZCVector& rhs) const;
	//����
	ZCVector operator-() const;
	
};


class ZCFLOAT3
{
public:
	float x;
	float y;
	float z;
public:
	ZCFLOAT3() = default;
	ZCFLOAT3(float r,float b,float g):x(r),y(b),z(g){}
	ZCFLOAT3(const ZCFLOAT3& rhs) :x(rhs.x), y(rhs.y), z(rhs.z) {}
	ZCFLOAT3& operator= (const ZCFLOAT3& rhs)
	{
		if (this == &rhs)
			return *this;
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}
};


//��ά������Ҫ���ڱ�ʾ��������
class ZCFLOAT2
{
public:
	float u;
	float v;
public:
	ZCFLOAT2() = default;
	ZCFLOAT2(float x, float y) :u(x), v(y) {}
	ZCFLOAT2(const ZCFLOAT2& rhs):u(rhs.u),v(rhs.v){}
	ZCFLOAT2& operator= (const ZCFLOAT2& rhs)
	{
		if (this == &rhs)
			return *this;
		u = rhs.u;
		v = rhs.v;
		return *this;
	}
};