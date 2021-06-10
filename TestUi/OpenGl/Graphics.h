#pragma once

#include <windows.h>
#include <glm/gtc/matrix_transform.hpp>

#include "colorshaderclass.h"
#include "ModelGl.h"
#include "RenderMesh.h"

//#pragma comment(lib, "glew32.lib")
//#pragma comment(lib, "Opengl32.lib")

#define GL_CHECK_ERRORS assert(glGetError()== GL_NO_ERROR);

using namespace glm;

const float FOV_Y = 60.0f;              // vertical FOV in degree
const float CAMERA_ANGLE_X = 45.0f;			// pitch in degree
const float CAMERA_ANGLE_Y = -0.0f;			// heading in degree
const float CAMERA_DISTANCE = 25.0f;		// camera distance

class DrawGrd;
class Cube;
class FrustumDraw;

class CGraphics
{
public:

	CGraphics(CWnd* pWnd, int width, int height);
	~CGraphics();

	bool InitializeGraphics();

	void Renderer();
//	void UpdateViewMatrix(int x, int y, int z, int pitch, int heading, int roll);

	void TranslateMatrixView(float x, float y, float z);
	void RotateMatrixView(float rx, float ry, float rz);
	void TranslateMatrixWorld(float x, float y, float z);
	void RotateMatrixWorld(float rx, float ry, float rz);

	void OnSize(int m_width, int m_height);
	
	void SetCameraPosition(float x, float y, float z, float rx, float ry, float rz, bool bln = false);

	void MouseMove(float x, float y);
	void SetMouse(float x, float y) const;
	
private:

	CWnd* p_Wnd;
	HWND m_hwnd;
	
	unique_ptr<ColorShaderClass> p_shader;
	int width, height;

	//матрицы проекции
	mat4 matrixProject1, matrixProject2;
	//матрицы вида
	mat4 matrixView1, matrixView2;

	//обеъекты вывода
	unique_ptr<DrawGrd> pDrawGrd;
	unique_ptr<Cube> pDrawCubePers;

	unique_ptr<DrawGrd> pDrawGrdPerson;
	unique_ptr<Cube> pDrawCubePersModel;
	unique_ptr<FrustumDraw> pDrawFrustum;

	shared_ptr<RenderMesh> pRenderMesh;

	void DrawSub1();
	void DrawSub2();

	void SetViewPortSub(float fov, int x, int y, int width, int heigth, float nearPlane, float farPlane, bool bln = false);

	void DisplayMatrixView(mat4 m);
	void DisplayMatrixModel(mat4 m);
	void DisplayMatrixViewModel();
}; 