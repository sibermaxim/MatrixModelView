#include "stdafx.h"
#include "DrawFrustum.h"

#include "RenderMesh.h"

void FrustumDraw::DrawFrustum(float fov, float aspectRatio, float nearPlane, float farPlane, shared_ptr<RenderMesh> pRender) const
{
	const float tangent = tanf(radians(fov / 2));
	const float nearHeight = nearPlane * tangent;
	const float nearWidth = nearPlane * aspectRatio;
	const float farHeight = farPlane * tangent;
	const float farWidth = farHeight * aspectRatio;


	const uint32 m_vertexCount = 8;
	const uint32 m_indexCount = 8;
	unsigned int* indices = new unsigned[m_indexCount];
	VertexType* vertices = new VertexType[m_vertexCount];

	for (int i = 0; i < 8; i++)
		indices[i] = i;

	//верхне правый
	vertices[0].x = nearWidth;		vertices[0].y = nearHeight;			vertices[0].z = -nearPlane;
	vertices[0].r = 1.0;			vertices[0].g = 1.0;				vertices[0].b = 1.0;
	//верхне левый
	vertices[1].x = -nearWidth;		vertices[1].y = nearHeight;			vertices[1].z = -nearPlane;
	vertices[1].r = 1.0;			vertices[1].g = 1.0;				vertices[1].b = 1.0;
	//нижне левый
	vertices[2].x = -nearWidth;		vertices[2].y = -nearHeight;		vertices[2].z = -nearPlane;
	vertices[2].r = 1.0;			vertices[2].g = 1.0;				vertices[2].b = 1.0;
	//нижне правый
	vertices[3].x = nearWidth;		vertices[3].y = -nearHeight;		vertices[3].z = -nearPlane;
	vertices[3].r = 1.0;			vertices[3].g = 1.0;				vertices[3].b = 1.0;
	//верхне правый дальний
	vertices[4].x = farWidth;		vertices[4].y = farHeight;			vertices[4].z = -farPlane;
	vertices[4].r = 1.0;			vertices[4].g = 1.0;				vertices[4].b = 1.0;
	//верхне левый дальний
	vertices[5].x = -farWidth;		vertices[5].y = farHeight;			vertices[5].z = -farPlane;
	vertices[5].r = 1.0;			vertices[5].g = 1.0;				vertices[5].b = 1.0;
	//нижний левый дальний
	vertices[6].x = -farWidth;		vertices[6].y = -farHeight;			vertices[6].z = -farPlane;
	vertices[6].r = 1.0;			vertices[6].g = 1.0;				vertices[6].b = 1.0;
	//нижний правый дальний
	vertices[7].x = farWidth;		vertices[7].y = -farHeight;			vertices[7].z = -farPlane;
	vertices[7].r = 1.0;			vertices[7].g = 1.0;				vertices[7].b = 1.0;

	pRender->BindBuffer(vertices, m_vertexCount * sizeof(VertexType), indices,
		m_indexCount * sizeof(uint32), GL_QUADS);

	for(int i=0; i<4; i++)
	{
		indices[2 * i] = i;
		indices[2 * i + 1] = i + 4;
	}
	pRender->BindBuffer(vertices, m_vertexCount * sizeof(VertexType), indices,
		m_indexCount * sizeof(uint32), GL_LINES);
	
	delete[]vertices;
	delete[] indices;
}
