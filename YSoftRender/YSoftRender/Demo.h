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
	void Init();
	void Update();
	void SoftRender();
	VertexOut TransformToProj(const VertexIn& x);
	bool isClip(const VertexOut& v);
	void ToCVV(VertexOut& v);
	void DrawTriangle(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3);
	void fill(int Y,const VertexOut& left, const VertexOut& right);
	void DrawPixel(int x, int y, Vector color);
public:
	Martix  m_worldViewProj;//�����ӽ�ͶӰ���� ����-�����-����βü�
	Martix m_world;//������� �任Ϊ��������ϵ�¾���Ĭ�Ͼ��ǵ�λ��

	std::vector<VertexIn>  m_vertices;//���㼯��
	std::vector<UINT>	   m_indices;//��������

	Shader* m_Shader;		//��ɫ��

	//������ĽǶȺ�λ��
	float m_theta;
	float m_phi;
	float m_radius;
	POINT m_lastMousePos;

	//
	int Cwidth;
	int Cheight;

	UINT* m_pFramebuffer;
};

