#include "pch.h"
#include "Direct3DShader.h"
#include "Direct3DContext.h"
#include <d3dcompiler.h>
#include <comdef.h>

#include <iostream>

// Add static libaray here, maybe add to project settings later
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

namespace MTX {

	Direct3DShader::Direct3DShader(const LPCWSTR vertexShader, const LPCWSTR pixelShader, GraphicsContext* gfx)
		:m_VertexShader(nullptr), m_PixelShader(nullptr), m_VSBlob(nullptr), m_PSBlob(nullptr)
	{
		////////////////////////////////////////////////////////
		// VertexShader ////////////////////////////////////////
		////////////////////////////////////////////////////////

		// Reads from the compiled binary for vertexshader.hlsl
		HRESULT hr = D3DReadFileToBlob(vertexShader, &m_VSBlob);
		if (hr != S_OK)
			MTX_CORE_ERROR("Error loading VertexShader.cso");

		// Creates the vertexshader with the information we've provided
		hr = gfx->GetDevice()->CreateVertexShader(m_VSBlob->GetBufferPointer(), m_VSBlob->GetBufferSize(), nullptr, &m_VertexShader);
		if (hr != S_OK)
			MTX_CORE_ERROR("Error creating VertexShader");



		// Bind vertexshader to pipeline
		gfx->GetContext()->VSSetShader(m_VertexShader.Get(), nullptr, 0u);

		////////////////////////////////////////////////////////
		// PixelShader /////////////////////////////////////////
		////////////////////////////////////////////////////////

		// Reuse blob from before
		hr = D3DReadFileToBlob(pixelShader, &m_PSBlob);
		if (hr != S_OK)
			MTX_CORE_ERROR("Error loading PixelShader.cso");

		// Creates the pixelshader with the information we've provided
		hr = gfx->GetDevice()->CreatePixelShader(m_PSBlob->GetBufferPointer(), m_PSBlob->GetBufferSize(), nullptr, &m_PixelShader);
		if (hr != S_OK)
			MTX_CORE_ERROR("Error creating PixelShader");

		// Bind vertexshader to pipeline
		gfx->GetContext()->PSSetShader(m_PixelShader.Get(), nullptr, 0u);
	}

	void Direct3DShader::Bind() const
	{

	}

	void Direct3DShader::Unbind() const
	{

	}
}