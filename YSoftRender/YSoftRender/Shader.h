#pragma once
#include "Martix.h"
#include "Vertex.h"
class Shader
{
public:
	Shader();
	~Shader();
private:
	Martix m_worldViewProj; //�����ӽ�ͶӰ����	
	Martix m_world; //�������
	Vector m_eyePos;			//�۲��
public:
	void SetWorldViewProj(const Martix& worldViewProj);
	void SetWorld(const Martix& world);
	void SetEyePos(const Vector& eyePos);

	VertexOut VS(const VertexIn& vin);	//������ɫ��
	Vector PS(VertexOut& pin);//
};

