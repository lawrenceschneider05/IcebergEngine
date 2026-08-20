#include "glvertexbuffer.h"
#include <glad/glad.h>

namespace Engine {

    glVertexBuffer::glVertexBuffer(const void* data, size_t size)
    {
        glGenBuffers(1, &RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    glVertexBuffer::~glVertexBuffer()
    {
        glDeleteBuffers(1, &RendererID);
    }

    glVertexBuffer::glVertexBuffer(glVertexBuffer&& other) noexcept
        : RendererID(other.RendererID)
    {
        other.RendererID = 0;
    }

    glVertexBuffer& glVertexBuffer::operator=(glVertexBuffer&& other) noexcept
    {
        if (this != &other)
        {
            glDeleteBuffers(1, &RendererID);
            RendererID = other.RendererID;
            other.RendererID = 0;
        }
        return *this;
    }

    void glVertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, RendererID);
    }

    void glVertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

}