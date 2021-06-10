#include "stdafx.h"
#include "DrawGrid.h"

#include <vector>

/***********************************************************************
	функция:			DrawGrd()
	назначение:			конструктор класса
	входные данные:		нет
	выходные данные:	нет
**********************************************************************/
DrawGrd::DrawGrd()
{
}

/***********************************************************************
	функция:			GridDraw()
	назначение:			Рисование сетки
	входные данные:		size - размер сетки
						step - шаг сетки
	выходные данные:	нет
**********************************************************************/
void DrawGrd::GridDraw(int size, float step, shared_ptr<RenderMesh> pRender)
{
	vector<VertexType>vertices;
	vector<uvec4>indices;

	for (int i = -size; i <= size; i += step)
	{
		for (int j = -size; j <= size; j += step)
		{
			VertexType vertLoc;
			vertLoc.x = j;
			vertLoc.y = 0.0f;
			vertLoc.z = i;
			vertLoc.r = 1.0f;
			vertLoc.g = 1.0f;
			vertLoc.b = 1.0f;

			vertices.push_back(vertLoc);
		}
	}

	for (int j = 0; j<2 * size / step; j++)
	{
		for (int i = 0; i<2 * size / step; i++)
		{
			const int row1 = j * (2 * size / step + 1);
			const int row2 = (j + 1) * (2 * size + 1);

			indices.push_back(uvec4(row1 + i, row1 + i + 1, row1 + i + 1, row2 + i + 1));
			indices.push_back(glm::uvec4(row2 + i + 1, row2 + i, row2 + i, row1 + i));
		}
	}

	pRender->BindBuffer(vertices.data(), vertices.size() * sizeof(VertexType), indices.data(), indices.size() * sizeof(uvec4), GL_LINES);
}
