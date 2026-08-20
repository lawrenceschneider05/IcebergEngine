#pragma once

#include "renderer/iVertexBuffer.h"
#include "renderer/BufferLayout.h"

namespace Engine {

    class glVertexBuffer : public iVertexBuffer {
    public:
        glVertexBuffer(const void* data, size_t size);
        ~glVertexBuffer() override;

        void Bind() const override;
        void Unbind() const override;

        void SetLayout(const BufferLayout& layout) override { Layout = layout; }
        const BufferLayout& GetLayout() const override { return Layout; }

    private:
        unsigned int RendererID = 0;
        BufferLayout Layout;
    };

}