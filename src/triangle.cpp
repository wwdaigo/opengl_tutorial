#include "triangle.h"
#include "shaders.h"
#include <sstream>
#include <string>

const GLfloat Triangle::vertices[] = {
	-0.5f,	-0.5f,	0.0f,
	0.5f,	-0.5f,	0.0f,
	0.0f,	0.5f,	0.0f
};

void Triangle::draw()
{
	setBgColor();
	runPipeline();
}

void Triangle::setBgColor()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Triangle::setupVertexArrayBuffer()
{
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void Triangle::compileVertexShader()
{
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	debugShaderCompilation(vertexShader, "ERROR::SHADER::VERTEX::COMPILATION_FAILED");
}

void Triangle::compileFragmentShader()
{
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	debugShaderCompilation(fragmentShader, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED");
}

void Triangle::debugShaderCompilation(GLuint shader, std::string tag)
{
	GLint success;
	GLchar infoLog [512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::stringstream ss;
		ss << tag << std::endl << infoLog << std::endl;
		throw std::runtime_error(ss.str());
	}
}
void Triangle::createShaderProgram()
{
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
}

void Triangle::cleanupShader()
{
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void linkVertexAttributes()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
}

void renderTriangle()
{
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0 ,3);
	glBindVertexArray(0);
}

void Triangle::runPipeline()
{
	// Vertex Array buffer / object
	setupVertexArrayBuffer();	

	// Shaders
	compileVertexShader();
	compileFragmentShader();
	createShaderProgram();
	cleanupShader();
		
	linkVertexAttributes();
	renderTriangle();
}