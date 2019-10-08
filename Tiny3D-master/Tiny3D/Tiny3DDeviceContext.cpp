#include "Tiny3DDeviceContext.h"
#include "Math/MathUtil.h"
#include <algorithm>

Tiny3DDeviceContext::Tiny3DDeviceContext():m_renderMode(TINY3D_FILL_WIREFRAME),m_cameraPos(ZCVector(0.f,0.f,0.f,1.f))
{
}


Tiny3DDeviceContext::~Tiny3DDeviceContext()
{
}

void Tiny3DDeviceContext::Init(Tiny3DDevice* pDevice)
{
	m_pDevice = pDevice;
}

//������Ⱦģʽ
void Tiny3DDeviceContext::SetRenderMode(TINY3D_FILL_MODE mode)
{
	m_renderMode = mode;
}

//���ö��㻺��
void Tiny3DDeviceContext::SetVertexBuffer(std::vector<VertexIn> vertices)
{
	m_vertices = vertices;
}

//�������λ��
void Tiny3DDeviceContext::SetCameraPos(const ZCVector& pos)
{
	m_cameraPos = pos;
}

//������������
void Tiny3DDeviceContext::SetIndexBuffer(std::vector<UINT> indices)
{
	m_indices = indices;
}

//������ɫ��
void Tiny3DDeviceContext::SetShader(ShaderBase* base)
{
	m_pShader = base;
}

//���ƶ��㻺���е�������
void Tiny3DDeviceContext::DrawIndexed(UINT indexCount, UINT startIndexLocation, UINT startVertexLocation)
{
	//�õ���Ļ�任����
	ZCMatrix screenTransformMat = MathUtil::ZCMatrixScreenTransform(m_pDevice->GetClientWidth(),
		m_pDevice->getClientHeight());

 	for (int i = startIndexLocation; i < indexCount / 3; ++i)
 	{
		VertexIn p1 = m_vertices[startVertexLocation + m_indices[3 * i]];
		VertexIn p2 = m_vertices[startVertexLocation + m_indices[3 * i + 1]];
		VertexIn p3 = m_vertices[startVertexLocation + m_indices[3 * i + 2]];
		//��������
		if (BackFaceCulling(p1, p2, p3) == false)                                                                                                                                         
		{
			continue;
		}

		//ת������βü��ռ䣬��ͶӰ�������
		VertexOut v1 = TransformToProj(p1);
		VertexOut v2 = TransformToProj(p2);
		VertexOut v3 = TransformToProj(p3);


		//�ж��Ƿ�ͨ��cvv�ü�
		if (Clip(v1) == false || Clip(v2) == false || Clip(v3) == false)
		{
			continue;
		}

		//����͸�ӳ��� ת��cvv
		ToCVV(v1);
		ToCVV(v2);
		ToCVV(v3);

		//��ͶӰ�õ�������ת��Ϊ��Ļ����
		TransformToScreen(screenTransformMat, v1);
		TransformToScreen(screenTransformMat, v2);
		TransformToScreen(screenTransformMat, v3);
		
		DrawTriangle(v1, v2, v3);
 	}
}

//ת����cvv
void Tiny3DDeviceContext::ToCVV(VertexOut& v)
{
	v.posH.x /= v.posH.w;
	v.posH.y /= v.posH.w;
	v.posH.z /= v.posH.w;
	v.posH.w = 1;
}

//��cvv�ü�
bool Tiny3DDeviceContext::Clip(const VertexOut& v)
{
	//cvvΪ x-1,1  y-1,1  z0,1
	if (v.posH.x >= -v.posH.w && v.posH.x <= v.posH.w &&
		v.posH.y >= -v.posH.w && v.posH.y <= v.posH.w &&
		v.posH.z >= 0.f && v.posH.z <= v.posH.w)
	{
		return true;
	}
	return false;
}

//ת����βü��ռ�
VertexOut Tiny3DDeviceContext::TransformToProj(const VertexIn& v)
{
	VertexOut out = m_pShader->VS(v);
	//����oneDivZ
	out.oneDivZ = 1 / out.posH.w;
	//����1/z��x,y�����Թ�ϵ
	//���ｫ��Ҫ��ֵ����Ϣ������1/z �õ� s/z��t/z�ȣ������դ���׶ν��в�ֵ
	out.color.x *= out.oneDivZ;
	out.color.y *= out.oneDivZ;
	out.color.z *= out.oneDivZ;

	out.normal.x *= out.oneDivZ;
	out.normal.y *= out.oneDivZ;
	out.normal.z *= out.oneDivZ;

	out.tex.u *= out.oneDivZ;
	out.tex.v *= out.oneDivZ;

	return out;
}

