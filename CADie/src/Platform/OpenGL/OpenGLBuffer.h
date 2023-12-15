#pragma once
#include "CADie/Renderer/Buffer.h"

namespace CADie {

	// ---------------- Vertex Buffer Class -----------------
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		void Bind() const override;
		void Unbind() const override;

		void SetLayout(const BufferLayout& layout) override;
		const BufferLayout& GetLayout() const override;
	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};
	// -----------------------------------------------------

	// ---------------- Index Buffer Class -----------------
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		uint32_t GetCount() const override { return m_Count; };

		void Bind() const override;
		void Unbind() const override;
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
	// -----------------------------------------------------

}