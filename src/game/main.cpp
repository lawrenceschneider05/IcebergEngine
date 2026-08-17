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

	log(LOG_DEBUG, "test ", 123);
	log(LOG_INFO, "test", 123);
	log(LOG_WARN, "test", 123);
	log(LOG_SUCCESS, "test", 123);
	log(LOG_ERROR, "test", 123);
	return 0;
}