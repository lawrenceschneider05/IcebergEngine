#include "vertexarray.h"
#include <glad/glad.h>

namespace Engine {

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &_RendererID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &_RendererID);
	}

	VertexArray::VertexArray(VertexArray&& other) noexcept
		: _RendererID(other._RendererID),
		indexBuffer(std::move(other.indexBuffer)),
		vertexBuffer(std::move(other.vertexBuffer))
	{
		other._RendererID = 0;
	}

	VertexArray& VertexArray::operator=(VertexArray&& other) noexcept
	{
		if (this != &other)
		{
			glDeleteVertexArrays(1, &_RendererID);
			_RendererID = other._RendererID;
			indexBuffer = std::move(other.indexBuffer);
			vertexBuffer = std::move(other.vertexBuffer);
			other._RendererID = 0;
		}
		return *this;
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(_RendererID);
	}

	void VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void VertexArray::SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vb)
	{
		glBindVertexArray(_RendererID);
		vb->Bind();

		const auto& layout = vb->GetLayout();
		uint32_t index = 0;
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				ShaderDataTypeComponentCount(element.type),
				GL_FLOAT,
				element.normalized ? GL_TRUE : GL_FALSE,
				layout.getStride(),
				(const void*)(uintptr_t)element.offset
			);
			index++;
		}

		vertexBuffer = vb;
	}

	void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ib)
	{
		glBindVertexArray(_RendererID);
		ib->Bind();
		indexBuffer = ib;
	}
}