#pragma once

#include <glm/glm.hpp>
#include <string>
#include <functional>
#include "window_config.h"

using std::string;
using std::function;

namespace Engine
{
	class IWindow
	{
	public:
		IWindow(WindowConfig window_config)
			: config(window_config)
		{}
		virtual ~IWindow() = default;

		virtual bool init() = 0;

		virtual glm::vec2 get_dimension() = 0;
		virtual string get_title() = 0;

		virtual bool set_dimension(glm::vec2) = 0;
		virtual bool set_title(string) = 0;

		virtual void poll_events() = 0;
		virtual void swap_buffers() = 0;

		virtual bool should_close() = 0;

		using ResizeCallback = function<void(int, int)>;
		virtual void set_resize_callback(ResizeCallback) = 0;

	protected:
		WindowConfig config;
	};
}