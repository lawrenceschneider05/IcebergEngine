#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "core/IcebergEngine.h"
#include "utils/log.h"

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