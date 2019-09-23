#include "pch.h"
#include "MathUtil.h"



const float MathUtil::PI = 3.1415926f;


//单位矩阵
Martix MathUtil::MartixIdentity()
{
	return Martix(1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f);
}


//矩阵的转置
Martix MathUtil::MartixTranspose(const Martix& t)
{
	return Martix(t._00, t._10, t._20, t._30,
		t._01, t._11, t._21, t._31,
		t._02, t._12, t._22, t._32,
		t._03, t._13, t._23, t._33);
}

//缩放矩阵
Martix MathUtil::MatrixScaling(float scaleX, float scaleY, float scaleZ)
{
	return Martix(
		scaleX, 0, 0, 0,
		0, scaleY, 0, 0,
		0, 0, scaleZ, 0,
		0, 0, 0, 1
	);
}

//平移矩阵
Martix MathUtil::MatrixTranslate(float offsetX, float offsetY, float offsetZ)
{
	return Martix(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		offsetX, offsetY, offsetZ, 1
	);
}



//拿到视角矩阵
Martix MathUtil::GetLookAt(Vector eyePos, Vector lookAt, Vector up)
{
	Vector zv = lookAt - eyePos;
	zv.Normalize();
	Vector xv = up.Cross(zv).Normalize();
	Vector yv = zv.Cross(xv);
	return Martix(
		xv.x, yv.x, zv.x, 0,
		xv.y, yv.y, zv.y, 0,
		xv.z, yv.z, zv.z, 0,
		-xv.Dot(eyePos), -yv.Dot(eyePos), -zv.Dot(eyePos), 1
	);
}

//获取投影矩阵 同OPGL 
//								     	 近裁剪平面   远裁剪平面   屏幕大小 
Martix MathUtil::MartixPerspectiveFovLH(float n, float f,float r,float t)
{
	Martix mat;
	mat.SetZero();
	mat._00 = n / r;
	mat._11 = n / t;
	mat._22 = -(f + n) / (f - n);
	mat._23 = -2 * f*n / (f - n);
	mat._32 = -1;
	return mat;
}
//获取投影矩阵 同dx中的XMMatrixPerspectiveFovLH
//									             观察角            宽高比       近裁剪平面   远裁剪平面       
Martix MathUtil::MartixPerspectiveFovLH2(float fovAngleY, float aspectRatio, float nearZ, float farZ)
{
	Martix mat;
	mat.SetZero();
	// tan(fovAngleY*0.5f)
	float height = cos(fovAngleY*0.5f) / sin(fovAngleY*0.5f);
	mat._00 = height / aspectRatio;
	mat._11 = height;
	mat._22 = farZ / (farZ - nearZ);
	mat._23 = 1.f;
	mat._32 = (nearZ * farZ) / (nearZ - farZ);
	return mat;
}



Martix MathUtil::MartixScreenTransform(int clientWidth, int clientHeight)
{
	return Martix(
		clientWidth / 2, 0, 0, 0,
		0, clientHeight / 2, 0, 0,
		0, 0, 1, 0,
		clientWidth / 2, clientHeight / 2, 0, 1
	);
}

//线性插值 t位于[0,1]
inline float MathUtil::Lerp(float x1, float x2, float t)
{
	return x1 + (x2 - x1)*t;
}

//矢量插值
Vector MathUtil::Lerp(const Vector& v1, const Vector& v2, float t)
{
	return Vector(
		Lerp(v1.x, v2.x, t),
		Lerp(v1.y, v2.y, t),
		Lerp(v1.z, v2.z, t),
		v1.w
	);
}

//FLOAT2 插值
FLOAT2 MathUtil::Lerp(const FLOAT2& v1, const FLOAT2& v2, float t)
{
	return FLOAT2(
		Lerp(v1.u, v2.u, t),
		Lerp(v1.v, v2.v, t)
	);
}

//FLOAT3 插值
FLOAT3 MathUtil::Lerp(const FLOAT3& v1, const FLOAT3& v2, float t)
{
	return FLOAT3(
		Lerp(v1.x, v2.x, t),
		Lerp(v1.y, v2.y, t),
		Lerp(v1.z, v2.z, t)
	);
}

//VertexOut 插值
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

//颜色Float3(r,b,g,a)转化为UINT
UINT32 MathUtil::ColorToUINT(const Vector& color)
{
	BYTE red = 255 * color.x/*  color.w*/;
	BYTE green = 255 * color.y/* color.w*/;
	BYTE blue = 255 * color.z /* color.w*/;
	UINT32 color_num = ((UINT32)((BYTE)blue | (WORD)((BYTE)green << 8) | (DWORD)((BYTE)red << 16)));

	return (UINT32)color_num;
}

void MathUtil::Swap(VertexOut& v1, VertexOut& v2)
{
	VertexOut tmp = v1;
	v1 = v2;
	v2 = tmp;
}