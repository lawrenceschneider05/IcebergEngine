#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "IcebergEngine.h"

using namespace Engine;

int main()
{
	IcebergEngine engine{};
	if (engine.init())
	{
		engine.start();
	}
	return 0;
}