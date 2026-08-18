#pragma once
#include "iwindow.h"
#include "GLFW/glfw3.h"

namespace Engine
{
	class Window_GLFW : public IWindow
	{
	public:
		Window_GLFW(WindowConfig window_config);
		~Window_GLFW() override;

		bool init() override;

		glm::vec2 get_dimension() override;
		string get_title() override;

		bool set_dimension(glm::vec2) override;
		bool set_title(string) override;

		bool should_close() override;
		void poll_events() override;
		void swap_buffers() override;

		void set_resize_callback(ResizeCallback callback) override;

		operator GLFWwindow* ()
		{
			return handle;
		}
	private:
		static void framebuffer_size_callback(GLFWwindow* handle, int width, int height);

		GLFWwindow* handle;
		ResizeCallback resize_callback;
	};
}