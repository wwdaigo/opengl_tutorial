#include "opengl_base.h"

void OpenGLBase::run()
{
	initOpenGL();
	createWindow();
	mainLoop();
	cleanup();
}

void OpenGLBase::initOpenGL()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR ,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR ,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE ,GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, WINDOW_RESIZE);
}

void OpenGLBase::createWindow()
{
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Learn OpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		throw std::runtime_error("Failed to create GLFW window");
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		throw std::runtime_error("Failed to initialize GLEW");
	}
	glViewport(0, 0, 800, 600);
}

void OpenGLBase::mainLoop()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		draw();
		glfwSwapBuffers(window);
	}
}

void OpenGLBase::cleanup()
{
	glfwTerminate();
}