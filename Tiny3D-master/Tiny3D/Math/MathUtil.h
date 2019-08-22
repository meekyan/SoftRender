#pragma once
#include "ZCVector.h"
#include "ZCMatrix.h"
#include "Vertex.h"
#include <windows.h>
#include <cmath>
#include <vector>

namespace MathUtil
{
	extern const float PI;
	//���Բ�ֵ tλ��[0,1]
	float Lerp(float x1, float x2, float t);

	//ʸ����ֵ
	ZCVector Lerp(const ZCVector& v1, const ZCVector& v2, float t);

	//ZCFLOAT2 ��ֵ
	ZCFLOAT2 Lerp(const ZCFLOAT2& v1, const ZCFLOAT2& v2, float t);

	//ZCFLOAT3��ֵ
	ZCFLOAT3 Lerp(const ZCFLOAT3& v1, const ZCFLOAT3& v2, float t);

	//VertexOut��ֵ
	VertexOut Lerp(const VertexOut& v1, const VertexOut& v2, float t);

	//clamp
	float Clamp(float x, float min, float max);

	//�Ƕ�ת����
	inline float ZCConvertToRadians(float fDegrees) { return fDegrees * (PI / 180.0f); }

	//��������
	float Length(const ZCVector& v);

	//��λ����
	ZCMatrix ZCMatrixIdentity();

	//����ת��
	ZCMatrix ZCMatrixTranspose(const ZCMatrix& mat);

	//�����Ӧ����ʽ	
	float ZCMatrixDet(const ZCMatrix& mat);

	//��������е�ÿһ�� 3*3�����Ӧ������ʽֵ
	float ZCMatrixAdjElem(
		float a1, float a2, float a3,
		float b1, float b2, float b3,
		float c1, float c2, float c3);

	//������� ��������ʽ��ɵľ����ת��
	ZCMatrix ZCMatrixAdj(const ZCMatrix& mat);

	//����� = �������/(����ʽֵ�ľ���ֵ)
	ZCMatrix ZCMatrixInverse(const ZCMatrix& mat);

	//���ž���
	ZCMatrix ZCMatrixScaling(float scaleX, float scaleY, float scaleZ);

	//ƽ�ƾ���
	ZCMatrix ZCMatrixTranslate(float offsetX, float offsetY, float offsetZ);

	//��x����ת����
	ZCMatrix ZCMatrixRotationX(float angle);

	//��y����ת����
	ZCMatrix ZCMatrixRotationY(float angle);

	//��z����ת����
	ZCMatrix ZCMatrixRotationZ(float angle);

	//��ȡ�ӽǾ���
	ZCMatrix ZCMatrixLookAtLH(ZCVector eyePos, ZCVector lookAt, ZCVector up);

	//��ȡͶӰ���� ͬdx�е�XMMatrixPerspectiveFovLH
	//									    �۲��            ��߱�       ���ü�ƽ��   Զ�ü�ƽ��       
	ZCMatrix ZCMatrixPerspectiveFovLH(float fovAngleY, float aspectRatio, float nearZ, float farZ);
	
	//ͶӰ���������굽��Ļ����任����
	ZCMatrix ZCMatrixScreenTransform(int clientWidth, int clientHeight);

	//��ɫZCVector(r,b,g,a)ת��ΪUINT
	UINT ColorToUINT(const ZCVector& color);

	//�������������ڷ��ߵķ�������
	ZCVector Reflect(const ZCVector& vin, const ZCVector& normal);
}