#include "pch.h"
#include "Renderer.h"

namespace MTX {

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene()
	{
		// set viewprojectionmatrix to camera's view
	}

	void Renderer::EndScene()
	{}

	void Renderer::Submit()
	{
		// bind shaders
		// upload shader uniforms to shader

		// bind vertex array
		
	}
}