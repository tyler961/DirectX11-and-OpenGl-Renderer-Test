#pragma once

#include "Renderer/GraphicsContext.h"

namespace MTX {

	class Direct3DContext : public GraphicsContext
	{
	public:
		Direct3DContext(HWND* windowHandle);
		~Direct3DContext();
		virtual void Init() override;
		virtual void SwapBuffers() override;

		// Temp to figure out what needs to be done
		virtual void TmpDraw() override;

		virtual COMPTR(ID3D11Device) GetDevice() override { return m_Device; }
		virtual COMPTR(IDXGISwapChain) GetSwapChain() override { return m_SwapChain; }
		virtual COMPTR(ID3D11DeviceContext) GetContext() override { return m_Context; }
		virtual COMPTR(ID3D11RenderTargetView) GetTargetView() override { return m_TargetView; }

	private:
		// Implement later with comptrs
		HWND*							m_WindowHandle;
		COMPTR(ID3D11Device)			m_Device = nullptr;
		COMPTR(IDXGISwapChain)			m_SwapChain = nullptr;
		COMPTR(ID3D11DeviceContext)		m_Context = nullptr;
		COMPTR(ID3D11RenderTargetView)	m_TargetView = nullptr;
	};
}