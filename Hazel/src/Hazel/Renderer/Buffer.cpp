#include "hzpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Hazel/PlathForm/OpenGL/OpenGLBuffer.h"

namespace Hazel
{
	VertexBuffer* VertexBuffer::Create(float* vertice, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			break;
		case RendererAPI::OpenGL:
			return new OpenGLVertexBuffer(vertice, size);
			break;
		}
		HZ_CORE_ASSERT(false, "Unkown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			break;
		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indices, size);
			break;
		}
		HZ_CORE_ASSERT(false, "Unkown RendererAPI!");
		return nullptr;
	}
}
