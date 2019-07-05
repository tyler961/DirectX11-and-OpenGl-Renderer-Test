#pragma once
#include "GraphicsContext.h"

struct WindowsWindow;

namespace MTX {

	class RendererAPI
	{
	public:
		enum class API { None = 0, DIRECT3D = 1, OPENGL = 2, VULKAN = 3};

	public:
		virtual void SetClearColor(float r, float g, float b, GraphicsContext* gfx) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed() = 0;

		inline static API GetAPI() { return s_API; }

	private:
		static API s_API;
	};
}