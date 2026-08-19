#include "VertexBuffer.h"
#include <glad/glad.h>

namespace Engine {

    VertexBuffer::VertexBuffer(const void* data, size_t size)
    {
        glGenBuffers(1, &RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &RendererID);
    }

    VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
        : RendererID(other.RendererID)
    {
        other.RendererID = 0;
    }

    VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
    {
        if (this != &other)
        {
            glDeleteBuffers(1, &RendererID);
            RendererID = other.RendererID;
            other.RendererID = 0;
        }
        return *this;
    }

    void VertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, RendererID);
    }

    void VertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

}