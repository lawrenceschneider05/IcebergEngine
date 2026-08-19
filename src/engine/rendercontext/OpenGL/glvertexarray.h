#pragma once
#include <memory>
#include <vector>
#include "iVertexArray.h"
#include "iIndexBuffer.h"
#include "iVertexBuffer.h"

namespace Engine {

    class glVertexArray : public iVertexArray {
    public:
        glVertexArray();
        ~glVertexArray() override;

        void Bind() const override;
        void Unbind() const override;

        void AddVertexBuffer(const std::shared_ptr<iVertexBuffer>& vertexBuffer) override;
        void SetIndexBuffer(const std::shared_ptr<iIndexBuffer>& indexBuffer) override;

        const std::vector<std::shared_ptr<iVertexBuffer>>& getVertexBuffers() const override { return vertexBuffers; }
        const std::shared_ptr<iIndexBuffer>& getIndexBuffer() const override { return indexBuffer; }

    private:
        unsigned int rendererID = 0;
        unsigned int index = 0;
        std::shared_ptr<iIndexBuffer> indexBuffer;
        std::vector<std::shared_ptr<iVertexBuffer>> vertexBuffers;
    };

}