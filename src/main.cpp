#include <iostream>
#include "opengl_base.h"

int main()
{
	OpenGLBase openGLBase;
	try
	{
		openGLBase.run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}