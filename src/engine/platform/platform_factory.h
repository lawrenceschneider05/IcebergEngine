#pragma once
#include "iplatform.h"
#include "window/iwindow.h"

namespace Engine
{
	enum class PlatformBackend
	{
		GLFW,
		SDL
	};

	IWindow* create_window(PlatformBackend, WindowConfig);
	IPlatform* create_platform(PlatformBackend);
}