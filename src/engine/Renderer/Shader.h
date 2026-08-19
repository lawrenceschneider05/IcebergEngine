#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>

namespace Engine
{
    class Shader
    {
    public:
        Shader() = default;
        ~Shader()
        {
            if (program != 0)
                glDeleteProgram(program);
        }
        Shader(std::string vertPath, std::string fragPath);
        void bind();
        void setMat4(std::string, glm::mat4);
    private:
        std::string readFile(const std::string& path);
        void compileShaders();
        std::string vertPath, fragPath;
        glm::uint32_t program{};
    };
}
