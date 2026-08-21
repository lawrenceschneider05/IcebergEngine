#include "glindexbuffer.h"
#include <glad/glad.h>

namespace Engine {

    glIndexBuffer::glIndexBuffer(const unsigned int* data, unsigned int count)
    {
        this->count = count;
        glGenBuffers(1, &RendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
    }

    glIndexBuffer::~glIndexBuffer()
    {
        glDeleteBuffers(1, &RendererID);
    }

    void glIndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererID);
    }

    void glIndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
