#pragma once
#include "utils/noncopyable.h"
#include "BufferLayout.h"

namespace Engine {

	class VertexBuffer : private NonCopyable {

	public:
		VertexBuffer(const void* data, size_t size);
		~VertexBuffer();

		VertexBuffer(VertexBuffer&& other) noexcept;
		VertexBuffer& operator=(VertexBuffer&& other) noexcept;

		void Bind() const;
		void Unbind() const;

		void SetLayout(const BufferLayout& layout) { Layout = layout; }
		const BufferLayout& GetLayout() const { return Layout; }

	private:
		unsigned int RendererID = 0;
		BufferLayout Layout;
	};
}