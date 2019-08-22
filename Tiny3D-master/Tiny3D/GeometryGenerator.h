#pragma once
#include "Math/ZCMath.h"

class GeometryGenerator
{
private:
	GeometryGenerator() {}

public:
	//����ģʽ
	static GeometryGenerator* GetInstance()
	{
		static GeometryGenerator instance;
		return &instance;
	}

	//��������ṹ�����㼯��+��������
	struct MeshData
	{
		std::vector<VertexIn>	vertices;
		std::vector<UINT>	indices;
	};

	//����һ�������壺ָ����(X����)����(Y����)����(Z����)
	void CreateBox(float width, float height, float depth, MeshData &mesh);
};

