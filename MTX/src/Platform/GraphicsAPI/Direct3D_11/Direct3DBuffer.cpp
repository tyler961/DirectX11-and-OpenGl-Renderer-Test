#include "pch.h"
#include "Direct3DBuffer.h"
#include "Direct3DContext.h"
#include "Direct3DShader.h"

namespace MTX {

	Direct3DVertexBuffer::Direct3DVertexBuffer(const Vertex* vertices, uint32_t size, GraphicsContext* gfx)
		:m_VertexBuffer(nullptr)
	{
		// Buffer Descriptor :
		// UINT ByteWidth				Size in bytes
		// D3D11_USAGE Usage			Look up values if needed, most common is D3D11_USAGE_DEFAULT (Allows reading and writing access by the GPU)
		// UINT BindFlags				How it's going to be bound to the buffer (D3D11_BIND_VERTEX_BUFFER, Index_Buffer, Shader_Resource, Constant_Buffer etc) (msdn d3d11_bind_flag enumeration for lookup)
		// UINT CPUAccessFlags			0 to not allow the cpu access, additional flags for d3d11_cpu_access_flag
		// UINT MiscFlags				Not using any for triangle drawing, for future reference d3d11_resource_misc_flag
		// UINT StructureByteStride		The size of every vertex in the structure in bytes
		D3D11_BUFFER_DESC bd = {};
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.CPUAccessFlags = 0u;
		bd.MiscFlags = 0u;
		bd.ByteWidth = size;
		bd.StructureByteStride = sizeof(Vertex);

		// D3D11_SUBRESOURCE_DATA, only thing we care about filling out in that structure is a const void* that points to our data. other two things only have to do with textures, nothing else
		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = vertices;

		// Creates all kinds of buffers that you want
		// V1: Descriptor of the kind of buffer you want to create
		// V2: D3D11_SUBRESOURCE_DATA, only thing we care about filling out in that structure is a const void* that points to our data. other two things only have to do with textures, nothing else
		// V3: The object to fill with the vertex buffer, in this case a D3D11Buffer*
		HRESULT hr = gfx->GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
		if (hr != S_OK)
			MTX_CORE_ERROR("m_Device->CreateBuffer Failed!!!");

		// V1: Where to start in your array of buffers
		// V2: Number of vertex buffers in your vertex buffer array 
		// V3: The array of vertex buffers. It takes in a pointer to an array of vertex buffer pointers
		// V4: Strides, the distance between the vertexes in bytes
		// V5: Pointer to an array of offset values, where to start in each buffer in the array
		// Bind vertex buffer to pipeline
		const UINT stride = sizeof(Vertex);
		const UINT offset = 0u;
		gfx->GetContext()->IASetVertexBuffers(0u, 1u, m_VertexBuffer.GetAddressOf(), &stride, &offset);
	}

	void Direct3DVertexBuffer::Bind() const
	{
	}

	void Direct3DVertexBuffer::Unbind() const
	{
	}
	void Direct3DVertexBuffer::SetLayout(std::string name, ShaderDataType type, GraphicsContext* gfx, Direct3DShader* shader)
	{
		DXGI_FORMAT formatType = GetFormat(type);
		if (formatType == DXGI_FORMAT_UNKNOWN)
			MTX_CORE_ASSERT(false, "Format Unknown for Direct3D SetLayout()");

		const D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{ name.c_str(), 0, formatType, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		// CreateInputLayout
		// const D3D11_INPUT_ELEMENT_DESC *pInputElementDescs	Input element desc
		// UINT NumElements										Number of elements
		// const void *pShaderBytecodeWithInputSignature		Byte code of a vertex shader
		// SIZE_T BytecodeLength								Length of that bytecode
		// ID3D11InputLayout **ppInputLayout					Our input layout we created
		HRESULT hr = gfx->GetDevice()->CreateInputLayout(
			ied, (UINT)std::size(ied),
			shader->m_VSBlob->GetBufferPointer(),
			shader->m_VSBlob->GetBufferSize(),
			&m_InputLayout
		);
		if (hr != S_OK)
			MTX_CORE_ERROR("Error creating Input Layout!!!");

		// Bind InputLayout
		gfx->GetContext()->IASetInputLayout(m_InputLayout.Get());
	}


	DXGI_FORMAT Direct3DVertexBuffer::GetFormat(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:     return DXGI_FORMAT_UNKNOWN;
			case ShaderDataType::Float2:    return DXGI_FORMAT_R32G32_FLOAT;
			case ShaderDataType::Float3:    return DXGI_FORMAT_R32G32B32_FLOAT;
			case ShaderDataType::Float4:    return DXGI_FORMAT_R32G32B32A32_FLOAT;
			case ShaderDataType::Mat3:      return DXGI_FORMAT_UNKNOWN;
			case ShaderDataType::Mat4:      return DXGI_FORMAT_UNKNOWN;
			case ShaderDataType::Int:       return DXGI_FORMAT_UNKNOWN;
			case ShaderDataType::Int2:		return DXGI_FORMAT_R32G32_UINT;
			case ShaderDataType::Int3:		return DXGI_FORMAT_R32G32B32_UINT;
			case ShaderDataType::Int4:		return DXGI_FORMAT_R32G32B32A32_UINT;
			case ShaderDataType::Bool:		return DXGI_FORMAT_UNKNOWN;
		}
	}
}