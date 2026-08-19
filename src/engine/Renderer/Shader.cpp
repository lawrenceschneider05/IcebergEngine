#include "Shader.h"
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

    Shader::Shader(std::string vPath, std::string fPath) : vertPath(vPath), fragPath(fPath)
    {
        compileShaders();
    }

    void Shader::bind()
    {
        glUseProgram(program);
    }

    void Shader::setMat4(std::string name, glm::mat4 mat)
    {
        GLint location = glGetUniformLocation(program, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
    }

    std::string Shader::readFile(const std::string& path)
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

    void Shader::compileShaders() {
        std::string vertCode = readFile(vertPath);
        std::string fragCode = readFile(fragPath);

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