#pragma once

#include "Renderer/RendererAPI.h"

namespace MTX {

	class Direct3DRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(float r, float g, float b, GraphicsContext* gfx) override; // Send color
		virtual void Clear() override;

		virtual void SetRenderTarget(GraphicsContext* gfx, COMPTR(ID3D11RenderTargetView) targetView) override;

		virtual void SetViewport(float width, float height, float minDepth, float maxDepth, GraphicsContext* gfx, float topX = 0, float topY = 0) override;

		virtual void DrawIndexed() override; // Send Vertex Array
	};
}