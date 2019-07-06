#pragma once

#include "Renderer/Shader.h"
#include "Renderer/GraphicsContext.h"

#include <d3d11.h>

namespace MTX {

	class Direct3DShader : public Shader
	{
	public:
		Direct3DShader(const LPCWSTR vertexShader, const LPCWSTR pixelShader, GraphicsContext* gfx);
		~Direct3DShader() {}

		virtual void Bind() const override;
		virtual void Unbind() const override;

		// Keep references to blob for input layout when it needs m_VSBlob
		COMPTR(ID3DBlob) m_VSBlob;
		COMPTR(ID3DBlob) m_PSBlob;

	private:
		COMPTR(ID3D11VertexShader) m_VertexShader;
		COMPTR(ID3D11PixelShader) m_PixelShader;

	};
}