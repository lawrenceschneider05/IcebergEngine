#pragma once

#include "utils/noncopyable.h"
#include "bufferlayout.h"
#include <memory>
#include <cstdint>

namespace Engine {

    class iVertexBuffer : private NonCopyable {
    public:
        virtual ~iVertexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual const BufferLayout& GetLayout() const = 0;
        virtual void SetLayout(const BufferLayout& layout) = 0;

        static std::shared_ptr<iVertexBuffer> Create(const void* vertices, uint32_t size);
        static std::shared_ptr<iVertexBuffer> Create(uint32_t size);
    };

}