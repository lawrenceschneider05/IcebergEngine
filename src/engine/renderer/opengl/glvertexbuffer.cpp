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

    void glVertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, RendererID);
    }

    void glVertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

}