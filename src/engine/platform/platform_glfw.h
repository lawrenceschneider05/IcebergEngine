#pragma once

#include "iplatform.h"

namespace Engine
{
	class Platform_GLFW : public IPlatform
	{
	public:
		bool init() override;
		void shutdown() override;
	private:
	};
}