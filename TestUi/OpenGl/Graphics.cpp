#include "stdafx.h"
#include <iostream>
//#include <gl/glew.h>
#include "Graphics.h"
#include "MainFrm.h"

#include "DrawGrid.h"
#include "DrawFrustum.h"
#include "DrawCube.h"

using namespace std;

CGraphics::CGraphics(CWnd* pWnd, int width, int height)
{
	p_Wnd = pWnd;
	m_hwnd = pWnd->m_hWnd;

	this->width = width;
	this->height = height;

	pDrawGrd = make_unique<DrawGrd>();
	pDrawGrdPerson = make_unique<DrawGrd>();

	pDrawCubePers = make_unique<Cube>();
	pDrawCubePersModel = make_unique<Cube>();
	pDrawFrustum = make_unique<FrustumDraw>();
	
	pRenderMesh = make_shared<RenderMesh>() ;

	p_shader = make_unique<ColorShaderClass>();

	matrixProject1 = mat4(1.0);
	matrixProject2 = mat4(1.0);
	matrixView1 = mat4(1.0);
	matrixView2 = mat4(1.0);
}

CGraphics::~CGraphics()
{
	FreeConsole();
}

bool CGraphics::InitializeGraphics() 
{
	pRenderMesh->InitOpenGl(p_Wnd);
		
	// Initialize the color shader object.
	const bool res = p_shader->Initialize(m_hwnd);
	if (!res)
	{
		MessageBox(m_hwnd, "Could not initialize the color shader object.", "Error", MB_OK);
		return false;
	}
	p_shader->SetShader();

	SetCameraPosition(0, 0, CAMERA_DISTANCE, CAMERA_ANGLE_X, CAMERA_ANGLE_Y, 0, true);

	return true;
}

/***********************************************************************
	функция:			Renderer()
	назначение:			Вывод данных на экран
	входные данные:		x, y, z - параметры смещения
	выходные данные:	нет
**********************************************************************/
void CGraphics::Renderer()
{
	mat4 worldMatrix, viewMatrix;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	DrawSub1();
	viewMatrix = pDrawGrd->GetViewMatrix();
	worldMatrix = pDrawGrd->GetModelMatrix();
	p_shader->SetShaderParameters(worldMatrix, viewMatrix, matrixProject1);
	pDrawGrd->GridDraw(10, 1, pRenderMesh);

	viewMatrix = pDrawCubePers->GetViewMatrix();
	worldMatrix = pDrawCubePers->GetModelMatrix();
	p_shader->SetShaderParameters(worldMatrix, viewMatrix, matrixProject1);
	pDrawCubePers->DrawCube(pRenderMesh);

	DrawSub2();
	viewMatrix = pDrawGrdPerson->GetViewMatrix();
	worldMatrix = pDrawGrdPerson->GetModelMatrix();
	p_shader->SetShaderParameters(worldMatrix, viewMatrix, matrixProject2);
	pDrawGrdPerson->GridDraw(10, 1, pRenderMesh);

	viewMatrix = pDrawCubePersModel->GetViewMatrix();
	worldMatrix = pDrawCubePersModel->GetModelMatrix();
	p_shader->SetShaderParameters(worldMatrix, viewMatrix, matrixProject2);
	pDrawCubePersModel->DrawCube(pRenderMesh);

	viewMatrix = pDrawFrustum->GetViewMatrix();
	worldMatrix = pDrawFrustum->GetModelMatrix();
	p_shader->SetShaderParameters(worldMatrix, viewMatrix, matrixProject2);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	pDrawFrustum->DrawFrustum(60, 1, 1, 10, pRenderMesh);
	glDisable(GL_BLEND);
		
	//отображаем модель
	SwapBuffers(GetDC(m_hwnd));
}

void CGraphics::TranslateMatrixView(float x, float y, float z)
{
	float rx, ry, rz;
	
	mat4 m = mat4(1.0);
	pDrawGrd->GetRotationCamera(rx, ry, rz);
	pDrawGrd->RotateMatrixX(rx, ry, rz, m);
	pDrawGrd->TranslateMatrix(-x, -y, -z, m);
	pDrawGrd->SetViewMatrix(m);
	pDrawGrd->SetPositionCamera(x, y, z);
	pDrawCubePers->SetViewMatrix(m);

	DisplayMatrixView(m);
	
	m = mat4(1.0);
	pDrawFrustum->RotateMatrixZ(-rx, ry, -rz, m);
	pDrawFrustum->TranslateMatrix(x, y, z, m);
	pDrawFrustum->SetModelMatrix(m);

	Renderer();
}

