#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class OpenGLBase
{
public:
	void run();

private:
	GLFWwindow* window;

	static const int WINDOW_WIDTH = 800;
	static const int WINDOW_HEIGHT = 600;
	static const int WINDOW_RESIZE = GL_FALSE;

	void initOpenGL();
	void createWindow();
	void mainLoop();
	void cleanup();
};