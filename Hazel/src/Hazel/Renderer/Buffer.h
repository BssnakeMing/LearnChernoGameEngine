#pragma once


namespace Hazel
{
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer(){};

		virtual void Bind() const{};
		virtual void UnBind() const {};

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
