#include <iostream>
#include <stdexcept>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class OpenGLBase
{
public:
	void run();
	virtual void draw() = 0;
private:
	GLFWwindow* window;

	static const GLuint WINDOW_WIDTH = 800;
	static const GLuint WINDOW_HEIGHT = 600;
	static const int WINDOW_RESIZE = GL_FALSE;

	void initOpenGL();
	void createWindow();
	void mainLoop();
	void cleanup();
};