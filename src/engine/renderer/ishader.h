#pragma once

#include "utils/noncopyable.h"
#include <string>
#include <memory>
#include <glm/glm.hpp>

namespace Engine {

    class iShader : private NonCopyable {
    public:
        virtual ~iShader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetInt(const std::string& name, int value) = 0;
        virtual void SetFloat(const std::string& name, float value) = 0;
        virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
        virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
        virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

        static std::shared_ptr<iShader> Create(const std::string& filepath);
        static std::shared_ptr<iShader> Create(const std::string& vertPath, const std::string& fragPath);
    };

}