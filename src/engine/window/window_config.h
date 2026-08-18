#pragma once
#include <glm/glm.hpp>
#include <string>
using std::string;


namespace Engine
{
    struct WindowConfig
    {
        string title = "Window";
        glm::vec2 dimension = { 800, 600 };
        bool resizable = false;
        bool maximized = false;
        bool fullscreen = false;
    };
}