void CGraphics::RotateMatrixView(float rx, float ry, float rz)
{
	float x, y, z;
	
	mat4 m = mat4(1.0);
	pDrawGrd->GetPositionCamera(x, y, z);
	pDrawGrd->RotateMatrixX(rx, ry, rz, m);
	pDrawGrd->TranslateMatrix(-x, -y, -z, m);
	pDrawGrd->SetRotationCamera(rx, ry, rz);
	pDrawGrd->SetViewMatrix(m);
	pDrawCubePers->SetViewMatrix(m);

	DisplayMatrixView(m);

	m = mat4(1.0);
	pDrawFrustum->TranslateMatrix(x, y, z, m);
	pDrawFrustum->RotateMatrixX(-rx, ry, -rz, m);
	pDrawFrustum->SetModelMatrix(m);
	
	Renderer();
}

/***********************************************************************
	функция:			RotateMatrixWorld()
	назначение:			Смещение модели(куба)
	входные данные:		x, y, z - параметры смещения
	выходные данные:	нет
**********************************************************************/
void CGraphics::TranslateMatrixWorld(float x, float y, float z)
{
	float rx, ry, rz;
	
	mat4 m = mat4(1.0);

	pDrawCubePers->GetRotationModel(rx, ry, rz);
	pDrawCubePers->TranslateMatrix(x, y, z, m);
	pDrawCubePers->SetPositionModel(x, y, z);
	pDrawCubePers->RotateMatrixX(rx, ry, rz, m);

	pDrawCubePers->SetModelMatrix(m);
	pDrawCubePersModel->SetModelMatrix(m);
	Renderer();

	DisplayMatrixModel(m);
}

/***********************************************************************
	функция:			RotateMatrixWorld()
	назначение:			Вращение модели(куба)
	входные данные:		rx, ry, rz - параметры вращения
	выходные данные:	нет
**********************************************************************/
void CGraphics::RotateMatrixWorld(float rx, float ry, float rz)
{
	CMainFrame* pFrame = static_cast<CMainFrame*>(AfxGetApp()->m_pMainWnd);
	float x, y, z;

	mat4 m = mat4(1.0);
	pDrawCubePers->SetRotationModel(rx, ry, rz);
	pDrawCubePers->GetPositionModel(x, y, z);
	pDrawCubePers->TranslateMatrix(x, y, z, m);
	pDrawCubePers->RotateMatrixX(rx, ry, rz, m);

	pDrawCubePers->SetModelMatrix(m);
	pDrawCubePersModel->SetModelMatrix(m);
	
	Renderer();
	DisplayMatrixModel(m);
}

/***********************************************************************
	функция:			OnSize()
	назначение:			изменение размеров экрана
	входные данные:		m_width, m_height - новые размеры
	выходные данные:	нет
**********************************************************************/
void CGraphics::OnSize(int m_width, int m_height)
{
	width = m_width;
	height = m_height;
	Renderer();
}

/***********************************************************************
	функция:			DrawGrd()
	назначение:			конструктор класса
	входные данные:		нет
	выходные данные:	нет
**********************************************************************/
void CGraphics::DrawSub1()
{
	const int poWidth = width / 2;
	if (height > poWidth)
		SetViewPortSub(60, 0, (height - poWidth)/2, poWidth, poWidth, NEARE_PLANE, FAR_PLANE);
	else
	{
		SetViewPortSub(60, (poWidth - height) / 2, 0, height, height, NEARE_PLANE, FAR_PLANE);
	}
}

/***********************************************************************
	функция:			DrawGrd()
	назначение:			конструктор класса
	входные данные:		нет
	выходные данные:	нет
**********************************************************************/
void CGraphics::DrawSub2()
{
	const int poWidth = width / 2;
	
	SetViewPortSub(60, poWidth, 0, poWidth, height, NEARE_PLANE, 100, true);
}

void CGraphics::SetViewPortSub(float fov, int x, int y, int mwidth, int mheight, float nearPlane, float farPlane, bool bln)
{
	glViewport(x, y, mwidth, mheight);
	glScissor(x, y, mwidth, mheight);
	
	if(!bln)
		matrixProject1 = perspective(radians(fov), static_cast<float>(mwidth) / static_cast<float>(mheight), nearPlane, farPlane);
	else
		matrixProject2 = perspective(radians(fov), static_cast<float>(mwidth) / static_cast<float>(mheight), nearPlane, farPlane);
}

/***********************************************************************
	функция:			DisplayMatrixView()
	назначение:			отобразить матрицу вида
	входные данные:		m - матрица вида
	выходные данные:	нет
**********************************************************************/
void CGraphics::DisplayMatrixView(mat4 m)
{
	auto pFrame = dynamic_cast<CMainFrame*>(AfxGetApp()->m_pMainWnd);

	float mm[16];
	for (int i = 0; i < 4; i++)
	{
		mm[4 * i] = m[i].x;
		mm[4 * i + 1] = m[i].y;
		mm[4 * i + 2] = m[i].z;
		mm[4 * i + 3] = m[i].w;
	}
	pFrame->m_wndDlgBar.DisplayViewMatrix(mm);
	DisplayMatrixViewModel();
}

