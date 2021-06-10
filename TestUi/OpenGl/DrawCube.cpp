#include "stdafx.h"
#include "DrawCube.h"
#include "RenderMesh.h"
#include <vector>

Cube::Cube()
{
}

void Cube::DrawCube(shared_ptr<RenderMesh> pRender)
{
	vector<VertexType>vertices;
	vector<unsigned>indices;

	VertexType vertLoc;

	vertLoc.x = -3.0f;
	vertLoc.y = 0.0f;
	vertLoc.z = 1.77f;
	vertLoc.r = 0.929524f;
	vertLoc.g = 0.796542f;
	vertLoc.b = 0.178823f;
	vertices.push_back(vertLoc);

	vertLoc.x = -3.0f;
	vertLoc.y = 2.4f;
	vertLoc.z = 1.77f;
	vertLoc.r = 0.929524f;
	vertLoc.g = 0.796542f;
	vertLoc.b = 0.178823f;
	vertices.push_back(vertLoc);
	
	vertLoc.x = 3.0f;
	vertLoc.y = 2.4f;
	vertLoc.z = 1.77f;
	vertLoc.r = 0.929524f;
	vertLoc.g = 0.796542f;
	vertLoc.b = 0.178823f;
	vertices.push_back(vertLoc);
	
	vertLoc.x = 3.0f;
	vertLoc.y = 0.0f;
	vertLoc.z = 1.77f;
	vertLoc.r = 0.929524f;
	vertLoc.g = 0.796542f;
	vertLoc.b = 0.178823f;
	vertices.push_back(vertLoc);

	vertLoc.x = -3.0f;
	vertLoc.y = 0.0f;
	vertLoc.z = -1.77f;
	vertLoc.r = 0.929524f;
	vertLoc.g = 0.796542f;
	vertLoc.b = 0.178823f;
	vertices.push_back(vertLoc);

	vertLoc.x = -3.0f;
	vertLoc.y = 2.4f;
	vertLoc.z = -1.77f;
	vertLoc.r = 0.929524f;
	vertLoc.g = 0.796542f;
	vertLoc.b = 0.178823f;
	vertices.push_back(vertLoc);

	vertLoc.x = 3.0f;
	vertLoc.y = 2.4f;
	vertLoc.z = -1.77f;
	vertLoc.r = 0.929524f;
	vertLoc.g = 0.796542f;
	vertLoc.b = 0.178823f;
	vertices.push_back(vertLoc);

	vertLoc.x = 3.0f;
	vertLoc.y = 0.0f;
	vertLoc.z = -1.77f;
	vertLoc.r = 0.929524f;
	vertLoc.g = 0.796542f;
	vertLoc.b = 0.178823f;
	vertices.push_back(vertLoc);

	//перед
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(3);

	//правый
	indices.push_back(3);
	indices.push_back(2);
	indices.push_back(6);
	indices.push_back(3);
	indices.push_back(6);
	indices.push_back(7);
	
	//задний
	indices.push_back(4);
	indices.push_back(5);
	indices.push_back(6);
	indices.push_back(4);
	indices.push_back(6);
	indices.push_back(7);

	//левый
	indices.push_back(4);
	indices.push_back(5);
	indices.push_back(1);
	indices.push_back(4);
	indices.push_back(1);
	indices.push_back(0);
	
	//вверх
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(6);
	indices.push_back(1);
	indices.push_back(6);
	indices.push_back(5);

	//низ
	indices.push_back(0);
	indices.push_back(3);
	indices.push_back(7);
	indices.push_back(0);
	indices.push_back(4);
	indices.push_back(7);

	pRender->BindBuffer(vertices.data(), vertices.size() * sizeof(VertexType),
		indices.data(), indices.size() * sizeof(unsigned), GL_TRIANGLES);
}
