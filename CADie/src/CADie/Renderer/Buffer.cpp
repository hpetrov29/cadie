#include "pch.h"
#include "Buffer.h"

#include "Renderer.h"

namespace CADie {

	// ---------------- Vertex Buffer Service -----------------
	void Bind(std::unique_ptr<VertexBuffer>& vb)
	{
		vb->Bind();
	}

	void Unbind(std::unique_ptr<VertexBuffer>& vb)
	{
		vb->Unbind();
	}

	void SetLayout(std::unique_ptr<VertexBuffer>& vb, const BufferLayout& layout)
	{
		vb->SetLayout(layout);
	}

	const BufferLayout& GetLayout(std::unique_ptr<VertexBuffer>& vb)
	{
		return vb->GetLayout();
	}
	// -------------------------------------------------------

	// ---------------- Index Buffer Service -----------------
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
	// -------------------------------------------------------
}