#pragma once

#include "Renderer/RendererAPI.h"

namespace MTX {

	class Direct3DRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(float r, float g, float b, GraphicsContext* gfx) override; // Send color
		virtual void Clear() override;

		virtual void DrawIndexed() override; // Send Vertex Array
	};
}