#include "glvertexarray.h"
#include <glad/glad.h>

namespace Engine {

	glVertexArray::glVertexArray()
	{
		glGenVertexArrays(1, &rendererID);
	}

	glVertexArray::~glVertexArray()
	{
		glDeleteVertexArrays(1, &rendererID);
	}

	glVertexArray::glVertexArray(glVertexArray&& other) noexcept
		: rendererID(other.rendererID),
		indexBuffer(std::move(other.indexBuffer)),
		vertexBuffers(std::move(other.vertexBuffers))
	{
		other.rendererID = 0;
	}

	glVertexArray& glVertexArray::operator=(glVertexArray&& other) noexcept
	{
		if (this != &other)
		{
			glDeleteVertexArrays(1, &rendererID);
			rendererID = other.rendererID;
			indexBuffer = std::move(other.indexBuffer);
			vertexBuffers = std::move(other.vertexBuffers);
			other.rendererID = 0;
		}
		return *this;
	}

	void glVertexArray::Bind() const
	{
		glBindVertexArray(rendererID);
	}

	void glVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void glVertexArray::AddVertexBuffer(const std::shared_ptr<OpenGLVertexBuffer>& vb)
	{
		glBindVertexArray(rendererID);
		vb->Bind();
		
		const auto& layout = vb->GetLayout();
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
		
		vertexBuffers.push_back(vb);
	}

	void glVertexArray::SetIndexBuffer(const std::shared_ptr<glIndexBuffer>& ib)
	{
		glBindVertexArray(rendererID);
		ib->Bind();
		indexBuffer = ib;
	}
}