////////////////////////////////////////////////////////////////////////////////
// Filename: colorshaderclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <gl/glew.h>
#include "colorshaderclass.h"


ColorShaderClass::ColorShaderClass()
{
}

ColorShaderClass::~ColorShaderClass()
{
}

bool ColorShaderClass::Initialize(HWND h_Wnd)
{
	bool result;

	hwnd = h_Wnd;
	
	// Initialize the vertex and pixel shaders.
	result = InitializeShader("Engine/color.vs", "Engine/color.ps");
	if (!result)
	{
		return false;
	}

	return true;
}

void ColorShaderClass::Shutdown()
{
	// Shutdown the vertex and pixel shaders as well as the related objects.
	ShutdownShader();

	return;
}

void ColorShaderClass::SetShader()
{
	// Install the shader program as part of the current rendering state.
	glUseProgram(m_shaderProgram);

	return;
}

bool ColorShaderClass::InitializeShader(char* vsFilename, char* fsFilename)
{
	const char* vertexShaderBuffer;
	const char* fragmentShaderBuffer;
	int status;

	// Load the vertex shader source file into a text buffer.
	vertexShaderBuffer = LoadShaderSourceFile(vsFilename);
	if (!vertexShaderBuffer)
	{
		return false;
	}

	// Load the fragment shader source file into a text buffer.
	fragmentShaderBuffer = LoadShaderSourceFile(fsFilename);
	if (!fragmentShaderBuffer)
	{
		return false;
	}

	// Create a vertex and fragment shader object.
	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Copy the shader source code strings into the vertex and fragment shader objects.
	glShaderSource(m_vertexShader, 1, &vertexShaderBuffer, NULL);
	glShaderSource(m_fragmentShader, 1, &fragmentShaderBuffer, NULL);

	// Release the vertex and fragment shader buffers.
	delete[] vertexShaderBuffer;
	vertexShaderBuffer = 0;

	delete[] fragmentShaderBuffer;
	fragmentShaderBuffer = 0;

	// Compile the shaders.
	glCompileShader(m_vertexShader);
	glCompileShader(m_fragmentShader);

	// Check to see if the vertex shader compiled successfully.
	glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &status);
	if (status != 1)
	{
		// If it did not compile then write the syntax error message out to a text file for review.
		OutputShaderErrorMessage(m_vertexShader, vsFilename);
		return false;
	}

	// Check to see if the fragment shader compiled successfully.
	glGetShaderiv(m_fragmentShader, GL_COMPILE_STATUS, &status);
	if (status != 1)
	{
		// If it did not compile then write the syntax error message out to a text file for review.
		OutputShaderErrorMessage(m_fragmentShader, fsFilename);
		return false;
	}

	// Create a shader program object.
	m_shaderProgram = glCreateProgram();

	// Attach the vertex and fragment shader to the program object.
	glAttachShader(m_shaderProgram, m_vertexShader);
	glAttachShader(m_shaderProgram, m_fragmentShader);

	// Bind the shader input variables.
	glBindAttribLocation(m_shaderProgram, 0, "inputPosition");
	glBindAttribLocation(m_shaderProgram, 1, "inputColor");

	// Link the shader program.
	glLinkProgram(m_shaderProgram);

	// Check the status of the link.
	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &status);
	if (status != 1)
	{
		// If it did not link then write the syntax error message out to a text file for review.
		OutputLinkerErrorMessage(m_shaderProgram);
		return false;
	}

	return true;
}

char* ColorShaderClass::LoadShaderSourceFile(char* filename)
{
	ifstream fin;
	int fileSize;
	char input;
	char* buffer;


	// Open the shader source file.
	fin.open(filename);

	// If it could not open the file then exit.
	if (fin.fail())
	{
		return 0;
	}

	// Initialize the size of the file.
	fileSize = 0;

	// Read the first element of the file.
	fin.get(input);

	// Count the number of elements in the text file.
	while (!fin.eof())
	{
		fileSize++;
		fin.get(input);
	}

	// Close the file for now.
	fin.close();

	// Initialize the buffer to read the shader source file into.
	buffer = new char[fileSize + 1];
	if (!buffer)
	{
		return 0;
	}

	// Open the shader source file again.
	fin.open(filename);

	// Read the shader text file into the buffer as a block.
	fin.read(buffer, fileSize);

	// Close the file.
	fin.close();

	// Null terminate the buffer.
	buffer[fileSize] = '\0';

	return buffer;
}

