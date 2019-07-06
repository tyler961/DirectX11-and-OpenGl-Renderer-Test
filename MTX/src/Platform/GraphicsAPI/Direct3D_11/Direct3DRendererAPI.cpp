#include "pch.h"
#include "Direct3DRendererAPI.h"
#include "Platform/OS/Windows/WindowsWindow.h"

#include "Direct3DContext.h"

#include <d3d11.h>

namespace MTX {

	void Direct3DRendererAPI::SetClearColor(float r, float g, float b, GraphicsContext* gfx)
	{
		// set clear color with Direct3D
		const float color[] = { r, g, b, 1.0f };
		gfx->GetContext()->ClearRenderTargetView(gfx->GetTargetView().Get(), color);
	}

	void Direct3DRendererAPI::Clear()
	{
		// Clear the screen with Direct3D
	}

	void Direct3DRendererAPI::SetRenderTarget(GraphicsContext* gfx, COMPTR(ID3D11RenderTargetView) targetView)
	{
		gfx->GetContext()->OMSetRenderTargets(1u, targetView.GetAddressOf(), nullptr);
	}

	void Direct3DRendererAPI::SetViewport(float width, float height, float minDepth, float maxDepth, GraphicsContext* gfx, float topX, float topY)
	{
		// Configure viewport (viewports map whats being draw to the actual screen) ex. the whole screen, a small section for the minimap, HUD, etc
		// Setting up viewport is self explainatory
		D3D11_VIEWPORT vp;
		vp.Width = width;
		vp.Height = height;
		vp.MinDepth = minDepth;
		vp.MaxDepth = maxDepth;
		vp.TopLeftX = topX;
		vp.TopLeftY = topY;

		// Bind viewport to pipeline
		gfx->GetContext()->RSSetViewports(1u, &vp);
	}

	void Direct3DRendererAPI::DrawIndexed()
	{
		// Draw vertex array with Direct3D
	}
}
