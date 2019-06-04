#include "opengl_base.h"

class Triangle : public OpenGLBase
{
public:
	void draw();

private:
	GLuint vertexShader;
	GLuint fragmentShader;

	void setBgColor();

	// Shaders
	void compileVertexShader();
	void compileFragmentShader();
	void debugShaderCompilation(GLuint shader, std::string tag);

	void drawTriangle();
};