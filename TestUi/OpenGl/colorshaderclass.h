////////////////////////////////////////////////////////////////////////////////
// Filename: colorshaderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _COLORSHADERCLASS_H_
#define _COLORSHADERCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <fstream>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

///////////////////////
// MY CLASS INCLUDES //
///////////////////////


////////////////////////////////////////////////////////////////////////////////
// Class name: ColorShaderClass
////////////////////////////////////////////////////////////////////////////////
class ColorShaderClass
{
public:
	HWND hwnd;

	ColorShaderClass();
	~ColorShaderClass();

	bool Initialize(HWND);
	void Shutdown();
	void SetShader();
	bool SetShaderParameters(mat4 worldMatrix, mat4 viewMatrix, mat4 projectionMatrix);

private:


	unsigned int m_vertexShader;
	unsigned int m_fragmentShader;
	unsigned int m_shaderProgram;

	bool InitializeShader(char*, char*);
	char* LoadShaderSourceFile(char*);
	void OutputShaderErrorMessage(unsigned int, char*);
	void OutputLinkerErrorMessage(unsigned int);
	void ShutdownShader();

	void ConvertMat4toFloat(mat4 matrix, float m[16]);
};

#endif