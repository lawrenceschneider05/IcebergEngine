#pragma once

#include "utils/noncopyable.h"
#include <memory>
#include <cstdint>

namespace Engine {

    class iIndexBuffer : private NonCopyable {
    public:
        virtual ~iIndexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual unsigned int GetCount() const = 0;

        static std::shared_ptr<iIndexBuffer> Create(const uint32_t* indices, uint32_t count);
    };

}