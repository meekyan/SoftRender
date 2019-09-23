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
	//单位化法线
	pin.normal.Normalize();

	//纹理采样
	//Vector texColor = m_tex.Sample(pin.tex);

	//顶点到观察点向量
	Vector toEye = (m_eyePos - pin.posTrans).Normalize();

	//初始化颜色值全部为0
	Vector ambient(0.f, 0.f, 0.f, 0.f);
	Vector diffuse(0.f, 0.f, 0.f, 0.f);
	Vector specular(0.f, 0.f, 0.f, 0.f);

	//光源计算后得到的环境光、漫反射 、高光
	Vector A, D, S;

	//Lights::ComputeDirectionalLight(m_material, m_dirLight, pin.normal, toEye, A, D, S);

	//ambient = ambient + A;
	//diffuse = diffuse + D;
	//specular = specular + S;


	////纹理+光照计算公式： 纹理*(环境光+漫反射光)+高光
	//Vector litColor = texColor * (ambient + diffuse) + specular;

	////最终颜色透明度使用漫反射光的透明度
	//litColor.w = m_material.diffuse.w * texColor.w;
	Vector litColor;


	return pin.color;
}

