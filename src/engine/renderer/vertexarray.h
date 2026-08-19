#pragma once
#include <memory>
#include "utils/noncopyable.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Engine {
	class VertexArray : private NonCopyable {
	public:
		VertexArray();
		~VertexArray();

		VertexArray(VertexArray&& other) noexcept;
		VertexArray& operator=(VertexArray&& other) noexcept;

		void Bind() const;
		void Unbind() const;

		void SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
		void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);
		
		const std::shared_ptr<VertexBuffer>& getVertexBuffer() const { return vertexBuffer; }
		const std::shared_ptr<IndexBuffer>& getIndexBuffer() const { return indexBuffer; }

	private:
		unsigned int _RendererID = 0;
		std::shared_ptr<IndexBuffer> indexBuffer;
		std::shared_ptr<VertexBuffer> vertexBuffer;
		
	};
}