#pragma once
#include <cmath>

class Martix
{
public:
	//��λ��
	void Identity();
	//0����
	void SetZero();
	//����
	bool operator== (const Martix& rhs) const;
	//��
	Martix operator+ (const Martix& rhs) const;
	//��
	Martix operator- (const Martix& rhs) const;
	//��
	Martix operator* (const Martix& rhs) const;
private:

};