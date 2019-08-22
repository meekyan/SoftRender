#pragma once
#include "ShaderBase.h"
#include "Math/ZCMath.h"

class BoxShader : public ShaderBase
{
public:
	BoxShader();
	~BoxShader();

private:
 	ZCMatrix						m_worldViewProj;		//�����ӽ�ͶӰ����	
	Texture2D					m_tex;				//����
 	ZCMatrix						m_world;				//�������
 	ZCMatrix						m_worldInvTranspose;	//�������������ת�ã����ڵ�������
 	Lights::Material				m_material;			//����
	Lights::DirectionalLight		m_dirLight;			//ƽ�й�
	ZCVector						m_eyePos;			//�۲��

public:
	void SetWorldViewProj(const ZCMatrix& worldViewProj);
	void SetTexture(const Texture2D& tex);
	void SetWorld(const ZCMatrix& world);
	void SetWorldInvTranspose(const ZCMatrix& worldInvTrans);
	void SetEyePos(const ZCVector& eyePos);
	void SetMaterial(const Lights::Material& material);
	void SetDirLight(const Lights::DirectionalLight& dirLight);
public:
	VertexOut VS(const VertexIn& vin);	//������ɫ��
	ZCVector PS(VertexOut& pin);
};

