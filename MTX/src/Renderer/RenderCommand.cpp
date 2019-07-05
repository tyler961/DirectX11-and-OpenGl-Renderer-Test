#include "pch.h"
#include "RenderCommand.h"

#include "Platform/GraphicsAPI/Direct3D_11/Direct3DRendererAPI.h"

namespace MTX {

	RendererAPI* RenderCommand::s_RendererAPI = new Direct3DRendererAPI;
}