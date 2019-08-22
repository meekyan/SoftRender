#include "MathUtil.h"


const float MathUtil::PI = 3.1415926f;

//���Բ�ֵ tλ��[0,1]
inline float MathUtil::Lerp(float x1, float x2, float t)
{
	return x1 + (x2 - x1)*t;
}

//ʸ����ֵ
ZCVector MathUtil::Lerp(const ZCVector& v1, const ZCVector& v2, float t)
{
	return ZCVector(
		Lerp(v1.x, v2.x, t),
		Lerp(v1.y, v2.y, t),
		Lerp(v1.z, v2.z, t),
		v1.w
	);
}

//ZCFLOAT2 ��ֵ
ZCFLOAT2 MathUtil::Lerp(const ZCFLOAT2& v1, const ZCFLOAT2& v2, float t)
{
	return ZCFLOAT2(
		Lerp(v1.u, v2.u, t),
		Lerp(v1.v, v2.v, t)
	);
}

//ZCFLOAT3 ��ֵ
ZCFLOAT3 MathUtil::Lerp(const ZCFLOAT3& v1, const ZCFLOAT3& v2, float t)
{
	return ZCFLOAT3(
		Lerp(v1.x, v2.x, t),
		Lerp(v1.y, v2.y, t),
		Lerp(v1.z, v2.z, t)
	);
}

//VertexOut ��ֵ
VertexOut MathUtil::Lerp(const VertexOut& v1, const VertexOut& v2, float t)
{
	return VertexOut(
		Lerp(v1.posTrans, v2.posTrans, t),
		Lerp(v1.posH, v2.posH, t),
		Lerp(v1.tex, v2.tex, t),
		Lerp(v1.normal, v2.normal, t),
		Lerp(v1.color, v2.color, t),
		Lerp(v1.oneDivZ, v2.oneDivZ, t)
	);
}

//clamp
float MathUtil::Clamp(float x, float min, float max)
{
	if (x <= min)
		return min;
	else if (x >= max)
		return max;
	return x;
}

