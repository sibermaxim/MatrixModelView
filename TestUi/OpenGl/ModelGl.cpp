#include "stdafx.h"
#include "ModelGl.h"
#include "glm/gtx/euler_angles.hpp"



/***********************************************************************
	�������:			ModelGl()
	����������:			����������� ������ �� ���������
	������� ������:		���
	�������� ������:	���
**********************************************************************/
ModelGl::ModelGl()
	: cameraPositX(0),
	  cameraPositY(0),
	  cameraPositZ(0), pitch(0), heading(0), roll(0), mouseX(0), mouseY(0),
	  matrixProject()
{
	matrixView = mat4(1.0);
	matrixModel = mat4(1.0);

	matrixViewRot = mat4(1.0);
	matrixViewTransl = mat4(1.0);
	
	matrixModelRot = mat4(1.0);

	//������
	modelPositX = 0;
	modelPositY = 0;
	modelPositZ = 0;
	modelPitch = 0;
	modelHeading = 0;
	modelRoll = 0;
}

/***********************************************************************
	�������:			SetViewMatrix()
	����������:			������� ������� ����
	������� ������:		m - ������� ����
	�������� ������:	���
**********************************************************************/
void ModelGl::SetViewMatrix(mat4 m)
{
	matrixView = m;
}

/***********************************************************************
	�������:			GetViewMatrix()
	����������:			���������� ������� ����
	������� ������:		���
	�������� ������:	matrixView - ������� ����
**********************************************************************/
mat4 ModelGl::GetViewMatrix() const
{
	return matrixView;
}

/***********************************************************************
	�������:			GetViewMatrix()
	����������:			���������� ������� �������� ����
	������� ������:		���
	�������� ������:	matrixView - ������� ����
**********************************************************************/
mat4 ModelGl::GetViewMatrTrans() const
{
	return matrixViewTransl;
}

/***********************************************************************
	�������:			SetViewMatrix()
	����������:			������� ������� ������
	������� ������:		m - ������� ������
	�������� ������:	���
**********************************************************************/
void ModelGl::SetModelMatrix(mat4 m)
{
	matrixModel = m;
}

/***********************************************************************
	�������:			GetViewMatrix()
	����������:			���������� ������� ������
	������� ������:		���
	�������� ������:	matrixView - ������� ������
**********************************************************************/
mat4 ModelGl::GetModelMatrix()
{
	return matrixModel;
}


/***********************************************************************
	�������:			TranslateMatrix()
	����������:			������� �������� �������
	������� ������:		startMatr - �������� �������
						x, y,z - ��������� ��������
						viewModel - ������� ������ ��� ����
						1 - ����
						2 - ������
	�������� ������:	���
**********************************************************************/
void ModelGl::TranslateMatrix(float x, float y, float  z, mat4& startMatr)
{
	const vec3 xlate = vec3(x, y,  z);
	startMatr = translate(startMatr, xlate);
}

/***********************************************************************
	�������:			RotateMatrixZ()
	����������:			�������� �������� ������� � ������������������
						��� Z, Y, X
	������� ������:		startMatr - �������� �������
						rx, ry,rz - ��������� ��������
	�������� ������:	���
**********************************************************************/
void ModelGl::RotateMatrixZ(float rx, float ry, float rz, mat4& startMatr)
{
	startMatr = rotate(startMatr, radians(rz), vec3(0, 0, 1));
	startMatr = rotate(startMatr, radians(ry), vec3(0, 1, 0));
	startMatr = rotate(startMatr, radians(rx), vec3(1, 0, 0));
}

/***********************************************************************
	�������:			RotateMatrixZ()
	����������:			�������� �������� ������� � ������������������
						��� X, Y, Z
	������� ������:		startMatr - �������� �������
						rx, ry,rz - ��������� ��������
	�������� ������:	���
**********************************************************************/
void ModelGl::RotateMatrixX(float rx, float ry, float rz, mat4& startMatr)
{
	startMatr = rotate(startMatr, radians(rx), vec3(1, 0, 0));
	startMatr = rotate(startMatr, radians(ry), vec3(0, 1, 0));
	startMatr = rotate(startMatr, radians(rz), vec3(0, 0, 1));
}