//ת������Ļ����
void Tiny3DDeviceContext::TransformToScreen(const ZCMatrix& m, VertexOut& v)
{
	v.posH = v.posH * m;
}

//��������
bool Tiny3DDeviceContext::BackFaceCulling(const VertexIn& v1, const VertexIn& v2, const VertexIn& v3)
{
	//�߿�ģʽ�����б�������
	if (m_renderMode == TINY3D_FILL_WIREFRAME)
	{
		return true;
	}
	else
	{
		ZCVector vector1 = v2.pos - v1.pos;
		ZCVector vector2 = v3.pos - v2.pos;
		//���㻺����˳��Ϊ˳ʱ��
		//����õ��ķ���������ϵһ��
		ZCVector normal = vector1.Cross(vector2);

		ZCVector viewDir = v1.pos - m_cameraPos;
		if (normal.Dot(viewDir) < 0)
		{
			return true;
		}
		return false;
	}
}

//��������
void Tiny3DDeviceContext::DrawTriangle(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3)
{
	//�߿�ģʽ
	if (m_renderMode == TINY3D_FILL_WIREFRAME)
	{
		BresenhamDrawLine(v1.posH.x, v1.posH.y, v2.posH.x, v2.posH.y);
		BresenhamDrawLine(v1.posH.x, v1.posH.y, v3.posH.x, v3.posH.y);
		BresenhamDrawLine(v2.posH.x, v2.posH.y, v3.posH.x, v3.posH.y);
	}
	else if (m_renderMode == TINY3D_FILL_SOLIDE)
	{
		TriangleRasterization(v1, v2, v3);
	}

}

//bresenham����
void Tiny3DDeviceContext::BresenhamDrawLine(int x1, int y1, int x2, int y2)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	int stepx = 1;
	int stepy = 1;

	if (dx >= 0)
	{
		stepx = 1;
	}
	else
	{
		stepx = -1;
		dx = abs(dx);
	}

	if (dy >= 0)
	{
		stepy = 1;
	}
	else
	{
		stepy = -1;
		dy = abs(dy);
	}

	int deltaX = 2 * dx;
	int deltaY = 2 * dy;
	if (dx > dy)
	{
		int error = deltaY - dx;
		for (int i = 0; i <= dx; ++i)
		{
			if(x1 >= 0 && x1 < m_pDevice->GetClientWidth() && y1 >= 0 && y1 < m_pDevice->getClientHeight())
				m_pDevice->DrawPixel(x1, y1, ZCVector(0.f, 0.f, 0.f,1.f));
			if (error >= 0)
			{
				error -= deltaX;
				y1 += stepy;
			}
			error += deltaY;
			x1 += stepx;
		}
	}
	else
	{
		int error = deltaX - dy;
		for (int i = 0; i <= dy; i++)
		{
			if (x1 >= 0 && x1 < m_pDevice->GetClientWidth() && y1 >= 0 && y1 < m_pDevice->getClientHeight())
				m_pDevice->DrawPixel(x1, y1, ZCVector(0.f, 0.f, 0.f,1.f));
			if (error >= 0)
			{
				error -= deltaY;
				x1 += stepx;
			}
			error += deltaX;
			y1 += stepy;
		}
	}
}

//ɨ�������
//left ��˵�  right �Ҷ˵�
void Tiny3DDeviceContext::ScanlineFill(const VertexOut& left, const VertexOut& right,  int yIndex)
{
	float dx = right.posH.x - left.posH.x;

	for (float x = left.posH.x; x <= right.posH.x; x += 1.f)
	{
		//��������
		int xIndex = static_cast<int>(x + .5f);
		
		if(xIndex >= 0 && xIndex < m_pDevice->GetClientWidth())
		{
			//��ֵϵ��
			float lerpFactor = 0;
			if (dx != 0)
			{
				lerpFactor = (x - left.posH.x) / dx;
			}

			//��Ȳ���
			//1/z����x����y'�����Թ�ϵ��
			float oneDivZ = MathUtil::Lerp(left.oneDivZ, right.oneDivZ, lerpFactor);
			if (oneDivZ >= m_pDevice->GetZ(xIndex,yIndex))
			{
				m_pDevice->SetZ(xIndex, yIndex, oneDivZ);

				float w = 1 / oneDivZ;
				//��ֵ���� ԭ����Ҫ��ֵ����Ϣ������oneDivZ
				//���ڵõ���ֵ�����Ϣ��Ҫ����oneDivZ�õ���ʵֵ
				VertexOut out = MathUtil::Lerp(left, right, lerpFactor);
				out.posH.y = yIndex;
				out.tex.u *= w;
				out.tex.v *= w;
				out.normal.x *= w;
				out.normal.y *= w;
				out.normal.z *= w;
				out.color.x *= w;
				out.color.y *= w;
				out.color.z *= w;
				//�����ص���ɫ
				m_pDevice->DrawPixel(xIndex, yIndex, m_pShader->PS(out));
			}			
		}	
	}
}