//��������
float MathUtil::Length(const ZCVector& v)
{
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

//��λ����
ZCMatrix MathUtil::ZCMatrixIdentity()
{
	return ZCMatrix(1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f);
}

//����ת��
ZCMatrix MathUtil::ZCMatrixTranspose(const ZCMatrix& mat)
{
	return ZCMatrix(mat._11, mat._21, mat._31, mat._41,
		mat._12, mat._22, mat._32, mat._42,
		mat._13, mat._23, mat._33, mat._43,
		mat._14, mat._24, mat._34, mat._44);
}

//�����Ӧ����ʽ	
/************************************************************************/
/* a11a22a33a44 - a11a22a34a43 - a11a23a32a44 + a11a23a34a42
+ a11a24a32a43 - a11a24a33a42 - a12a21a33a44 + a12a21a34a43
+ a12a23a31a44 - a12a23a34a41 - a12a24a31a43 + a12a24a33a41
+ a13a21a32a44 - a13a21a34a42 - a13a22a31a44 + a13a22a34a41
+ a13a24a31a42 - a13a24a32a41 - a14a21a32a43 + a14a21a33a42
+ a14a22a31a43 - a14a22a33a41 - a14a23a31a42 + a14a23a32a41                                                                     */
/************************************************************************/
float MathUtil::ZCMatrixDet(const ZCMatrix& mat)
{
	float result =
		mat._11*mat._22*mat._33*mat._44 - mat._11*mat._22*mat._34*mat._43 -
		mat._11*mat._23*mat._32*mat._44 + mat._11*mat._23*mat._34*mat._42 +

		mat._11*mat._24*mat._32*mat._43 - mat._11*mat._24*mat._33*mat._42 -
		mat._12*mat._21*mat._33*mat._44 + mat._12*mat._21*mat._34*mat._43 +

		mat._12*mat._23*mat._31*mat._44 - mat._12*mat._23*mat._34*mat._41 -
		mat._12*mat._24*mat._31*mat._43 + mat._12*mat._24*mat._33*mat._41 +

		mat._13*mat._21*mat._32*mat._44 - mat._13*mat._21*mat._34*mat._42 -
		mat._13*mat._22*mat._31*mat._44 + mat._13*mat._22*mat._34*mat._41 +

		mat._13*mat._24*mat._31*mat._42 - mat._13*mat._24*mat._32*mat._41 -
		mat._14*mat._21*mat._32*mat._43 + mat._14*mat._21*mat._33*mat._42 +

		mat._14*mat._22*mat._31*mat._43 - mat._14*mat._22*mat._33*mat._41 -
		mat._14*mat._23*mat._31*mat._42 + mat._14*mat._23*mat._32*mat._41;

	return result;
}

//��������е�ÿһ�� 3*3�����Ӧ������ʽֵ
float MathUtil::ZCMatrixAdjElem(
	float a1, float a2, float a3,
	float b1, float b2, float b3,
	float c1, float c2, float c3)
{
	return a1*(b2*c3 - c2*b3) - a2*(b1*c3 - c1*b3) + a3*(b1*c2 - c1*b2);
}

//������� ��������ʽ��ɵľ����ת��
ZCMatrix MathUtil::ZCMatrixAdj(const ZCMatrix& mat)
{
	float a1 = ZCMatrixAdjElem(mat._22, mat._23, mat._24, mat._32, mat._33, mat._34, mat._42, mat._43, mat._44);
	float a2 = ZCMatrixAdjElem(mat._21, mat._23, mat._24, mat._31, mat._33, mat._34, mat._41, mat._43, mat._44);
	float a3 = ZCMatrixAdjElem(mat._21, mat._22, mat._24, mat._31, mat._32, mat._34, mat._41, mat._42, mat._44);
	float a4 = ZCMatrixAdjElem(mat._21, mat._22, mat._23, mat._31, mat._32, mat._33, mat._41, mat._42, mat._43);
	float b1 = ZCMatrixAdjElem(mat._12, mat._13, mat._14, mat._32, mat._33, mat._34, mat._42, mat._43, mat._44);
	float b2 = ZCMatrixAdjElem(mat._11, mat._13, mat._14, mat._31, mat._33, mat._34, mat._41, mat._43, mat._44);
	float b3 = ZCMatrixAdjElem(mat._11, mat._12, mat._14, mat._31, mat._32, mat._34, mat._41, mat._42, mat._44);
	float b4 = ZCMatrixAdjElem(mat._11, mat._12, mat._13, mat._31, mat._32, mat._33, mat._41, mat._42, mat._43);
	float c1 = ZCMatrixAdjElem(mat._12, mat._13, mat._14, mat._22, mat._23, mat._24, mat._42, mat._43, mat._44);
	float c2 = ZCMatrixAdjElem(mat._11, mat._13, mat._14, mat._21, mat._23, mat._24, mat._41, mat._43, mat._44);
	float c3 = ZCMatrixAdjElem(mat._11, mat._12, mat._14, mat._21, mat._22, mat._24, mat._41, mat._42, mat._44);
	float c4 = ZCMatrixAdjElem(mat._11, mat._12, mat._13, mat._21, mat._22, mat._23, mat._41, mat._42, mat._43);
	float d1 = ZCMatrixAdjElem(mat._12, mat._13, mat._14, mat._22, mat._23, mat._24, mat._32, mat._33, mat._34);
	float d2 = ZCMatrixAdjElem(mat._11, mat._13, mat._14, mat._21, mat._23, mat._24, mat._31, mat._33, mat._34);
	float d3 = ZCMatrixAdjElem(mat._11, mat._12, mat._14, mat._21, mat._22, mat._24, mat._31, mat._32, mat._34);
	float d4 = ZCMatrixAdjElem(mat._11, mat._12, mat._13, mat._21, mat._22, mat._23, mat._31, mat._32, mat._33);

	ZCMatrix result(
		a1, -a2, a3, -a4,
		-b1, b2, -b3, b4,
		c1, -c2, c3, -c4,
		-d1, d2, -d3, d4
	);
	return ZCMatrixTranspose(result);
}

//����� = �������/(����ʽֵ�ľ���ֵ)
ZCMatrix MathUtil::ZCMatrixInverse(const ZCMatrix& mat)
{
	float det = abs(ZCMatrixDet(mat));
	ZCMatrix adj = ZCMatrixAdj(mat);
	ZCMatrix inverse;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
		{
			inverse.m[i][j] = adj.m[i][j] / det;
		}

	return inverse;
}

//���ž���
ZCMatrix MathUtil::ZCMatrixScaling(float scaleX, float scaleY, float scaleZ)
{
	return ZCMatrix(
		scaleX, 0, 0, 0,
		0, scaleY, 0, 0,
		0, 0, scaleZ, 0,
		0, 0, 0, 1
	);
}

//ƽ�ƾ���
ZCMatrix MathUtil::ZCMatrixTranslate(float offsetX, float offsetY, float offsetZ)
{
	return ZCMatrix(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		offsetX, offsetY, offsetZ, 1
	);
}

//��x����ת����
ZCMatrix MathUtil::ZCMatrixRotationX(float angle)
{
	return ZCMatrix(
		1, 0, 0, 0,
		0, cos(angle), sin(angle), 0,
		0, -sin(angle), cos(angle), 0,
		0, 0, 0, 1
	);
}

//��y����ת����
ZCMatrix MathUtil::ZCMatrixRotationY(float angle)
{
	return ZCMatrix(
		cos(angle), 0, -sin(angle), 0,
		0, 1, 0, 0,
		sin(angle), 0, cos(angle), 0,
		0, 0, 0, 1
	);
}

//��z����ת����
ZCMatrix MathUtil::ZCMatrixRotationZ(float angle)
{
	return ZCMatrix(
		cos(angle), sin(angle), 0, 0,
		-sin(angle), cos(angle), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);
}

//��ȡ�ӽǾ���
ZCMatrix MathUtil::ZCMatrixLookAtLH(ZCVector eyePos, ZCVector lookAt, ZCVector up)
{
	ZCVector zaxis = lookAt - eyePos;
	zaxis.Normalize();
	ZCVector xaxis = up.Cross(zaxis).Normalize();
	ZCVector yaxis = zaxis.Cross(xaxis);

	return ZCMatrix(
		xaxis.x, yaxis.x, zaxis.x, 0,
		xaxis.y, yaxis.y, zaxis.y, 0,
		xaxis.z, yaxis.z, zaxis.z, 0,
		-xaxis.Dot(eyePos), -yaxis.Dot(eyePos), -zaxis.Dot(eyePos), 1
	);
}

//��ȡͶӰ���� ͬdx�е�XMMatrixPerspectiveFovLH
//									             �۲��            ��߱�       ���ü�ƽ��   Զ�ü�ƽ��       
ZCMatrix MathUtil::ZCMatrixPerspectiveFovLH(float fovAngleY, float aspectRatio, float nearZ, float farZ)
{
	ZCMatrix mat;
	mat.SetZero();
	// tan(fovAngleY*0.5f)
	float height = cos(fovAngleY*0.5f) / sin(fovAngleY*0.5f);
	mat._11 = height / aspectRatio;
	mat._22 = height;
	mat._33 = farZ / (farZ - nearZ);
	mat._34 = 1.f;
	mat._43 = (nearZ * farZ) / (nearZ - farZ);
	return mat;
}

ZCMatrix MathUtil::ZCMatrixScreenTransform(int clientWidth, int clientHeight)
{
	return ZCMatrix(
		clientWidth / 2, 0, 0, 0,
		0, clientHeight / 2, 0, 0,
		0, 0, 1, 0,
		clientWidth / 2, clientHeight / 2, 0, 1
	);
}

//��ɫZCFloat3(r,b,g,a)ת��ΪUINT
UINT MathUtil::ColorToUINT(const ZCVector& color)
{
	BYTE red = 255 * color.x/*  color.w*/;
	BYTE green = 255 * color.y/* color.w*/;
	BYTE blue = 255 * color.z /* color.w*/;
	return (UINT)((BYTE)blue | (WORD)((BYTE)green << 8) | (DWORD)((BYTE)red << 16));
}

//��������
ZCVector MathUtil::Reflect(const ZCVector& I, const ZCVector& N)
{
	//��ʽ R = I - 2(I��N)N
	float tmp = 2.f * I.Dot(N);
	return I - (N * tmp);
}

