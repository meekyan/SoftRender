#pragma once

#include "Vector.h"

//输入顶点信息
class VertexIn
{
public:
	Vector pos;//顶点位置
	Vector color;//顶点颜色 rbg
	FLOAT2 tex;//二维纹理坐标
	Vector normal;//法线
	VertexIn() = default;
	VertexIn(Vector pos, Vector color, FLOAT2 tex, Vector normal)
		:pos(pos), color(color), tex(tex), normal(normal) {}
	VertexIn(const VertexIn& t) :pos(t.pos), color(t.color), tex(t.tex), normal(t.normal) {}
};

//顶点着色器输出的坐标
class VertexOut
{
public:

	//世界变换后的坐标
	Vector posTrans;
	//投影变换后的坐标
	Vector posH;
	//纹理坐标
	FLOAT2 tex;
	//法线
	Vector normal;
	//颜色
	Vector color;
	//1/z用于深度测试
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