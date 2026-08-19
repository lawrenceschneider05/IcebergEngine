#include "indexbuffer.h"
#include <glad/glad.h>

namespace Engine {

    IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    {
        this->count = count;
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &m_RendererID);
    }

    IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
        : m_RendererID(other.m_RendererID), count(other.count)
    {
        other.m_RendererID = 0;
        other.count = 0;
    }

    IndexBuffer& Engine::IndexBuffer::operator=(IndexBuffer&& other) noexcept
    {
        if (this != &other)
        {
            glDeleteBuffers(1, &m_RendererID);
            m_RendererID = other.m_RendererID;
            count = other.count;
            other.m_RendererID = 0;
            other.count = 0;
        }
        return *this;
    }

    void IndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }

    void IndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
