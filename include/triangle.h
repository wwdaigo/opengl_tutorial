#include "opengl_base.h"

class Triangle : public OpenGLBase
{
public:
	void draw();

private:
	const static GLfloat vertices[];
	const static GLfloat quadVertices[];
	const static GLuint quadVertexIndices[];

	GLuint VBO, VAO, EBO;
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;

	void setBgColor();

	// Vertex array buffer
	void setupVertexArrayBuffer();
	void setupVertexArrayBufferQuad();

	// Shaders
	void compileVertexShader();
	void compileFragmentShader();
	void debugShaderCompilation(GLuint shader, std::string tag);
	void createShaderProgram();
	void cleanupShader();

	// Rendering
	void linkVertexAttributes();
	void renderTriangle();
	void renderQuad();

	void runPipeline();
	void runQuadPipeline();

	// Cleanup
	void cleanupBuffers();
};