#pragma once
#include "ZCVector.h"


//������Ϣ �������꣬��ɫ���������꣬���ߵȵ�
class VertexIn
{
public:
	//����λ��
	ZCVector pos;
	//������ɫ
	ZCVector color;
	//��������
	ZCFLOAT2 tex;
	//����
	ZCVector normal;

	VertexIn() = default;
	VertexIn(ZCVector pos, ZCVector color, ZCFLOAT2 tex, ZCVector normal)
		:pos(pos), color(color), tex(tex), normal(normal) {}

	VertexIn(const VertexIn& rhs):pos(rhs.pos),color(rhs.color),tex(rhs.tex),normal(rhs.normal){}
};

//����������ɫ������Ľṹ
class VertexOut
{
public:
	//����任�������
	ZCVector posTrans;
	//ͶӰ�任�������
	ZCVector posH;
	//��������
	ZCFLOAT2 tex;
	//����
	ZCVector normal;
	//��ɫ
	ZCVector color;
	//1/z������Ȳ���
	float oneDivZ;

	VertexOut() = default;
	VertexOut(ZCVector posT, ZCVector posH, ZCFLOAT2 tex, ZCVector normal, ZCVector color, float oneDivZ)
		:posTrans(posT), posH(posH), tex(tex), normal(normal), color(color), oneDivZ(oneDivZ) {}

	VertexOut(const VertexOut& rhs) :posTrans(rhs.posTrans), posH(rhs.posH), tex(rhs.tex), normal(rhs.normal),
	color(rhs.color),oneDivZ(rhs.oneDivZ){}

	VertexOut& operator= (const VertexOut& rhs)
	{
		if (this == &rhs)
			return *this;
		this->normal = rhs.normal;
		this->posH = rhs.posH;
		this->posTrans = rhs.posTrans;
		this->tex = rhs.tex;
		this->color = rhs.color;
		this->oneDivZ = rhs.oneDivZ;
		return *this;
	}
};

