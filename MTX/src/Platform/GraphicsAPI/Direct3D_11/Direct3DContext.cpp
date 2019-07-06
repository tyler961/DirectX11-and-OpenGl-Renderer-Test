#include "pch.h"
#include "Direct3DContext.h"
#include "MTX/Core.h"
#include "Direct3DShader.h"
#include "Direct3DBuffer.h"
#include "Renderer/Buffer.h"
#include "Direct3DRendererAPI.h"
#include <d3dcompiler.h>


// Add static libaray here, maybe add to project settings later
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

namespace MTX {

	Direct3DContext::Direct3DContext(HWND* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		MTX_CORE_ASSERT(windowHandle, "Direc3D windowHandle is nullptr!!!");
	}

	Direct3DContext::~Direct3DContext()
	{}

	void Direct3DContext::Init()
	{
		// Create swapchain structure
		DXGI_SWAP_CHAIN_DESC sd = {};
		sd.BufferDesc.Width = 0;													// Makes buffer figure it out from the window
		sd.BufferDesc.Height = 0;
		sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;							// Layout of the pixels
		sd.BufferDesc.RefreshRate.Numerator = 0;									// Refresh rate, we dont set one
		sd.BufferDesc.RefreshRate.Denominator = 0;
		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;						// Because width and height are 0, no scaling is required
		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		sd.SampleDesc.Count = 1;													// Basically antialiasing, off right now
		sd.SampleDesc.Quality = 0;													// Basically antialiasing, off right now
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;							// Buffer to be used as a render target
		sd.BufferCount = 1;															// How many back buffers we want, so two total buffers. Front and back
		sd.OutputWindow = *m_WindowHandle;											// Window to draw to
		sd.Windowed = TRUE;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;									// Normal, vanilla
		sd.Flags = 0;																// No flags

		// Initialize Direct3D
		D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			D3D11_CREATE_DEVICE_DEBUG,
			nullptr,
			0,
			D3D11_SDK_VERSION,
			&sd,
			&m_SwapChain,
			&m_Device,
			nullptr,
			&m_Context
		);

		// Used to set target view
		COMPTR(ID3D11Resource) backBuffer;
		m_SwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &backBuffer);
		m_Device->CreateRenderTargetView(
			backBuffer.Get(),
			nullptr,
			&m_TargetView
		);

		// Send out info of vendor, renderer and version
	}

	void Direct3DContext::SwapBuffers()
	{
		// First variable:  Framerate based off monitor refresh rate. 1u is 60, 2u is half so 30 frames
		// Second variable: Flags
		m_SwapChain->Present(1u, 0u);
	}

	void Direct3DContext::TmpDraw()
	{
		//// Array of vertices to plot the points
		//const Vertex vertices[] =
		//{
		//	{  0.0f,  0.5f },	// top of triangle
		//	{  0.5f, -0.5f },   // right corner
		//	{ -0.5f, -0.5f }    // left corner
		//};

		//// Vertex Buffer
		//VertexBuffer* VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices), this);

		//// Create shader binaries, create shaders, set shaders
		//Direct3DShader shader(L"C:/dev/MTX_Engine/MTX/VertexShader.cso", L"C:/dev/MTX_Engine/MTX/PixelShader.cso", this);

		//// Create Layout for Vertex Shader (MUST CREATE VERTEX SHADER FIRST)
		//VertexBuffer->SetLayout("Position", ShaderDataType::Float2, this, &shader);

		//// Bind render TargetView
		//// When getting a pointer to a pointer it automatically frees the old pointer. Ex. &blob frees the old blob and retargets it
		//// Hence we don't want to free the targetview, so we use m_TargetView.GetAddressOf();
		//m_Context->OMSetRenderTargets(1u, m_TargetView.GetAddressOf(), nullptr);

		//// Set primitive topology to triangle list (so it knows how to draw the vertices we've given it
		//m_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//// Configure viewport (viewports map whats being draw to the actual screen) ex. the whole screen, a small section for the minimap, HUD, etc
		//// Setting up viewport is self explainatory
		//D3D11_VIEWPORT vp;
		//vp.Width = 1920;
		//vp.Height = 1080;
		//vp.MinDepth = 0;
		//vp.MaxDepth = 1;
		//vp.TopLeftX = 0;
		//vp.TopLeftY = 0;
		//// Bind viewport to pipeline
		//m_Context->RSSetViewports(1u, &vp);


		//// Number of vertices, which one to start with, draw them
		//m_Context->Draw( (UINT)std::size(vertices), 0u);
	}
}