#pragma once
#include <memory>

#include "ModelGl.h"
#include "RenderMesh.h"

class FrustumDraw:public ModelGl
{
public:
	void DrawFrustum(float fov, float aspectRatio, float nearPlane, float farPlane, shared_ptr<RenderMesh> pRender) const;
};
 