#include "platform_factory.h"
#include "window/window_glfw.h"
#include "platform_glfw.h"
#include "window/window_config.h"

namespace Engine
{
	IWindow* create_window(PlatformBackend backend, WindowConfig config)
	{
		switch (backend)
		{
		case PlatformBackend::GLFW:
			return new Window_GLFW(config);
		default:
			return nullptr;
		}
	}

	IPlatform* create_platform(PlatformBackend backend)
	{
		switch (backend)
		{
		case PlatformBackend::GLFW:
			return new Platform_GLFW();
		default: nullptr;
		}
	}
}