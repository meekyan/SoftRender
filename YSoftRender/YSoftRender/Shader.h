#pragma once
#include "Martix.h"
#include "Vertex.h"
class Shader
{
public:
	Shader();
	~Shader();
private:
	Martix m_worldViewProj; //世界视角投影矩阵	
	Martix m_world; //世界矩阵
	Vector m_eyePos;			//观察点
public:
	void SetWorldViewProj(const Martix& worldViewProj);
	void SetWorld(const Martix& world);
	void SetEyePos(const Vector& eyePos);

	VertexOut VS(const VertexIn& vin);	//顶点着色器
	Vector PS(VertexOut& pin);//
};

