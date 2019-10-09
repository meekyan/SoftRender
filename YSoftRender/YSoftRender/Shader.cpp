#include "pch.h"
#include "Shader.h"


Shader::Shader()
{
}


Shader::~Shader()
{
}


void Shader::SetWorldViewProj(const Martix& worldViewProj)
{
	m_worldViewProj = worldViewProj;
}

void Shader::SetWorld(const Martix& world)
{
	m_world = world;
}

void Shader::SetEyePos(const Vector& eyePos)
{
	m_eyePos = eyePos;
}

VertexOut Shader::VS(const VertexIn& vin)
{
	VertexOut out;
	out.posH = vin.pos * m_worldViewProj;

	out.posTrans = vin.pos * m_world;

	out.color = vin.color;
	out.tex = vin.tex;

	return out;
}

Vector Shader::PS(VertexOut& pin)
{
	//纹理采样
	//光源计算后得到的环境光、漫反射 、高光
	return pin.color;
}

