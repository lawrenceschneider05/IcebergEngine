#include "platform_glfw.h"
#include "GLFW/glfw3.h"

namespace Engine
{
	bool Platform_GLFW::init()
	{
		return glfwInit();
	}

	void Platform_GLFW::shutdown()
	{
		glfwTerminate();
	}
}