void ColorShaderClass::OutputShaderErrorMessage(unsigned int shaderId, char* shaderFilename)
{
	int logSize, i;
	char* infoLog;
	ofstream fout;
	//unsigned int error, convertedChars;


	// Get the size of the string containing the information log for the failed shader compilation message.
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logSize);

	// Increment the size by one to handle also the null terminator.
	logSize++;

	// Create a char buffer to hold the info log.
	infoLog = new char[logSize];
	if (!infoLog)
	{
		return;
	}

	// Now retrieve the info log.
	glGetShaderInfoLog(shaderId, logSize, NULL, infoLog);

	// Open a file to write the error message to.
	fout.open("shader-error.txt");

	// Write out the error message.
	for (i = 0; i < logSize; i++)
	{
		fout << infoLog[i];
	}

	// Close the file.
	fout.close();

	// Convert the shader filename to a wide character string.
	/*error = mbstowcs_s(&convertedChars, newString, 128, shaderFilename, 128);
	if (error != 0)
	{
		return;
	}*/

	// Pop a message up on the screen to notify the user to check the text file for compile errors.
	MessageBox(hwnd, "Error compiling shader.  Check shader-error.txt for message.", shaderFilename, MB_OK);

	return;
}

void ColorShaderClass::OutputLinkerErrorMessage(unsigned int programId)
{
	int logSize, i;
	char* infoLog;
	ofstream fout;


	// Get the size of the string containing the information log for the failed shader compilation message.
	glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logSize);

	// Increment the size by one to handle also the null terminator.
	logSize++;

	// Create a char buffer to hold the info log.
	infoLog = new char[logSize];
	if (!infoLog)
	{
		return;
	}

	// Now retrieve the info log.
	glGetProgramInfoLog(programId, logSize, NULL, infoLog);

	// Open a file to write the error message to.
	fout.open("linker-error.txt");

	// Write out the error message.
	for (i = 0; i < logSize; i++)
	{
		fout << infoLog[i];
	}

	// Close the file.
	fout.close();

	// Pop a message up on the screen to notify the user to check the text file for linker errors.
	MessageBox(hwnd, "Error compiling linker.  Check linker-error.txt for message.", "Linker Error", MB_OK);

	return;
}

void ColorShaderClass::ShutdownShader()
{
	// Detach the vertex and fragment shaders from the program.
	glDetachShader(m_shaderProgram, m_vertexShader);
	glDetachShader(m_shaderProgram, m_fragmentShader);

	// Delete the vertex and fragment shaders.
	glDeleteShader(m_vertexShader);
	glDeleteShader(m_fragmentShader);

	// Delete the shader program.
	glDeleteProgram(m_shaderProgram);

	return;
}

/***********************************************************************
	функция:			ConvertMat4toFloat()
	назначение:			Конвертирование матрицы типа mat4 в матрицу типа float[16]
	входные данные:		matrix - матрица типа mat4
						m[16] - матрица типа float[16]
	выходные данные:	нет
**********************************************************************/
void ColorShaderClass::ConvertMat4toFloat(mat4 matrix, float m[16])
{
	for (int i = 0; i < 4; i++)
	{
		m[4 * i] = matrix[i].x;
		m[4 * i + 1] = matrix[i].y;
		m[4 * i + 2] = matrix[i].z;
		m[4 * i + 3] = matrix[i].w;
	}
}

bool ColorShaderClass::SetShaderParameters(mat4 worldMatrix, mat4 viewMatrix, mat4 projectionMatrix)
{
	float m[16];
	
	// Set the world matrix in the vertex shader.
	unsigned int location = glGetUniformLocation(m_shaderProgram, "worldMatrix");
	if (location == -1)
	{
		return false;
	}
	ConvertMat4toFloat(worldMatrix, m);
	glUniformMatrix4fv(location, 1, false, m);

	// Set the view matrix in the vertex shader.
	location = glGetUniformLocation(m_shaderProgram, "viewMatrix");
	if (location == -1)
	{
		return false;
	}
	ConvertMat4toFloat(viewMatrix, m);
	glUniformMatrix4fv (location, 1, false, m);

	// Set the projection matrix in the vertex shader.
	location = glGetUniformLocation(m_shaderProgram, "projectionMatrix");
	if (location == -1)
	{
		return false;
	}
	ConvertMat4toFloat(projectionMatrix, m);
	glUniformMatrix4fv(location, 1, false, m);

	return true;
}
