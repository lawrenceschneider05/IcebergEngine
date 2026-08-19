#pragma once

#include "utils/noncopyable.h"
#include "ivertexbuffer.h"
#include "iindexbuffer.h"
#include <memory>
#include <vector>

namespace Engine {

    class iVertexArray : private NonCopyable {
    public:
        virtual ~iVertexArray() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void AddVertexBuffer(const std::shared_ptr<iVertexBuffer>& vertexBuffer) = 0;
        virtual void SetIndexBuffer(const std::shared_ptr<iIndexBuffer>& indexBuffer) = 0;

        virtual const std::vector<std::shared_ptr<iVertexBuffer>>& GetVertexBuffers() const = 0;
        virtual const std::shared_ptr<iIndexBuffer>& GetIndexBuffer() const = 0;

        static std::shared_ptr<iVertexArray> Create();
    };

}