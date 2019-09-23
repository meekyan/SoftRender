#pragma once

#include "Martix.h"
#include "Vector.h"
#include "Vertex.h"
#include <windows.h>
#include <cmath>
#include <vector>

namespace MathUtil
{
	extern const float PI;

	Martix MartixIdentity();//单位矩阵

	Martix MartixTranspose(const Martix& t);//转置矩阵
	//缩放矩阵
	Martix MatrixScaling(float scaleX, float scaleY, float scaleZ);

	//平移矩阵
	Martix MatrixTranslate(float offsetX, float offsetY, float offsetZ);

	float MatrixDet(const Martix& mat);//矩阵对应行列式	

	Martix MatrixAdj(const Martix& mat);//伴随矩阵 代数余子式组成的矩阵的转置


	Martix GetLookAt(Vector eyePos, Vector lookAt, Vector up);//获得视角矩阵


	//获取投影矩阵 同OPGL 
//								     	 近裁剪平面   远裁剪平面   屏幕大小       
	Martix MartixPerspectiveFovLH(float n, float f, float r, float t);

	Martix MartixPerspectiveFovLH2(float n, float f, float r, float t);

	//投影-》屏幕
	Martix MartixScreenTransform(int clientWidth, int clientHeight);

	//线性插值 t位于[0,1]
	float Lerp(float x1, float x2, float t);

	//矢量插值
	Vector Lerp(const Vector& v1, const Vector& v2, float t);

	//ZCFLOAT2 插值
	FLOAT2 Lerp(const FLOAT2& v1, const FLOAT2& v2, float t);

	//ZCFLOAT3插值
	FLOAT3 Lerp(const FLOAT3& v1, const FLOAT3& v2, float t);

	//VertexOut插值
	VertexOut Lerp(const VertexOut& v1, const VertexOut& v2, float t);

	UINT32 ColorToUINT(const Vector& color);

	void Swap(VertexOut& v1, VertexOut& v2);
}