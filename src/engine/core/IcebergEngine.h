#pragma once

#include <iostream>
#include "window/iwindow.h"
#include "platform/iplatform.h"

namespace Engine
{
	void PrintEngineVersion();

	class IcebergEngine
	{
	public:
		IcebergEngine();
		~IcebergEngine();

		bool init();
		
		void start();
	private:
		IWindow* window;
		IPlatform* platform;
	};
}