#include "stdafx.h"
#include "ModelGl.h"
#include "glm/gtx/euler_angles.hpp"



/***********************************************************************
	функция:			ModelGl()
	назначение:			Конструктор класса по умолчанию
	входные данные:		нет
	выходные данные:	нет
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

	//модель
	modelPositX = 0;
	modelPositY = 0;
	modelPositZ = 0;
	modelPitch = 0;
	modelHeading = 0;
	modelRoll = 0;
}

/***********************************************************************
	функция:			SetViewMatrix()
	назначение:			Задание матрицы вида
	входные данные:		m - матрица вида
	выходные данные:	нет
**********************************************************************/
void ModelGl::SetViewMatrix(mat4 m)
{
	matrixView = m;
}

/***********************************************************************
	функция:			GetViewMatrix()
	назначение:			возврацает матрицу вида
	входные данные:		нет
	выходные данные:	matrixView - матрица вида
**********************************************************************/
mat4 ModelGl::GetViewMatrix() const
{
	return matrixView;
}

/***********************************************************************
	функция:			GetViewMatrix()
	назначение:			возврацает матрицу переноса вида
	входные данные:		нет
	выходные данные:	matrixView - матрица вида
**********************************************************************/
mat4 ModelGl::GetViewMatrTrans() const
{
	return matrixViewTransl;
}

/***********************************************************************
	функция:			SetViewMatrix()
	назначение:			Задание матрицы модели
	входные данные:		m - матрица модели
	выходные данные:	нет
**********************************************************************/
void ModelGl::SetModelMatrix(mat4 m)
{
	matrixModel = m;
}

/***********************************************************************
	функция:			GetViewMatrix()
	назначение:			возврацает матрицу модели
	входные данные:		нет
	выходные данные:	matrixView - матрица модели
**********************************************************************/
mat4 ModelGl::GetModelMatrix()
{
	return matrixModel;
}


/***********************************************************************
	функция:			TranslateMatrix()
	назначение:			Перенос исходной матрицы
	входные данные:		startMatr - исходная матрица
						x, y,z - параметры переноса
						viewModel - матрица модели или вида
						1 - вида
						2 - модели
	выходные данные:	нет
**********************************************************************/
void ModelGl::TranslateMatrix(float x, float y, float  z, mat4& startMatr)
{
	const vec3 xlate = vec3(x, y,  z);
	startMatr = translate(startMatr, xlate);
}

/***********************************************************************
	функция:			RotateMatrixZ()
	назначение:			Вращение исходной матрицы в последовательности
						ось Z, Y, X
	входные данные:		startMatr - исходная матрица
						rx, ry,rz - параметры вращения
	выходные данные:	нет
**********************************************************************/
void ModelGl::RotateMatrixZ(float rx, float ry, float rz, mat4& startMatr)
{
	startMatr = rotate(startMatr, radians(rz), vec3(0, 0, 1));
	startMatr = rotate(startMatr, radians(ry), vec3(0, 1, 0));
	startMatr = rotate(startMatr, radians(rx), vec3(1, 0, 0));
}

/***********************************************************************
	функция:			RotateMatrixZ()
	назначение:			Вращение исходной матрицы в последовательности
						ось X, Y, Z
	входные данные:		startMatr - исходная матрица
						rx, ry,rz - параметры вращения
	выходные данные:	нет
**********************************************************************/
void ModelGl::RotateMatrixX(float rx, float ry, float rz, mat4& startMatr)
{
	startMatr = rotate(startMatr, radians(rx), vec3(1, 0, 0));
	startMatr = rotate(startMatr, radians(ry), vec3(0, 1, 0));
	startMatr = rotate(startMatr, radians(rz), vec3(0, 0, 1));
}

/***********************************************************************
	функция:			SetPositionCamera()
	назначение:			Запомнить позицию камеры 
	входные данные:		x, y,z - позиция камеры
	выходные данные:	нет
**********************************************************************/
void ModelGl::SetPositionCamera(float x, float y, float z)
{
	cameraPositX = x;
	cameraPositY = y;
	cameraPositZ = z;
}

/***********************************************************************
	функция:			SetPositionCamera()
	назначение:			Возвратить позицию камеры 
	входные данные:		x, y,z - позиция камеры
	выходные данные:	нет
**********************************************************************/
void ModelGl::GetPositionCamera(float& x, float& y, float& z) const
{
	x = cameraPositX;
	y = cameraPositY;
	z = cameraPositZ;
}

/***********************************************************************
	функция:			SetRotationCamera()
	назначение:			Запомнить позицию камеры вращения
	входные данные:		rx, ry,rz - позиция камеры
	выходные данные:	нет
**********************************************************************/
void ModelGl::SetRotationCamera(float rx, float ry, float rz)
{
	pitch = rx;
	heading = ry;
	roll = rz;
}

/***********************************************************************
	функция:			SetRotationCamera()
	назначение:			Возратить позицию камеры вращения
	входные данные:		rx, ry,rz - позиция камеры
	выходные данные:	нет
**********************************************************************/
void ModelGl::GetRotationCamera(float& rx, float& ry, float& rz) const
{
	rx = pitch;
	ry = heading;
	rz = roll;
}

/***********************************************************************
	функция:			SetPositionModel()
	назначение:			Запомнить позицию модели
	входные данные:		x, y,z - позиция модели
	выходные данные:	нет
**********************************************************************/
void ModelGl::SetPositionModel(float x, float y, float z)
{
	modelPositX = x;
	modelPositY = y;
	modelPositZ = z;
}

/***********************************************************************
	функция:			GetPositionModel()
	назначение:			Возвратить позицию модели
	входные данные:		x, y,z - позиция модели
	выходные данные:	нет
**********************************************************************/
void ModelGl::GetPositionModel(float& x, float& y, float& z) const
{
	x = modelPositX;
	y = modelPositY;
	z = modelPositZ;
}

/***********************************************************************
	функция:			SetRotationCamera()
	назначение:			Запомнить позицию модели вращения
	входные данные:		rx, ry,rz - позиция модели
	выходные данные:	нет
**********************************************************************/
void ModelGl::SetRotationModel(float rx, float ry, float rz)
{
	modelPitch = rx;
	modelHeading = ry;
	modelRoll = rz;
}

/***********************************************************************
	функция:			SetRotationCamera()
	назначение:			Возратить позицию модели вращения
	входные данные:		rx, ry,rz - позиция камеры
	выходные данные:	нет
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
	функция:			RotateCamera()
	назначение:			угол поворота при движении мышью
	входные данные:		x, y - позиция мыши
	выходные данные:	нет
**********************************************************************/
void ModelGl::RotateCamera(float x, float y)
{
	pitch += (y - mouseY) ;
	heading += (x  - mouseX);

	mouseX = x ;
	mouseY = y ;
}

/***********************************************************************
	функция:			SetMouse()
	назначение:			Инициализация позиции мыши при вращении камеры
	входные данные:		x, y - начальная позиция мыши
	выходные данные:	нет
**********************************************************************/
void ModelGl::SetMouse(float x, float y)
{
	mouseX = x;
	mouseY = y;
}