/***********************************************************************
	функция:			DisplayMatrixView()
	назначение:			отобразить матрицу модели
	входные данные:		m - матрица модели
	выходные данные:	нет
**********************************************************************/
void CGraphics::DisplayMatrixModel(mat4 m)
{
	auto pFrame = dynamic_cast<CMainFrame*>(AfxGetApp()->m_pMainWnd);

	float mm[16];
	for (int i = 0; i < 4; i++)
	{
		mm[4 * i] = m[i].x;
		mm[4 * i + 1] = m[i].y;
		mm[4 * i + 2] = m[i].z;
		mm[4 * i + 3] = m[i].w;
	}
	pFrame->m_wndDlgBar.DisplayModelMatrix(mm);
	DisplayMatrixViewModel();
}

/***********************************************************************
	функция:			DisplayMatrixView()
	назначение:			отобразить матрицу модели вида
	входные данные:		m - матрица модели вида
	выходные данные:	нет
**********************************************************************/
void CGraphics::DisplayMatrixViewModel()
{
	auto pFrame = dynamic_cast<CMainFrame*>(AfxGetApp()->m_pMainWnd);
	mat4 mView = pDrawGrd->GetViewMatrix();
	mat4 mMod = pDrawCubePers->GetModelMatrix();

	mView = mView * mMod;
	
	float mm[16];
	for (int i = 0; i < 4; i++)
	{
		mm[4 * i] = mView[i].x;
		mm[4 * i + 1] = mView[i].y;
		mm[4 * i + 2] = mView[i].z;
		mm[4 * i + 3] = mView[i].w;
	}
	pFrame->m_wndDlgBar.DisplayViewModelMatrix(mm);
}

/***********************************************************************
	функция:			DrawGrd()
	назначение:			конструктор класса
	входные данные:		нет
	выходные данные:	нет
**********************************************************************/
void CGraphics::SetCameraPosition(float x, float y, float z, float rx, float ry, float rz, bool bln)
{
	if (bln)
	{
		mat4 m = mat4(1.0);

		pDrawGrdPerson->SetModelMatrix(m);
		pDrawCubePersModel->SetModelMatrix(m);

		pDrawGrdPerson->TranslateMatrix(-x, -y, -z, m);
		pDrawGrdPerson->RotateMatrixX(rx, ry, rz, m);

		pDrawGrdPerson->SetViewMatrix(m);
		pDrawCubePersModel->SetViewMatrix(m);
		pDrawFrustum->SetViewMatrix(m);
		
		pDrawGrdPerson->SetRotationCamera(rx, ry, rz);
		pDrawGrdPerson->SetPositionCamera(x, y, z);
		
	}
	else
	{
		mat4 m = mat4(1.0);

		pDrawGrd->SetModelMatrix(m);
		DisplayMatrixModel(m);
		pDrawCubePers->SetModelMatrix(m);
		pDrawCubePers->SetPositionModel(0, 0, 0);
		pDrawCubePers->SetRotationModel(0, 0, 0);

		pDrawGrd->TranslateMatrix(-x, -y, -z, m);
		pDrawGrd->RotateMatrixX(rx, ry, rz, m);

		pDrawCubePers->SetViewMatrix(m);
		pDrawGrd->SetViewMatrix(m);
		DisplayMatrixView(m);
		
		m = mat4(1.0);
		pDrawFrustum->TranslateMatrix(x, y, z, m);
		pDrawFrustum->SetModelMatrix(m);
		pDrawGrd->SetRotationCamera(rx, ry, rz);
		pDrawGrd->SetPositionCamera(x, y, z);
	}
}

/***********************************************************************
	функция:			MouseMove()
	назначение:			Получение угла поворота в зависимости от сдвига мыши
	входные данные:		x, y - сдвиг мыши
	выходные данные:	нет
**********************************************************************/
void CGraphics::MouseMove(float x, float y)
{
	float posX, posY, posZ;
	
	mat4 m = mat4(1.0);
	pDrawGrdPerson->GetPositionCamera(posX, posY, posZ);
	pDrawGrdPerson->TranslateMatrix(-posX, -posY, -posZ, m);
	pDrawGrdPerson->RotateCamera(x, y);
		
	pDrawGrdPerson->GetRotationCamera(posX, posY, posZ);
	pDrawGrdPerson->RotateMatrixX(posX, posY, posZ, m);

	pDrawCubePersModel->SetViewMatrix(m);
	pDrawGrdPerson->SetViewMatrix(m);
	pDrawFrustum->SetViewMatrix(m);
	
	Renderer();
}

/***********************************************************************
	функция:			SetMouse()
	назначение:			Запомнить начальные координаты для вычисления угла поворота
	входные данные:		x, y - начальные координаты мыши
	выходные данные:	нет
**********************************************************************/
void CGraphics::SetMouse(float x, float y) const
{
	pDrawGrdPerson->SetMouse(x, y);
}
