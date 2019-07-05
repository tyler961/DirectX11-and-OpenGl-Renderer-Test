#pragma once

#include "WindowsInclude.h"
#include "MTX/Window.h"

namespace MTX {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow();
		virtual ~WindowsWindow();

		virtual void Init(const WindowProperties& props) override;

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		virtual GraphicsContext* GetContext() const override { return m_Context; }

		inline virtual void* GetNativeWindow() const; // { return m_Window }

		static const wchar_t* GetWindClassName() noexcept { return windClassName; }
		static HINSTANCE GetInstance() { return s_WindowClass.hInst; }

		// Private functions
	private:
		virtual void Shutdown();

		static LRESULT CALLBACK HandleMsgStatic(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		LRESULT CALLBACK HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		// Private Memebers
	private:
		HINSTANCE hInst;
		HWND m_WindowHandle;
		MSG m_Msg;
		GraphicsContext* m_Context;

		struct WindowData
		{
			std::wstring Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;

		static constexpr const wchar_t* windClassName = L"MTX Direct3D Engine Window";
		static WindowsWindow s_WindowClass;
	};
}