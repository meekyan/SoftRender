#pragma once
#include "Tiny3DDevice.h"
#include "Math/Vertex.h"
#include <vector>
#include "ShaderBase.h"

enum TINY3D_FILL_MODE//��Ⱦģʽ
{
	TINY3D_FILL_WIREFRAME,//�߿�ģʽ
	TINY3D_FILL_SOLIDE	  //ʵ��ģʽ
};

class Tiny3DDeviceContext
{
public:
	Tiny3DDeviceContext();
	~Tiny3DDeviceContext();
public:
	void Init(Tiny3DDevice* pDevice);										//��ʼ��
	void SetRenderMode(TINY3D_FILL_MODE mode);								//������Ⱦģʽ
	void SetVertexBuffer(std::vector<VertexIn> vertices);					//���ö��㻺��
	void SetCameraPos(const ZCVector& pos);									//�������λ��
	void SetIndexBuffer(std::vector<UINT> indices);							//������������
	void SetShader(ShaderBase* base);										//������ɫ��
	void DrawIndexed(UINT indexCount,UINT startIndexLocation,UINT startVertexLocation);																//����ͼ��
private:
	void ToCVV(VertexOut& v);																	//ͶӰ�������ת��Ϊcvv
	bool Clip(const VertexOut& v);																//cvv�ü�
	VertexOut TransformToProj(const VertexIn& v);													//ת����βü��ռ�
	void TransformToScreen(const ZCMatrix& m,VertexOut& v);										//ת������Ļ����
	bool BackFaceCulling(const VertexIn& v1, const VertexIn& v2, const VertexIn& v3);			//������������
	void BresenhamDrawLine(int x1, int y1, int x2, int y2);										//����
	void ScanlineFill(const VertexOut& left, const VertexOut& right, int yIndex);				//ɨ����
	void DrawTriangle(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3);			//��������
	void DrawTriangleTop(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3);			//��ƽ��������
	void DrawTriangleBottom(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3); 		//��ƽ��������
	void TriangleRasterization(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3);	//��դ��������
private:
	Tiny3DDevice* m_pDevice;													//�豸
	TINY3D_FILL_MODE m_renderMode;											//��Ⱦ״̬
	std::vector<VertexIn> m_vertices;										//���㻺��
	std::vector<UINT> m_indices;												//��������
	ShaderBase* m_pShader;													//��ɫ��
	ZCVector m_cameraPos;													//���λ�� ���ڱ�������
};

