#pragma once
#include <memory>

#include "ModelGl.h"
#include "RenderMesh.h"


class DrawGrd: public ModelGl
{
public:

	DrawGrd();
	void GridDraw(int size, float step, shared_ptr<RenderMesh> pRenderMesh);

};
