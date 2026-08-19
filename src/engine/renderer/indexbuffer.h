#pragma once
#include "utils/noncopyable.h"

namespace Engine {

	class IndexBuffer : private NonCopyable {
	public:
		IndexBuffer(const unsigned int* data, unsigned int count);
		~IndexBuffer();

		IndexBuffer(IndexBuffer&& other) noexcept;
		IndexBuffer& operator=(IndexBuffer&& other) noexcept;

		void Bind() const;
		void Unbind() const;

		inline unsigned int getCount() const { return count; }

	private:
		unsigned int m_RendererID = 0;
		unsigned int count = 0;
	};

}