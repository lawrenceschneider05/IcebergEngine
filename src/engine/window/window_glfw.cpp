#include "window_glfw.h"

namespace Engine
{
    Window_GLFW::Window_GLFW(WindowConfig config)
        : IWindow(config)
    {
    
    }

    Window_GLFW::~Window_GLFW()
    {
        if (handle)
        {
            glfwDestroyWindow(handle);
        }
    }

    bool Window_GLFW::init()
    {
        // DONT FORGET TO OPTIMIZE
        glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_FALSE);
        glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        glfwWindowHint(GLFW_SAMPLES, 8);
        if (config.fullscreen)
        {
            GLFWmonitor* monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode* mode = glfwGetVideoMode(monitor);

            glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
            glfwWindowHint(GLFW_RED_BITS, mode->redBits);
            glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
            glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
            glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

            handle = glfwCreateWindow(mode->width, mode->height, config.title.c_str(), nullptr, nullptr);
            glfwSetWindowPos(handle, 0, 0);
        }
        else
        {
            glfwWindowHint(GLFW_RESIZABLE, config.resizable);
            glfwWindowHint(GLFW_MAXIMIZED, config.maximized);

            handle = glfwCreateWindow(
                (int)config.dimension.x,
                (int)config.dimension.y,
                config.title.c_str(),
                nullptr,
                nullptr);
        }
        

        if (handle == NULL) {
            assert(handle);
            return false;
        }

        glfwMakeContextCurrent(handle);
        glfwSetWindowUserPointer(handle, this);
        glfwSetFramebufferSizeCallback(handle, framebuffer_size_callback);

        return true;
    }


    glm::vec2 Window_GLFW::get_dimension()
    {
        return config.dimension;
    }

    string Window_GLFW::get_title()
    {
        return config.title;
    }

    bool Window_GLFW::set_dimension(glm::vec2 dimension)
    {
        config.dimension = dimension;
        glfwSetWindowSize(handle, (int)config.dimension.x, (int)config.dimension.y);
        return true;
    }

    bool Window_GLFW::set_title(string title)
    {
        config.title = title;
        glfwSetWindowTitle(handle, title.c_str());
        return true;
    }

    bool Window_GLFW::should_close()
    {
        return glfwWindowShouldClose(handle);
    }

    void Window_GLFW::poll_events()
    {
        glfwPollEvents();
    }

    void Window_GLFW::swap_buffers()
    {
        glfwSwapBuffers(handle);
    }

    void Window_GLFW::set_resize_callback(ResizeCallback callback)
    {
        resize_callback = callback;
    }

    void Window_GLFW::framebuffer_size_callback(GLFWwindow* handle, int width, int height)
    {
        auto* self = static_cast<Window_GLFW*>(glfwGetWindowUserPointer(handle));
        self->config.dimension = glm::vec2((float)width, (float)height);

        if (self->resize_callback)
        {
            self->resize_callback(width, height);
        }
            
    }
}