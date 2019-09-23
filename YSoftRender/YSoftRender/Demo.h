#pragma once

#include "MathUtil.h"
#include "vector"
#include "Martix.h"
#include "Vertex.h"
#include "Shader.h"
#include <windows.h>

class Demo
{
public:
	Demo();

public:
	void Init(UINT32* Framebuffer,HINSTANCE hInstance, HWND hWnd);
	void Update();
	void SoftRender();
	VertexOut TransformToProj(const VertexIn& x);
	bool isClip(const VertexOut& v);
	void ToCVV(VertexOut& v);
	void SortAndDrawTriangle(VertexOut& v1, VertexOut& v2, VertexOut& v3);
	void DrawTriangle(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3);
	void fill(int Y,const VertexOut& left, const VertexOut& right);
	void DrawPixel(int x, int y, Vector color);
public:
	Martix  m_worldViewProj;//世界视角投影矩阵 世界-》相机-》齐次裁剪
	Martix m_world;//世界矩阵 变换为世界坐标系下矩阵，默认就是单位阵


	Shader* m_Shader;		//着色器

	//摄像机的角度和位置
	float m_theta;
	float m_phi;
	float m_radius;
	POINT m_lastMousePos;

	//
	int Cwidth;
	int Cheight;

	HINSTANCE	m_hInstance;
	HWND	m_hWnd;

	UINT32** m_pFramebuffer;

private:
	std::vector<VertexIn>  m_vertices;//顶点集合
	std::vector<UINT32>	   m_indices;//索引缓冲
};

