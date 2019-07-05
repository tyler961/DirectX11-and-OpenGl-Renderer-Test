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

	void Direct3DRendererAPI::DrawIndexed()
	{
		// Draw vertex array with Direct3D
	}
}
