#pragma once
#include "CADie/Renderer/Buffer.h"

namespace CADie {

	// ---------------- Vertex Buffer Class -----------------
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		 void Bind() const;
		 void Unbind() const;
	private:
		uint32_t m_RendererID;
	};
	// -----------------------------------------------------

	// ---------------- Index Buffer Class -----------------
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual uint32_t GetCount() const { return m_Count; };

		virtual void Bind() const;
		virtual void Unbind() const;
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
	// -----------------------------------------------------

}