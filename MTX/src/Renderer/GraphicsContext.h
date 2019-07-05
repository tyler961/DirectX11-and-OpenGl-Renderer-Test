#pragma once

#include "MTX/Core.h"
#include <d3d11.h>

namespace MTX {

	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		virtual void TmpDraw() = 0;

		virtual COMPTR(ID3D11Device) GetDevice() = 0;
		virtual COMPTR(IDXGISwapChain) GetSwapChain() = 0;
		virtual COMPTR(ID3D11DeviceContext) GetContext() = 0;
		virtual COMPTR(ID3D11RenderTargetView) GetTargetView() = 0;
	};
}