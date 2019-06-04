#include "opengl_base.h"

class Triangle : public OpenGLBase
{
public:
	void draw();

private:
	const static GLfloat vertices[];

	GLuint VBO, VAO;
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;

	void setBgColor();

	// Vertex array buffer
	void setupVertexArrayBuffer();

	// Shaders
	void compileVertexShader();
	void compileFragmentShader();
	void debugShaderCompilation(GLuint shader, std::string tag);
	void createShaderProgram();
	void cleanupShader();

	// Rendering
	void linkVertexAttributes();
	void renderTriangle();

	void runPipeline();
};