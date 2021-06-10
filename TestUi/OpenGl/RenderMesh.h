#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

#define GL_CHECK_ERRORS assert(glGetError()== GL_NO_ERROR);
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "Opengl32.lib")

struct VertexType
{
	float x, y, z;
	float r, g, b;
};

class RenderMesh
{
	HWND m_hwnd = nullptr;

	unsigned int m_vertexArrayId = 0, m_vertexBufferId = 0, m_indexBufferId = 0;
	int m_vertexCount = 0, m_indexCount = 0;
	
	void ShutdownBuffers();

public:
	RenderMesh();

	bool InitOpenGl(CWnd* pWnd);
	
	void DrawMesh(unsigned int m_vertexArrayId, uint32 indexCount, GLenum type = GL_TRIANGLES);
	void BindBuffer(const void* data, unsigned int sizeData, const void* indeces, unsigned int sizeIndeces,  GLenum type); 

};
