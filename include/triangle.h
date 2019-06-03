#include "opengl_base.h"

class Triangle : public OpenGLBase
{
public:
	void draw();

private:
	void setBgColor();
	void drawTriangle();
};