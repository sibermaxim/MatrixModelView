#include "stdafx.h"
#include "RenderMesh.h"
#include <gl/glew.h>

#include <iostream>

RenderMesh::RenderMesh()
{
}

bool RenderMesh::InitOpenGl(CWnd* pWnd)
{
	m_hwnd = pWnd->m_hWnd;
	const HDC m_hdc = GetDC(m_hwnd);

	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;

	const int nPixelFormat = ChoosePixelFormat(m_hdc, &pfd);

	if (nPixelFormat == 0)
		return false;

	const BOOL result = SetPixelFormat(m_hdc, nPixelFormat, &pfd);
	if (!result)
		return false;

	const HGLRC tempContext = wglCreateContext(m_hdc);
	wglMakeCurrent(m_hdc, tempContext);

	GLenum err = glewInit();

	if (!AllocConsole())
	{

	}
	FILE* fp;

	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONIN$", "r", stdin);


	if (GLEW_OK != err) {

	}
	else {
		if (GLEW_VERSION_3_3)
		{
			cout << "Driver supports OpenGL 3.3\nDetails:" << endl;
		}
	}
	glGetError(); //this is to ignore INVALID ENUM error 1282
	GL_CHECK_ERRORS

	//print information on screen
	cout << "\tUsing GLEW " << glewGetString(GLEW_VERSION) << endl;
	cout << "\tVendor: " << glGetString(GL_VENDOR) << endl;
	cout << "\tRenderer: " << glGetString(GL_RENDERER) << endl;
	cout << "\tVersion: " << glGetString(GL_VERSION) << endl;
	cout << "\tGLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

	return true;
}

/***********************************************************************
	функция:			RenderMesh()
	назначение:			вывод вершинных буфферов
	входные данные:		m_vertexArrayId - вершинный буффер
						indexCount - число индексов в вершинном буффере
						type - тип примитива
	выходные данные:	нет
**********************************************************************/
void RenderMesh::DrawMesh(unsigned int m_vertexArrayId, uint32 indexCount, GLenum type)
{
	glBindVertexArray(m_vertexArrayId);
	glDrawElements(type, indexCount, GL_UNSIGNED_INT, nullptr);
}

/***********************************************************************
	функция:			ShutdownBuffers()
	назначение:			освобождение вершинных буфферов
	входные данные:		нет
	выходные данные:	нет
**********************************************************************/
void RenderMesh::ShutdownBuffers()
{
	// Release the vertex buffer.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &m_vertexBufferId);

	// Release the index buffer.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &m_indexBufferId);

	// Release the vertex array object.
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &m_vertexArrayId);
}

/***********************************************************************
	функция:			BindBuffer()
	назначение:			Связывание буффера и вершинных даныых
	входные данные:		data - массив данных вершин, 
						sizeData - размер массива вершин в байтах
						indeces - индексы вершин
						sizeIndeces - размер индексов вершин в байтах
						type - тип примитива для отображения
	выходные данные:	нет
**********************************************************************/
void RenderMesh::BindBuffer(const void * data, unsigned int sizeData, const void * indeces,
				unsigned int sizeIndeces, GLenum type)
{
	ShutdownBuffers();

	glGenVertexArrays(1, &m_vertexArrayId);
	glBindVertexArray(m_vertexArrayId);

	glGenBuffers(1, &m_vertexBufferId);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeData, data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);			//vertex position
	glEnableVertexAttribArray(1);			//color position

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexType), 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(VertexType), static_cast<unsigned char*>(nullptr) + 3 * sizeof(float));

	glGenBuffers(1, &m_indexBufferId);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeIndeces, indeces, GL_STATIC_DRAW);

	//число индексов - размер индексов в байтах / 4
	int countInd = sizeIndeces / 4;
	DrawMesh(m_vertexArrayId, countInd, type);
}
