#pragma once


namespace Hazel
{
	// Buffer数据类型
	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:		return 4;
			case ShaderDataType::Float2:	return 4 * 2;
			case ShaderDataType::Float3:	return 4 * 3;
			case ShaderDataType::Float4:	return 4 * 4;
			case ShaderDataType::Mat3:		return 4 * 3 * 3;
			case ShaderDataType::Mat4:		return 4 * 4 * 4;
			case ShaderDataType::Int:		return 4;
			case ShaderDataType::Int2:		return 4 * 2;
			case ShaderDataType::Int3:		return 4 * 3;
			case ShaderDataType::Int4:		return 4 * 4;
			case ShaderDataType::Bool:		return 1;
		}
		HZ_CORE_ASSERT(false, "Unkown ShaderDataType!");
		return 0;

	}

	// 描述Buffer数据
	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		// 偏移量
		uint32_t Offset;
		// 读取Buffer大小
		uint32_t Size;

		bool Normalized;

		BufferElement() {}
		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			:Name(name), Type(type),Size(ShaderDataTypeSize(type)),Offset(0), Normalized(normalized){}

		// 获取元素数量
		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
				case ShaderDataType::Float:		return 1;
				case ShaderDataType::Float2:	return 2;
				case ShaderDataType::Float3:	return 3;
				case ShaderDataType::Float4:	return 4;
				case ShaderDataType::Mat3:		return 3 * 3;
				case ShaderDataType::Mat4:		return 4 * 4;
				case ShaderDataType::Int:		return 1;
				case ShaderDataType::Int2:		return 2;
				case ShaderDataType::Int3:		return 3;
				case ShaderDataType::Int4:		return 4;
				case ShaderDataType::Bool:		return 1;
			}
			HZ_CORE_ASSERT(false, "Unkown ShaderDataType!");
			return 0;
		}

	};

	// 缓存布局
	class BufferLayout
	{
	public:
		BufferLayout() {}
		BufferLayout(std::initializer_list<BufferElement> elements)
			:e_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		inline uint32_t GetStride()const { return m_Stride; }
		inline const std::vector<BufferElement>& GetElements() { return e_Elements; }

		std::vector<BufferElement>::iterator begin() { return e_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return e_Elements.end(); }

		std::vector<BufferElement>::const_iterator begin() const { return e_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return e_Elements.end(); }

	private:
		void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : e_Elements)
			{
				element.Offset = offset;
				// 每次越过上次元素大小
				offset += element.Size;
				
				m_Stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> e_Elements;
		uint32_t m_Stride;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer(){};

		virtual void Bind() const{};
		virtual void UnBind() const {};

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout()const = 0;

		static VertexBuffer* Create(float* vertice, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {};

		virtual void Bind() const {};
		virtual void UnBind() const {};

		virtual uint32_t GetCount()const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	};
}
