#include "pch.h"
#include "Demo.h"


Demo::Demo() : m_theta(1.5f * MathUtil::PI), m_phi(0.4*MathUtil::PI), m_radius(5.0f)
{
	m_world = MathUtil::MartixIdentity();
}

void Demo::Init()
{
	float halfW = 2 * 0.5f;
	float halfH = 2 * 0.5f;
	float halfD = 2 * 0.5f;
//创建一些顶点 4个
	m_vertices.resize(4);//先搞一个面
	m_indices.resize(6);//一个面 画2个三角形

	m_vertices[0].pos = Vector(-halfW, -halfH, -halfD, 1.f);
	m_vertices[0].normal = Vector(0.f, 0.f, -1.f);
	m_vertices[0].color = Vector(1.f, 0.f, 0.f, 1.f);
	m_vertices[0].tex = FLOAT2(0.f, 1.f);
	m_vertices[1].pos = Vector(-halfW, halfH, -halfD, 1.f);
	m_vertices[1].normal = Vector(0.f, 0.f, -1.f);
	m_vertices[1].color = Vector(0.f, 0.f, 0.f, 1.f);
	m_vertices[1].tex = FLOAT2(0.f, 0.f);
	m_vertices[2].pos = Vector(halfW, halfH, -halfD, 1.f);
	m_vertices[2].normal = Vector(0.f, 0.f, -1.f);
	m_vertices[2].color = Vector(1.f, 0.f, 0.f, 1.f);
	m_vertices[2].tex = FLOAT2(1.f, 0.f);
	m_vertices[3].pos = Vector(halfW, -halfH, -halfD, 1.f);
	m_vertices[3].normal = Vector(0.f, 0.f, -1.f);
	m_vertices[3].color = Vector(0.f, 1.f, 0.f, 1.f);
	m_vertices[3].tex = FLOAT2(1.f, 1.f);

	//构建索引
	m_indices[0] = 0;
	m_indices[1] = 1;
	m_indices[2] = 2;
	m_indices[3] = 0;
	m_indices[4] = 2;
	m_indices[5] = 3;

	Cheight = 800;
	Cwidth = 800;

	m_Shader = new Shader();//着色器
}

void Demo::Update()
{
//拿到相机位置，视角变换、世界-》裁剪 矩阵
	float x = m_radius * sinf(m_phi) * cosf(m_theta);
	float z = m_radius * sinf(m_phi) * sinf(m_theta);
	float y = m_radius * cosf(m_phi);

	Vector pos(x, y, z, 1.0f);
	Vector Target(0.f, 0.f, 0.f, 1.0f);
	Vector up(0.f, 1.f, 0.f, 0.0f);
	Martix view = MathUtil::GetLookAt(pos, Target, up);
	Martix proj = MathUtil::MartixPerspectiveFovLH(1.f,100.f, Cwidth/2, Cheight/2);

	Martix world = MathUtil::MartixIdentity();
	m_worldViewProj = world * view * proj;
	m_world = world;

	m_Shader->SetWorldViewProj(m_worldViewProj);
	m_Shader->SetWorld(m_world);

}

void Demo::SoftRender()
{
//设置一些变量
//拿到顶点集合 开始画三角形

	int count = m_indices.size();
	Martix ScreenTransform = MathUtil::MartixScreenTransform(Cwidth,Cheight);
	for (int i = 0; i < count / 3; ++i)
	{
		VertexIn p1 = m_vertices[m_indices[3 * i]];
		VertexIn p2 = m_vertices[m_indices[3 * i + 1]];
		VertexIn p3 = m_vertices[m_indices[3 * i + 2]];

		VertexOut v1 = TransformToProj(p1);
		VertexOut v2 = TransformToProj(p2);
		VertexOut v3 = TransformToProj(p3);

		if (isClip(v1) == false || isClip(v2) == false || isClip(v3) == false)
		{
			continue;
		}
		ToCVV(v1);
		ToCVV(v2);
		ToCVV(v3);
		v1.posH = v1.posH * ScreenTransform;
		v2.posH = v2.posH * ScreenTransform;
		v3.posH = v3.posH * ScreenTransform;

		DrawTriangle(v1, v2, v3);
	}
}

