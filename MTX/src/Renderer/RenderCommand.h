#pragma once

#include "RendererAPI.h"

namespace MTX {

	class RenderCommand
	{
	public:
		inline static void SetClearColor(float r, float g, float b, GraphicsContext* gfx) { s_RendererAPI->SetClearColor(r, g, b, gfx); } // send in colors to each

		inline static void Clear() { s_RendererAPI->Clear(); }

		inline static void DrawIndexed() { s_RendererAPI->DrawIndexed(); } // Send in a vertex array

		inline static void SetRenderTarget(GraphicsContext* gfx, COMPTR(ID3D11RenderTargetView) targetView) { s_RendererAPI->SetRenderTarget(gfx, targetView); }

		inline static void SetViewport(float width, float height, float minDepth, float maxDepth, GraphicsContext* gfx, float topX = 0, float topY = 0)
		{ 
			s_RendererAPI->SetViewport(width, height, minDepth, maxDepth, gfx, topX, topY); 
		}

		inline static RendererAPI* GetRendererAPI() { return s_RendererAPI; }

	private:
		static RendererAPI* s_RendererAPI;
	};
}
