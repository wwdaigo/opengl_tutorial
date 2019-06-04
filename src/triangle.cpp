#include "triangle.h"
#include "shaders.h"
#include <sstream>
#include <string>

void Triangle::draw()
{
	setBgColor();
	drawTriangle();
}

void Triangle::setBgColor()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Triangle::drawTriangle()
{
	// 1- define the vertices of triangle, following x, y, z coordinates from -1 to 1 for each vertex.
	GLfloat vertices[] = {
		-0.5f,	-0.5f,	0.0f,
		0.5f,	-0.5f,	0.0f,
		0.0f,	0.5f,	0.0f
	};

	// 2 - Create the vertex buffer object (VBO) to submit to GPU the vertices to be rendered
	// glGenBufers(n of buffers to be generated, reference to VBO)
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 3 - Compile the Vertex Shader
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLint success;
	GLchar infoLog [512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::stringstream ss;
		ss << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << std::endl << infoLog << std::endl;
		throw std::runtime_error(ss.str());
	}

	// 4 - Compile the fragment shader
	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// 5 - Create the shader program
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// 6 - Link the vertex attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0 ,3);
	glBindVertexArray(0);
}