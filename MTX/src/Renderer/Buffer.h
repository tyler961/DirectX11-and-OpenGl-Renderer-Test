#pragma once

#include "WindowsInclude.h"
#include "MTX/Log.h"
#include "MTX/Core.h"
#include <d3d11.h>
#include "GraphicsContext.h"
#include "Platform/GraphicsAPI/Direct3D_11/Direct3DShader.h"

namespace MTX {

	struct Vertex
	{
		float x, y;
	};

	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:     return 4;
			case ShaderDataType::Float2:    return 4 * 2;
			case ShaderDataType::Float3:    return 4 * 3;
			case ShaderDataType::Float4:    return 4 * 4;
			case ShaderDataType::Mat3:      return 4 * 3 * 3;
			case ShaderDataType::Mat4:      return 4 * 4 * 4;
			case ShaderDataType::Int:       return 4;
			case ShaderDataType::Int2:		return 4 * 2;
			case ShaderDataType::Int3:		return 4 * 3;
			case ShaderDataType::Int4:		return 4 * 4;
			case ShaderDataType::Bool:		return 1;
		}

		MTX_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	class BufferElement
	{
		BufferElement(ShaderDataType type, const std::string name, bool normalized = 0)
			:Name(name), Type(type), Offset(0), Size(ShaderDataTypeSize(type)), Normalized(normalized)
		{}

		// Default Constructor
		BufferElement()
		{}

		std::string Name;
		ShaderDataType Type;
		uint32_t Offset;
		uint32_t Size;
		bool Normalized;
	};

	class BufferLayout
	{
	public:
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements)
			:m_Elements(elements)
		{

		}

	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual COMPTR(ID3D11Buffer) GetVertexBuffer() const = 0;
		virtual void SetLayout(std::string name, ShaderDataType type, GraphicsContext* gfx, Direct3DShader* shader) = 0;

		static VertexBuffer* Create(const Vertex* vertices, uint32_t size, GraphicsContext* gfx);
	};
}