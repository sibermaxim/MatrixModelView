#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <gl/glew.h>

using namespace glm;
using namespace std;

const int FAR_PLANE = 10;
const int NEARE_PLANE = 1;

struct meshModel
{
	uint32 indexCount;
	unsigned int m_vertexArrayId;
};

class ModelGl
{
	mat4 matrixView, matrixModel;

	//позиция и поворот камеры 
	float cameraPositX, cameraPositY, cameraPositZ;
	float pitch, heading, roll;

	//позиция и поворот модели 
	float modelPositX, modelPositY, modelPositZ;
	float modelPitch, modelHeading, modelRoll;
	
	//начальная позия мыши при вращении камеры
	float mouseX, mouseY;

	mat4 matrixViewRot, matrixViewTransl;;
	
	mat4 matrixModelRot;
	
	mat4 matrixProject;

	
public:

	ModelGl();

	void SetViewMatrix(mat4 m);
	mat4 GetViewMatrix() const;

	mat4 GetViewMatrTrans() const;

	void SetModelMatrix(mat4 m);
	mat4 GetModelMatrix();
	
	void TranslateMatrix(float x, float y, float z, mat4& startMatr);
	void RotateMatrixZ(float rx, float ry, float rz, mat4& startMatr);
	void RotateMatrixX(float rx, float ry, float rz, mat4& startMatr);
	
	void SetPositionCamera(float x, float y, float z);
	void GetPositionCamera(float& x, float& y, float& z) const;
	void SetRotationCamera(float rx, float ry, float rz);
	void GetRotationCamera(float& rx, float& ry, float& rz) const;
	
	void SetPositionModel(float x, float y, float z);
	void GetPositionModel(float& x, float& y, float& z) const;
	void SetRotationModel(float rx, float ry, float rz);
	void GetRotationModel(float& rx, float& ry, float& rz) const;

	void SedWorldMatrix(float m[16]);

	void RotateCamera(float x, float y);
	void SetMouse(float x, float y);
	
};
