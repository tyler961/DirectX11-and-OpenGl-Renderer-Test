#pragma once

#include "RendererAPI.h"

namespace MTX {

	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(); // Submit shader object and vertex array object

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			// Projection matrix
		};

		static SceneData* s_SceneData;
	};
}