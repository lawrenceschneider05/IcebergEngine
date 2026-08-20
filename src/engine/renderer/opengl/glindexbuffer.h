#pragma once

#include "renderer/iindexbuffer.h"

namespace Engine {

    class glIndexBuffer : public iIndexBuffer {
    public:
        glIndexBuffer(const unsigned int* data, unsigned int count);
        ~glIndexBuffer() override;

        void Bind() const override;
        void Unbind() const override;

        unsigned int GetCount() const override { return count; }

    private:
        unsigned int RendererID = 0;
        unsigned int count = 0;
    };

}