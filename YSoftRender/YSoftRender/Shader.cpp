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
	//��λ������
	pin.normal.Normalize();

	//�������
	//Vector texColor = m_tex.Sample(pin.tex);

	//���㵽�۲������
	Vector toEye = (m_eyePos - pin.posTrans).Normalize();

	//��ʼ����ɫֵȫ��Ϊ0
	Vector ambient(0.f, 0.f, 0.f, 0.f);
	Vector diffuse(0.f, 0.f, 0.f, 0.f);
	Vector specular(0.f, 0.f, 0.f, 0.f);

	//��Դ�����õ��Ļ����⡢������ ���߹�
	Vector A, D, S;

	//Lights::ComputeDirectionalLight(m_material, m_dirLight, pin.normal, toEye, A, D, S);

	//ambient = ambient + A;
	//diffuse = diffuse + D;
	//specular = specular + S;


	////����+���ռ��㹫ʽ�� ����*(������+�������)+�߹�
	//Vector litColor = texColor * (ambient + diffuse) + specular;

	////������ɫ͸����ʹ����������͸����
	//litColor.w = m_material.diffuse.w * texColor.w;
	Vector litColor;


	return pin.color;
}