void Demo::DrawTriangle(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3)
{
	if (v1.posH.y > v2.posH.y)
	{
		std::swap(v1, v2);
	}
	if (v2.posH.y > v3.posH.y)
	{
		std::swap(v2, v3);
	}
	if (v1.posH.y > v2.posH.y)
	{
		std::swap(v1, v2);
	}
	float dy = 0;
	for (float y = v1.posH.y; y <= v3.posH.y; y += 1.0f)
	{
		int Y = static_cast<int>(y + 0.5f);//向外部四舍五入
		if (Y > Cheight) continue;
		float t = dy / (v3.posH.y - v1.posH.y);

		//插值生成左右顶点
		VertexOut new1 = MathUtil::Lerp(v1, v3, t);
		VertexOut new2 = MathUtil::Lerp(v2, v3, t);
		dy += 1.0f;
		//扫描线填充
		if (new1.posH.x < new2.posH.x)
		{
			fill(Y,new1, new2);
		}
		else
		{
			fill(Y,new2, new1);
		}
	
	}
}
void Demo::fill(int Y, const VertexOut& left, const VertexOut& right)
{
	for (int x = left.posH.x; x <= right.posH.x; x += 1.0f)
	{
		int X = static_cast<int>(x + 0.5f);
		if (X < Cwidth) continue;
		float K = 0;
		if(right.posH.x - left.posH.x != 0)
			K = (x - left.posH.x) / (right.posH.x - left.posH.x);
		//1/z’与x’和y'是线性关系的
		float oneDivZ = MathUtil::Lerp(left.oneDivZ, right.oneDivZ, K);
		float w = 1 / oneDivZ;
		//插值顶点 原先需要插值的信息均乘以oneDivZ
		//现在得到插值后的信息需要除以oneDivZ得到真实值
		VertexOut out = MathUtil::Lerp(left, right, K);
		out.posH.y = Y;
		out.tex.u *= w;
		out.tex.v *= w;
		out.normal.x *= w;
		out.normal.y *= w;
		out.normal.z *= w;
		out.color.x *= w;
		out.color.y *= w;
		out.color.z *= w;
		DrawPixel(X, Y, m_Shader->PS(out));
	}
}
VertexOut Demo::TransformToProj(const VertexIn& x)//???
{
	VertexOut out = m_Shader->VS(x);

	out.oneDivZ = 1 / out.posH.w;
	//由于1/z和x,y成线性关系
	//这里将需要插值的信息都乘以1/z 得到 s/z和t/z等，方便光栅化阶段进行插值
	out.color.x *= out.oneDivZ;
	out.color.y *= out.oneDivZ;
	out.color.z *= out.oneDivZ;

	out.normal.x *= out.oneDivZ;
	out.normal.y *= out.oneDivZ;
	out.normal.z *= out.oneDivZ;

	out.tex.u *= out.oneDivZ;
	out.tex.v *= out.oneDivZ;

	return out;
}

bool Demo::isClip(const VertexOut& v)
{
	//cvv为 x-1,1  y-1,1  z0,1
	if (v.posH.x >= -v.posH.w && v.posH.x <= v.posH.w &&
		v.posH.y >= -v.posH.w && v.posH.y <= v.posH.w &&
		v.posH.z >= 0.f && v.posH.z <= v.posH.w)
	{
		return true;
	}
	return false;
}

void Demo::ToCVV(VertexOut& v)
{
	v.posH.x /= v.posH.w;
	v.posH.y /= v.posH.w;
	v.posH.z /= v.posH.w;
	v.posH.w = 1;
}
//画像素
void Demo::DrawPixel(int x, int y, Vector color)
{
	m_pFramebuffer[Cwidth*y + x] = MathUtil::ColorToUINT(color);
}