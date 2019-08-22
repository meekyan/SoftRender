#include "BoxShader.h"



BoxShader::BoxShader()
{
}


BoxShader::~BoxShader()
{
}

void BoxShader::SetWorldViewProj(const ZCMatrix& worldViewProj)
{
	m_worldViewProj = worldViewProj;
}

void BoxShader::SetTexture(const Texture2D& tex)
{
	m_tex = tex;
}

void BoxShader::SetWorld(const ZCMatrix& world)
{
	m_world = world;
}

void BoxShader::SetWorldInvTranspose(const ZCMatrix& worldInvTrans)
{
	m_worldInvTranspose = worldInvTrans;
}

void BoxShader::SetEyePos(const ZCVector& eyePos)
{
	m_eyePos = eyePos;
}

void BoxShader::SetMaterial(const Lights::Material& material)
{
	m_material.ambient = material.ambient;
	m_material.diffuse = material.diffuse;
	m_material.reflect = material.reflect;
	m_material.specular = material.specular;
}

void BoxShader::SetDirLight(const Lights::DirectionalLight& dirLight)
{
	m_dirLight.ambient = dirLight.ambient;
	m_dirLight.diffuse = dirLight.diffuse;
	m_dirLight.direction = dirLight.direction;
	m_dirLight.specular = dirLight.specular;
}

VertexOut BoxShader::VS(const VertexIn& vin)
{
	VertexOut out;
	out.posH = vin.pos * m_worldViewProj;
	
	out.posTrans = vin.pos * m_world;
	out.normal = out.normal * m_worldInvTranspose;

 	out.color = vin.color;
 	out.tex = vin.tex;

	return out;
}

ZCVector BoxShader::PS(VertexOut& pin)
{
	//��λ������
	pin.normal.Normalize();

	//�������
	ZCVector texColor = m_tex.Sample(pin.tex);

	//���㵽�۲������
	ZCVector toEye = (m_eyePos - pin.posTrans).Normalize();

	//��ʼ����ɫֵȫ��Ϊ0
	ZCVector ambient(0.f, 0.f, 0.f, 0.f);
	ZCVector diffuse(0.f, 0.f, 0.f, 0.f);
	ZCVector specular(0.f, 0.f, 0.f, 0.f);

	//��Դ�����õ��Ļ����⡢������ ���߹�
	ZCVector A, D, S;

	Lights::ComputeDirectionalLight(m_material, m_dirLight, pin.normal, toEye, A, D, S);

	ambient = ambient + A;
	diffuse = diffuse + D;
	specular = specular + S;


	//����+���ռ��㹫ʽ�� ����*(������+�������)+�߹�
	ZCVector litColor = texColor * (ambient + diffuse) + specular;

	//������ɫ͸����ʹ����������͸����
	litColor.w = m_material.diffuse.w * texColor.w;

	return litColor;
}
