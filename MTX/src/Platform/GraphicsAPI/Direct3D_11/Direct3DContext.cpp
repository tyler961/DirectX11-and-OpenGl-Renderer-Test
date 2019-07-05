#include "pch.h"
#include "Direct3DContext.h"
#include "MTX/Core.h"
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
			0,
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
		// from m_Context, funtions beginnings coorispond with the pipeline for Direct3D 11. (msdn pipelines for direc3d version 11)
		// IA: Input Assembler
		// VS: Vertex Shader
		// HS: Hull Shader
		// DS: Domain Shader
		// GS: Geometry Shader
		// PS: Pixel Shader
		// OM: Output Merger
		// RS: Rasterizer Stage

		// Simple struct to hold vertex values
		struct Vertex 
		{
			float x, y;
		};

		// Array of vertices to plot the points
		const Vertex vertices[] =
		{
			{  0.0f,  0.5f },	// top of triangle
			{  0.5f, -0.5f },   // right corner
			{ -0.5f, -0.5f }    // left corner
		};

		// Vertex Buffer
		COMPTR(ID3D11Buffer) vertexBuffer;

		// Buffer Descriptor:
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
		bd.ByteWidth = sizeof(vertices);
		bd.StructureByteStride = sizeof(Vertex);

		// D3D11_SUBRESOURCE_DATA, only thing we care about filling out in that structure is a const void* that points to our data. other two things only have to do with textures, nothing else
		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = vertices;

		// Creates all kinds of buffers that you want
		// V1: Descriptor of the kind of buffer you want to create
		// V2: D3D11_SUBRESOURCE_DATA, only thing we care about filling out in that structure is a const void* that points to our data. other two things only have to do with textures, nothing else
		// V3: The object to fill with the vertex buffer, in this case a D3D11Buffer*
		HRESULT hr = m_Device->CreateBuffer(&bd, &sd, &vertexBuffer);
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
		m_Context->IASetVertexBuffers(0u, 1u, vertexBuffer.GetAddressOf(), &stride, &offset);

		////////////////////////////////////////////////////////
		// VertexShader ////////////////////////////////////////
		////////////////////////////////////////////////////////

		// Create vertex shader
		COMPTR(ID3D11VertexShader) vertexShader;
		COMPTR(ID3DBlob) blob;

		// Reads from the compiled binary for vertexshader.hlsl
		hr = D3DReadFileToBlob(L"C:/dev/MTX_Engine/MTX/VertexShader.cso", &blob);
		if (hr != S_OK)
			MTX_CORE_ERROR("Error loading VertexShader.cso");

		// Creates the vertexshader with the information we've provided
		hr = m_Device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &vertexShader);
		if (hr != S_OK)
			MTX_CORE_ERROR("Error creating VertexShader");

		// Bind vertexshader to pipeline
		m_Context->VSSetShader(vertexShader.Get(), nullptr, 0u);

		// HAVE TO CREATE VERTEX SHADER FIRST!!!!!!!!!!!!
		// Input(vertex) layout (2d position only)
		// Describes the input layout for our Struct Vertex
		// Layout:
		// Semantic Name, Semantic Index, Format, Input slot, AlignedByteOffset, InputSlotClass, InstanceDataSetRate
		COMPTR(ID3D11InputLayout) inputLayout;
		const D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{"Position", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
			// From format, R32G32 means we have two 32 floats in our struct
		};
		// CreateInputLayout
		// const D3D11_INPUT_ELEMENT_DESC *pInputElementDescs	Input element desc
		// UINT NumElements										Number of elements
		// const void *pShaderBytecodeWithInputSignature		Byte code of a vertex shader
		// SIZE_T BytecodeLength								Length of that bytecode
		// ID3D11InputLayout **ppInputLayout					Our input layout we created
		hr = m_Device->CreateInputLayout(
			ied, (UINT)std::size(ied),
			blob->GetBufferPointer(),
			blob->GetBufferSize(),
			&inputLayout
		);
		if (hr != S_OK)
			MTX_CORE_ERROR("Error creating Input Layout!!!");

		// Bind InputLayout
		m_Context->IASetInputLayout(inputLayout.Get());


		////////////////////////////////////////////////////////
		// PixelShader /////////////////////////////////////////
		////////////////////////////////////////////////////////

		// Create PixelShader
		COMPTR(ID3D11PixelShader) pixelShader;
		// Reuse blob from before
		hr = D3DReadFileToBlob(L"C:/dev/MTX_Engine/MTX/PixelShader.cso", &blob);
		if (hr != S_OK)
			MTX_CORE_ERROR("Error loading PixelShader.cso");

		// Creates the pixelshader with the information we've provided
		hr = m_Device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &pixelShader);
		if (hr != S_OK)
			MTX_CORE_ERROR("Error creating PixelShader");

		// Bind vertexshader to pipeline
		m_Context->PSSetShader(pixelShader.Get(), nullptr, 0u);

		// Bind render TargetView
		// When getting a pointer to a pointer it automatically frees the old pointer. Ex. &blob frees the old blob and retargets it
		// Hence we don't want to free the targetview, so we use m_TargetView.GetAddressOf();
		m_Context->OMSetRenderTargets(1u, m_TargetView.GetAddressOf(), nullptr);

		// Set primitive topology to triangle list (so it knows how to draw the vertices we've given it
		m_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// Configure viewport (viewports map whats being draw to the actual screen) ex. the whole screen, a small section for the minimap, HUD, etc
		// Setting up viewport is self explainatory
		D3D11_VIEWPORT vp;
		vp.Width = 1920;
		vp.Height = 1080;
		vp.MinDepth = 0;
		vp.MaxDepth = 1;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		// Bind viewport to pipeline
		m_Context->RSSetViewports(1u, &vp);


		// Number of vertices, which one to start with, draw them
		m_Context->Draw( (UINT)std::size(vertices), 0u);
	}
}