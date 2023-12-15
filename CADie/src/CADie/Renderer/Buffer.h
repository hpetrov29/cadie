#pragma once

namespace CADie {

	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:   return 4;
			case ShaderDataType::Float2:  return 8;
			case ShaderDataType::Float3:  return 12;
			case ShaderDataType::Float4:  return 16;
			case ShaderDataType::Mat3:    return 36;
			case ShaderDataType::Mat4:    return 64;
			case ShaderDataType::Int:     return 4;
			case ShaderDataType::Int2:    return 8;
			case ShaderDataType::Int3:    return 12;
			case ShaderDataType::Int4:    return 16;
			case ShaderDataType::Bool:    return 1;
		}
		CADIE_CORE_ASSERT(false, "Uknown shader data type");
		return 0;
	};

	struct BufferAttribute
	{
		std::string Name;
		ShaderDataType Type;
		uint64_t Offset;
		uint32_t Size;
		bool Normalized;

		BufferAttribute() 
		{
			Type = ShaderDataType::None;
			Offset = 0;
			Size = 0;
			Normalized = false;
		}

		BufferAttribute(ShaderDataType type, const std::string& name, bool normalized = false) : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized) {}
		
		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
				case ShaderDataType::Float:    return 1;
				case ShaderDataType::Float2:   return 2;
				case ShaderDataType::Float3:   return 3;
				case ShaderDataType::Float4:   return 4;
				case ShaderDataType::Mat3:     return 9;
				case ShaderDataType::Mat4:     return 16;
				case ShaderDataType::Int:      return 1;
				case ShaderDataType::Int2:     return 2;
				case ShaderDataType::Int3:     return 3;
				case ShaderDataType::Int4:     return 4;
				case ShaderDataType::Bool:     return 1;
			}
			CADIE_CORE_ASSERT(false, "Uknown shader data type");
			return 0;
		}
	};

	// ---------------- Buffer Layout Class ----------------
	class BufferLayout
	{
	public:
		BufferLayout()
		{
			m_Stride = 0;
		}

		BufferLayout(std::initializer_list<BufferAttribute> attributes) : m_Attributes(attributes) 
		{
			CalculateOffsetsAndStride();
		}

		inline const std::vector<BufferAttribute>& GetAttributes() { return m_Attributes; }

		inline uint32_t GetStride() const { return m_Stride; }

		std::vector<BufferAttribute>::iterator begin() { return m_Attributes.begin(); }
		std::vector<BufferAttribute>::iterator end() { return m_Attributes.end(); }
		std::vector<BufferAttribute>::const_iterator begin() const { return m_Attributes.begin(); }
		std::vector<BufferAttribute>::const_iterator end() const { return m_Attributes.end(); }
	private:
		void CalculateOffsetsAndStride()
		{
			uint64_t offset = 0;
			m_Stride = 0;
			for (auto& attribute : m_Attributes)
			{
				attribute.Offset = offset;
				offset += attribute.Size;
				m_Stride += attribute.Size;
			}
		}
	private:
		std::vector<BufferAttribute> m_Attributes;
		uint32_t m_Stride;
	};
	// -----------------------------------------------------

	// ---------------- Vertex Buffer Class -----------------
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;
	};

	void Bind(std::unique_ptr<VertexBuffer>& vb);
	void Unbind(std::unique_ptr<VertexBuffer>& vb);
	void SetLayout(std::unique_ptr<VertexBuffer>& vb, const BufferLayout& layout);
	const BufferLayout& GetLayout(std::unique_ptr<VertexBuffer>& vb);
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