/***********************************************************************
	�������:			SetPositionCamera()
	����������:			��������� ������� ������ 
	������� ������:		x, y,z - ������� ������
	�������� ������:	���
**********************************************************************/
void ModelGl::SetPositionCamera(float x, float y, float z)
{
	cameraPositX = x;
	cameraPositY = y;
	cameraPositZ = z;
}

/***********************************************************************
	�������:			SetPositionCamera()
	����������:			���������� ������� ������ 
	������� ������:		x, y,z - ������� ������
	�������� ������:	���
**********************************************************************/
void ModelGl::GetPositionCamera(float& x, float& y, float& z) const
{
	x = cameraPositX;
	y = cameraPositY;
	z = cameraPositZ;
}

/***********************************************************************
	�������:			SetRotationCamera()
	����������:			��������� ������� ������ ��������
	������� ������:		rx, ry,rz - ������� ������
	�������� ������:	���
**********************************************************************/
void ModelGl::SetRotationCamera(float rx, float ry, float rz)
{
	pitch = rx;
	heading = ry;
	roll = rz;
}

/***********************************************************************
	�������:			SetRotationCamera()
	����������:			��������� ������� ������ ��������
	������� ������:		rx, ry,rz - ������� ������
	�������� ������:	���
**********************************************************************/
void ModelGl::GetRotationCamera(float& rx, float& ry, float& rz) const
{
	rx = pitch;
	ry = heading;
	rz = roll;
}

/***********************************************************************
	�������:			SetPositionModel()
	����������:			��������� ������� ������
	������� ������:		x, y,z - ������� ������
	�������� ������:	���
**********************************************************************/
void ModelGl::SetPositionModel(float x, float y, float z)
{
	modelPositX = x;
	modelPositY = y;
	modelPositZ = z;
}

/***********************************************************************
	�������:			GetPositionModel()
	����������:			���������� ������� ������
	������� ������:		x, y,z - ������� ������
	�������� ������:	���
**********************************************************************/
void ModelGl::GetPositionModel(float& x, float& y, float& z) const
{
	x = modelPositX;
	y = modelPositY;
	z = modelPositZ;
}

/***********************************************************************
	�������:			SetRotationCamera()
	����������:			��������� ������� ������ ��������
	������� ������:		rx, ry,rz - ������� ������
	�������� ������:	���
**********************************************************************/
void ModelGl::SetRotationModel(float rx, float ry, float rz)
{
	modelPitch = rx;
	modelHeading = ry;
	modelRoll = rz;
}

/***********************************************************************
	�������:			SetRotationCamera()
	����������:			��������� ������� ������ ��������
	������� ������:		rx, ry,rz - ������� ������
	�������� ������:	���
**********************************************************************/
void ModelGl::GetRotationModel(float& rx, float& ry, float& rz) const
{
	rx = modelPitch;
	ry = modelHeading;
	rz = modelRoll;
}

void ModelGl::SedWorldMatrix(float m[16])
{
	for(int i=0; i<4; i++)
	{
		matrixModel[i].x = m[4 * i];
		matrixModel[i].y = m[4 * i + 1];
		matrixModel[i].z = m[4 * i + 2];
		matrixModel[i].w = m[4 * i + 3];
	}
}

/***********************************************************************
	�������:			RotateCamera()
	����������:			���� �������� ��� �������� �����
	������� ������:		x, y - ������� ����
	�������� ������:	���
**********************************************************************/
void ModelGl::RotateCamera(float x, float y)
{
	pitch += (y - mouseY) ;
	heading += (x  - mouseX);

	mouseX = x ;
	mouseY = y ;
}

/***********************************************************************
	�������:			SetMouse()
	����������:			������������� ������� ���� ��� �������� ������
	������� ������:		x, y - ��������� ������� ����
	�������� ������:	���
**********************************************************************/
void ModelGl::SetMouse(float x, float y)
{
	mouseX = x;
	mouseY = y;
}
