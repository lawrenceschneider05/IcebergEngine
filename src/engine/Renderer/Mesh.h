#pragma once

#include <vector>
#include "Vertex.h"

namespace Engine {

	class Mesh {

		mesh(const std::vector<vertex>& vertices, const std::vector<unsigned int>& indices);
        ~mesh();

        mesh(const mesh&) = delete;
        mesh& operator=(const mesh&) = delete;

        mesh(mesh&& other) noexcept;
        mesh& operator=(mesh&& other) noexcept;

        void bind() const;

        [[nodiscard]] unsigned int GetIndexCount() const { return indexCount; }

    private:
        unsigned int VAO{}, VBO{}, EBO{};
        size_t indexCount{};

        void cleanup() noexcept;
    };
}