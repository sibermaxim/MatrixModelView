#pragma once
#include <memory>

#include "ModelGl.h"
#include "RenderMesh.h"

class Cube : public ModelGl
{
public:
	
	Cube();
	void DrawCube(shared_ptr<RenderMesh> pRender);
};
