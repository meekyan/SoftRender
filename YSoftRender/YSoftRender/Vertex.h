#pragma once

#include "Vector.h"

//���붥����Ϣ
class VertexIn
{
public:
	Vector pos;//����λ��
	Vector color;//������ɫ rbg
	FLOAT2 tex;//��ά��������
	Vector normal;//����
	VertexIn() = default;
	VertexIn(Vector pos, Vector color, FLOAT2 tex, Vector normal)
		:pos(pos), color(color), tex(tex), normal(normal) {}
	VertexIn(const VertexIn& t) :pos(t.pos), color(t.color), tex(t.tex), normal(t.normal) {}
};

//������ɫ�����������
class VertexOut
{
public:

	//����任�������
	Vector posTrans;
	//ͶӰ�任�������
	Vector posH;
	//��������
	FLOAT2 tex;
	//����
	Vector normal;
	//��ɫ
	Vector color;
	//1/z������Ȳ���
	float oneDivZ;

	VertexOut() = default;
	VertexOut(Vector posT, Vector posH, FLOAT2 tex, Vector normal, Vector color, float oneDivZ)
		:posTrans(posT), posH(posH), tex(tex), normal(normal), color(color), oneDivZ(oneDivZ) {}

	VertexOut(const VertexOut& rhs) :posTrans(rhs.posTrans), posH(rhs.posH), tex(rhs.tex), normal(rhs.normal),
		color(rhs.color), oneDivZ(rhs.oneDivZ) {}

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

private:

};