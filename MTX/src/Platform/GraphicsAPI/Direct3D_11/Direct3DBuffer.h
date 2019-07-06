#pragma once
#include "Renderer/Buffer.h"

namespace MTX {

	class Direct3DVertexBuffer : public VertexBuffer
	{
	public:
		Direct3DVertexBuffer(const Vertex* vertices, uint32_t size, GraphicsContext* gfx);
		virtual ~Direct3DVertexBuffer() {}

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetLayout(std::string name, ShaderDataType type, GraphicsContext* gfx, Direct3DShader* shader) override;

		virtual COMPTR(ID3D11Buffer) GetVertexBuffer() const override { return m_VertexBuffer; }

	private:
		DXGI_FORMAT GetFormat(ShaderDataType type);
		COMPTR(ID3D11Buffer) m_VertexBuffer;
		COMPTR(ID3D11InputLayout) m_InputLayout;
	};
}