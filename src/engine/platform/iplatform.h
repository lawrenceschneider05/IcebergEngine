#pragma once

namespace Engine
{
	class IPlatform
	{
	public:
		virtual ~IPlatform() = default;
		virtual bool init() = 0;
		virtual void shutdown() = 0;
	};
}