//��ƽ�������� v3Ϊ�¶���
//y����ÿ������һ������ ����y��ֵ����

void Tiny3DDeviceContext::DrawTriangleTop(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3)
{
	float dy = 0;//ÿ��y����һ������
	for (float y = v1.posH.y; y <= v3.posH.y; y += 1.f)
	{
		//��������
		int yIndex = static_cast<int>(y + 0.5f);
		if (yIndex >= 0 && yIndex < m_pDevice->getClientHeight())
		{
			float t = dy / (v3.posH.y - v1.posH.y);

			//��ֵ�������Ҷ���
			VertexOut new1 = MathUtil::Lerp(v1, v3, t);
			VertexOut new2 = MathUtil::Lerp(v2, v3, t);
			dy += 1.f;
			//ɨ�������
			if (new1.posH.x < new2.posH.x)
			{
				ScanlineFill(new1, new2, yIndex);
			}
			else
			{
				ScanlineFill(new2, new1, yIndex);
			}
		}
		
	}
}

//��ƽ�������� v1Ϊ�϶���
void Tiny3DDeviceContext::DrawTriangleBottom(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3)
{
	float dy = 0;//ÿ��y����һ������
	for (float y = v1.posH.y; y <= v2.posH.y; y += 1.f)
	{
		//��������
		int yIndex = static_cast<int>(y + 0.5f);

		if (yIndex >= 0 && yIndex < m_pDevice->getClientHeight())
		{
			float t = dy / (v2.posH.y - v1.posH.y);

			//��ֵ���Ҷ���
			VertexOut new1 = MathUtil::Lerp(v1, v2, t);
			VertexOut new2 = MathUtil::Lerp(v1, v3, t);
			dy += 1.f;

			//ɨ�������
			if (new1.posH.x < new2.posH.x)
			{
				ScanlineFill(new1, new2, yIndex);
			}
			else
			{
				ScanlineFill(new2, new1, yIndex);
			}
		}
	}
}

//��դ��������
void Tiny3DDeviceContext::TriangleRasterization(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3)
{
	//�ж��Ƿ���ƽ�׻���ƽ��������
	if (v1.posH.y == v2.posH.y)
	{	
		if (v1.posH.y < v3.posH.y)
		{//ƽ��
			DrawTriangleTop(v1, v2, v3);
		}
		else
		{//ƽ��
			DrawTriangleBottom(v3, v1, v2);
		}
	}
	else if (v1.posH.y == v3.posH.y)
	{
		if (v1.posH.y < v2.posH.y)
		{//ƽ��
			DrawTriangleTop(v1, v3, v2);
		}
		else
		{//ƽ��
			DrawTriangleBottom(v2, v1, v3);
		}
	}
	else if (v2.posH.y == v3.posH.y)
	{
		if (v2.posH.y < v1.posH.y)
		{//ƽ��
			DrawTriangleTop(v2, v3, v1);
		}
		else
		{//ƽ��
			DrawTriangleBottom(v1, v2, v3);
		}
	}
	//һ�������� ����ָ��ƽ�������κ�ƽ��������
	else
	{
		//����yֵ��������������
		std::vector<VertexOut> vertices{v1,v2,v3};
		std::sort(vertices.begin(), vertices.end(), [](VertexOut v1,VertexOut v2) {
			return v1.posH.y < v2.posH.y;});
		VertexOut top = vertices[0];
		VertexOut middle = vertices[1];
		VertexOut bottom = vertices[2];

		//��ֵ���м��
		float middleX = (middle.posH.y - top.posH.y) * (bottom.posH.x - top.posH.x) /
			(bottom.posH.y - top.posH.y) + top.posH.x;
		float dy = middle.posH.y - top.posH.y;
		float t = dy / (bottom.posH.y - top.posH.y);
		
		VertexOut newMiddle = MathUtil::Lerp(top, bottom, t);
		newMiddle.posH.x = middleX;
		newMiddle.posH.y = middle.posH.y;

		//ƽ��
		DrawTriangleTop(middle, newMiddle, bottom);
		//ƽ��
		DrawTriangleBottom(top, middle, newMiddle);
	}
}

