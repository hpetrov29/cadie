#include "pch.h"
#include "Buffer.h"

#include "Renderer.h"

namespace CADie {

	void Bind(std::unique_ptr<VertexBuffer>& vb)
	{
		vb->Bind();
	}

	void Unbind(std::unique_ptr<VertexBuffer>& vb)
	{
		vb->Unbind();
	}

	void Bind(std::unique_ptr<IndexBuffer>& ib)
	{
		ib->Bind();
	}

	void Unbind(std::unique_ptr<IndexBuffer>& ib)
	{
		ib->Unbind();
	}
	uint32_t GetCount(std::unique_ptr<IndexBuffer>& vb)
	{
		uint32_t count = vb->GetCount();
		return count;
	}
}