// IcebergEngine.cpp : Defines the entry point for the application.
//

#include "IcebergEngine.h"
#include "utils/log.h"
#include "platform/platform_factory.h"

namespace Engine
{
	IcebergEngine::IcebergEngine()
	{
		WindowConfig config;
		config.title = "Iceberg";
		config.dimension = { 10,10 };
		config.maximized = true;
		window = create_window(PlatformBackend::GLFW, config);
		platform = create_platform(PlatformBackend::GLFW);
	}

	IcebergEngine::~IcebergEngine()
	{
		delete window;
		delete platform;
	}

	bool IcebergEngine::init() 
	{
		platform->init();
		window->init();
		return 1;
	}

	void IcebergEngine::start() 
	{
		while (!window->should_close())
		{
			window->poll_events();
			window->swap_buffers();
		}
	}
}