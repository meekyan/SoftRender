#pragma once
#include <cmath>

class Martix
{
public:
	//单位化
	void Identity();
	//0矩阵
	void SetZero();
	//等于
	bool operator== (const Martix& rhs) const;
	//加
	Martix operator+ (const Martix& rhs) const;
	//减
	Martix operator- (const Martix& rhs) const;
	//乘
	Martix operator* (const Martix& rhs) const;
private:

};