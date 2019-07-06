#include "pch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/GraphicsAPI/Direct3D_11/Direct3DBuffer.h"

namespace MTX {

	VertexBuffer* VertexBuffer::Create(const Vertex* vertices, uint32_t size, GraphicsContext* gfx)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: MTX_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
		case RendererAPI::API::DIRECT3D: return new Direct3DVertexBuffer(vertices, size, gfx);
		case RendererAPI::API::OPENGL: MTX_CORE_ASSERT(false, "RendererAPI::OPENGL is not currently supported"); return nullptr;
		case RendererAPI::API::VULKAN: MTX_CORE_ASSERT(false, "RendererAPI::VULKAN is not currently supported"); return nullptr;
		}
	}
}