#include "glshader.h"
#include "utils/log.h"
#include <fstream>
#include <sstream>

namespace {

    void checkCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                Engine::log(Engine::LOG_ERROR, "Shader compile error (", type, "): ", infoLog);
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                Engine::log(Engine::LOG_ERROR, "Shader link error: ", infoLog);
            }
        }
    }

}

namespace Engine {

    glShader::glShader(const std::string& filepath)
    {
        // Place single-file GLSL parsing logic here if needed
    }

    glShader::glShader(const std::string& vertPath, const std::string& fragPath)
        : vertPath(vertPath), fragPath(fragPath)
    {
        CompileShaders();
    }

    glShader::~glShader()
    {
        if (program != 0)
            glDeleteProgram(program);
    }

    void glShader::Bind() const
    {
        glUseProgram(program);
    }

    void glShader::Unbind() const
    {
        glUseProgram(0);
    }

    void glShader::SetInt(const std::string& name, int value)
    {
        GLint location = glGetUniformLocation(program, name.c_str());
        glUniform1i(location, value);
    }

    void glShader::SetFloat(const std::string& name, float value)
    {
        GLint location = glGetUniformLocation(program, name.c_str());
        glUniform1f(location, value);
    }

    void glShader::SetFloat3(const std::string& name, const glm::vec3& value)
    {
        GLint location = glGetUniformLocation(program, name.c_str());
        glUniform3f(location, value.x, value.y, value.z);
    }

    void glShader::SetFloat4(const std::string& name, const glm::vec4& value)
    {
        GLint location = glGetUniformLocation(program, name.c_str());
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void glShader::SetMat4(const std::string& name, const glm::mat4& value)
    {
        GLint location = glGetUniformLocation(program, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
    }

    std::string glShader::ReadFile(const std::string& path)
    {
        std::ifstream file;
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            file.open(path);
            std::stringstream stream;
            stream << file.rdbuf();
            file.close();
            return stream.str();
        }
        catch (std::ifstream::failure& e)
        {
            log(LOG_ERROR, "Failed to open shader file: ", path, " (", e.what(), ")");
        }

        return std::string();
    }

    void glShader::CompileShaders()
    {
        std::string vertCode = ReadFile(vertPath);
        std::string fragCode = ReadFile(fragPath);

        log(LOG_DEBUG, "Vertex source:\n", vertCode);
        log(LOG_DEBUG, "Fragment source:\n", fragCode);

        const char* code = vertCode.c_str();
        unsigned int v, f;

        v = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(v, 1, &code, NULL);
        glCompileShader(v);
        checkCompileErrors(v, "VERTEX");

        f = glCreateShader(GL_FRAGMENT_SHADER);
        code = fragCode.c_str();
        glShaderSource(f, 1, &code, NULL);
        glCompileShader(f);
        checkCompileErrors(f, "FRAGMENT");

        program = glCreateProgram();
        glAttachShader(program, v);
        glAttachShader(program, f);
        glLinkProgram(program);
        checkCompileErrors(program, "PROGRAM");

        glDeleteShader(v);
        glDeleteShader(f);
    }

}