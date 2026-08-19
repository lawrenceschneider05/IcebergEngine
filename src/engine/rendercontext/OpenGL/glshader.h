#pragma once

#include "ishader.h"
#include <glad/glad.h>

namespace Engine {

    class glShader : public iShader {
    public:
        glShader(const std::string& filepath);
        glShader(const std::string& vertPath, const std::string& fragPath);
        ~glShader() override;

        void Bind() const override;
        void Unbind() const override;

        void SetInt(const std::string& name, int value) override;
        void SetFloat(const std::string& name, float value) override;
        void SetFloat3(const std::string& name, const glm::vec3& value) override;
        void SetFloat4(const std::string& name, const glm::vec4& value) override;
        void SetMat4(const std::string& name, const glm::mat4& value) override;

    private:
        std::string ReadFile(const std::string& path);
        void CompileShaders();

        std::string vertPath;
        std::string fragPath;
        uint32_t program = 0;
    };

}