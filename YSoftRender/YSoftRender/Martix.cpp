#include "pch.h"
#include "Martix.h"

void Martix::SetZero()
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			martix[i][j] = 0.0f;
}

Martix Martix::operator+(const Martix& t) const
{
	Martix result;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			result.martix[i][j] = martix[i][j] + t.martix[i][j];
	return result;
}

Martix Martix::operator-(const Martix& t) const
{
	Martix result;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			result.martix[i][j] = martix[i][j] - t.martix[i][j];
	return result;
}

Martix Martix::operator*(const Martix& t) const
{
	Martix result;
	/*for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			for (int k = 0; k < 4; ++k)
				result.martix[j][i] += martix[j][k] * t.martix[k][i] * 1.0f;*/
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
		{
			result.martix[j][i] = (martix[j][0] * t.martix[0][i]) +
				(martix[j][1] * t.martix[1][i]) +
				(martix[j][2] * t.martix[2][i]) +
				(martix[j][3] * t.martix[3][i]);
		}
	return result;
}

void Martix::identity()
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++i)
			martix[i][j] = 0.0f;
	for (int i = 0; i < 4; ++i)
		martix[i][i] = 1.0f;
}

bool Martix::operator== (const Martix& t) const
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			if (abs(martix[i][j] - t.martix[i][j]) >= 0.000001f)
				return false;
	return true;
}

Martix Martix::operator^ (const Martix& t) const
{
	Martix result;
	return result;
}