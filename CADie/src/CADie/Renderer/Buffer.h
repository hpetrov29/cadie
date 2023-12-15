#pragma once

namespace CADie {

	// ---------------- Vertex Buffer Class -----------------
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	};

	void Bind(std::unique_ptr<VertexBuffer>& vb);
	void Unbind(std::unique_ptr<VertexBuffer>& vb);
	// -----------------------------------------------------

	// ---------------- Index Buffer Class -----------------
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;
	};

	void Bind(std::unique_ptr<IndexBuffer>& vb);
	void Unbind(std::unique_ptr<IndexBuffer>& vb);
	uint32_t GetCount(std::unique_ptr<IndexBuffer>& vb);
	// -----------------------------------------------------

}