#pragma once
#include <cmath>

class Martix
{
public:
	union
	{
		float martix[4][4];
		struct
		{
			float _00; float _01; float _02; float _03;
			float _10; float _11; float _12; float _13;
			float _20; float _21; float _22; float _23;
			float _30; float _31; float _32; float _33;
		};
	};

	Martix() = default;
	Martix(float a0, float a1, float a2, float a3,
		float b0, float b1, float b2, float b3,
		float c0, float c1, float c2, float c3,
		float d0, float d1, float d2, float d3)
	{
		_00 = a0; _01 = a1;_02 = a2;_03 = a3;
		_10 = b0; _11 = b1;_12 = b2;_13 = b3;
		_20 = c0; _21 = c1;_22 = c2;_23 = c3;
		_30 = d0; _31 = d1;_32 = d2;_33 = d3;
	}
	Martix(const Martix& t)
	{
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				martix[i][j] = t.martix[i][j];
	}
	Martix& operator= (const Martix& t)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				martix[i][j] = t.martix[i][j];
			}
		}
		return *this;
	}

	void SetZero();//0矩阵
	bool operator== (const Martix& t) const;//判相等
	Martix operator+ (const Martix& t) const;//相加
	Martix operator- (const Martix& t) const;//减
	Martix operator* (const Martix& t) const;//乘法
	Martix operator^ (const Martix& t) const;//幂
	void identity();//单位矩阵
private:
};