#pragma once

#include "utils/noncopyable.h"
#include "utils/log.h"
#include <cstddef>
#include <new>
#include <memory>

namespace Engine {

    class Arena : private NonCopyable {
    public:
        Arena(std::size_t bSize)
            : bufferSize(bSize) {
            buffer = reinterpret_cast<std::byte*>(::operator new(bufferSize)); // Allocates size
        }

        ~Arena() {
            ::operator delete(buffer)
        }

        void* allocate(std::size_t size, std::size_t alignment = alignof(std::max_align_t)) { // I haven't taken 261 so I don't understand but the CPU needs ints in a specific spot
            uintptr_t current{ reinterpret_cast<intptr_t> (buffer + offSet) }; 
            uintptr_t aligned{ (current + alignment - 1) & ~(alignment - 1) };
            std::size_t padding{ aligned - current };

                if (offSet + size + padding > bufferSize) {
                    return nullptr;
                    log(LOG_ERROR,"Arena out Of Memory")
                }

                offSet += padding;
                void* result{};
                return result;
        }

        template <typename T, typename... Args>
        T* allocate(Args&&... args) {
            void* object{ allocate(sizeof(T), alignof(T)) };

            if (object == nullptr) {
                return nullptr;
            }

            return new (object) T{ std::forward<Args>(Args) };
        }
        
        void reset() {
            offSet = 0
        } 

    private:
        std::byte* buffer;
        std::size_t bufferSize;
        std::size_t offSet;
    };

}