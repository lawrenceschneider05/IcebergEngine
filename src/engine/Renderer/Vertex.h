#pragma once

#include <glm/glm.hpp>

namespace Engine {

    struct vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 uv;
    };

}