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

	Martix MartixIdentity();//��λ����

	Martix MartixTranspose(const Martix& t);//ת�þ���
	//���ž���
	Martix MatrixScaling(float scaleX, float scaleY, float scaleZ);

	//ƽ�ƾ���
	Martix MatrixTranslate(float offsetX, float offsetY, float offsetZ);

	float MatrixDet(const Martix& mat);//�����Ӧ����ʽ	

	Martix MatrixAdj(const Martix& mat);//������� ��������ʽ��ɵľ����ת��


	Martix GetLookAt(Vector eyePos, Vector lookAt, Vector up);//����ӽǾ���


	//��ȡͶӰ���� ͬOPGL 
//								     	 ���ü�ƽ��   Զ�ü�ƽ��   ��Ļ��С       
	Martix MartixPerspectiveFovLH(float n, float f, float r, float t);

	Martix MartixPerspectiveFovLH2(float n, float f, float r, float t);

	//ͶӰ-����Ļ
	Martix MartixScreenTransform(int clientWidth, int clientHeight);

	//���Բ�ֵ tλ��[0,1]
	float Lerp(float x1, float x2, float t);

	//ʸ����ֵ
	Vector Lerp(const Vector& v1, const Vector& v2, float t);

	//ZCFLOAT2 ��ֵ
	FLOAT2 Lerp(const FLOAT2& v1, const FLOAT2& v2, float t);

	//ZCFLOAT3��ֵ
	FLOAT3 Lerp(const FLOAT3& v1, const FLOAT3& v2, float t);

	//VertexOut��ֵ
	VertexOut Lerp(const VertexOut& v1, const VertexOut& v2, float t);

	UINT32 ColorToUINT(const Vector& color);

	void Swap(VertexOut& v1, VertexOut& v2);
}