#include "triangle.h"
#include "shaders.h"
#include <sstream>
#include <string>

const GLfloat Triangle::vertices[] = {
	-0.5f,	-0.5f,	0.0f,
	0.5f,	-0.5f,	0.0f,
	0.0f,	0.5f,	0.0f
};

const GLfloat Triangle::quadVertices[] = {
	0.5f,	0.5f,	0.0f,	// Top right
	0.5f, 	-0.5f,	0.0f,	// Bottom right
	-0.5f,	-0.5f,	0.0f,	// Bottom left
	-0.5f,	0.5f,	0.0f	// Top left
};

const GLuint Triangle::quadVertexIndices[] = {
	0,	1,	3,	// First triangle
	1,	2,	3	// Second triangle
};

void Triangle::draw()
{
	setBgColor();
	//runPipeline();
	runQuadPipeline();
}

void Triangle::setBgColor()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Triangle::setupVertexArrayBuffer()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void Triangle::setupVertexArrayBufferQuad()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadVertexIndices), quadVertexIndices, GL_STATIC_DRAW);
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

void Triangle::linkVertexAttributes()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
}

void Triangle::renderTriangle()
{
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0 ,3);
	glBindVertexArray(0);
}

void Triangle::renderQuad()
{
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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

	cleanupBuffers();
}

void Triangle::runQuadPipeline()
{
	// Vertex Array buffer / object
	setupVertexArrayBufferQuad();	

	// Shaders
	compileVertexShader();
	compileFragmentShader();
	createShaderProgram();
	cleanupShader();
		
	linkVertexAttributes();
	renderQuad();

	cleanupBuffers();
}

void Triangle::cleanupBuffers()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}