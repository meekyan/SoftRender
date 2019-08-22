#pragma once
#include "Math/Vertex.h"
#include "Math/ZCVector.h"
#include "Math/ZCMatrix.h"
#include "LightHelper.h"

class ShaderBase
{
public:
	ShaderBase();
	virtual ~ShaderBase();

public:
	virtual VertexOut VS(const VertexIn& vin) = 0;	//������ɫ��
	virtual ZCVector PS(VertexOut& pin) = 0;	//������ɫ��
};

