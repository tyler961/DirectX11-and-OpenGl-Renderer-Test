#include "pch.h"
#include "WindowsWindow.h"
#include "MTX/Application.h"

#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include "Platform/GraphicsAPI/Direct3D_11/Direct3DContext.h"

#include "..//resource.h"

namespace MTX {

	WindowsWindow WindowsWindow::s_WindowClass;


	// HAVE TO CALL INIT AFTER CREATE
	Window* Window::Create(const WindowProperties& props)
	{
		return new WindowsWindow();
	}

	WindowsWindow::WindowsWindow()
		:hInst (GetModuleHandle(nullptr)), m_WindowHandle(nullptr), m_GraphicsContext(nullptr)
	{
		// ICONS NOT LOADING, CANT FIGURE OUT WHY
		// POSSIBLY ADD RESOURCE TO SANDBOX????
		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof(wc);
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = HandleMsgStatic;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = GetInstance();
		wc.hIcon = static_cast<HICON>(LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0));
		wc.hCursor = nullptr;
		wc.hbrBackground = nullptr;
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = GetWindClassName();
		wc.hIconSm = static_cast<HICON>(LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0));;

		RegisterClassEx(&wc);
	}

	WindowsWindow::~WindowsWindow()
	{
		// Windows API code for destroying window
		DestroyWindow(m_WindowHandle);
	}

	void WindowsWindow::Init(const WindowProperties& props)
	{
		// Need to use wstrings to convert to wchar_t for window to create the window class and handle
		// Using this method, if the user does not only use ASCII characters it will fail in the conversion

		std::wstring tmp(props.Title.begin(), props.Title.end());
		m_Data.Title = tmp;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		MTX_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		m_WindowHandle = CreateWindowEx(
			0,
			WindowsWindow::GetWindClassName(),
			m_Data.Title.c_str(),
			WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_SIZEBOX,
			200, 200, m_Data.Width, m_Data.Height,
			nullptr, nullptr, hInst, nullptr
		);

		ShowWindow(m_WindowHandle, SW_SHOW);

		m_GraphicsContext = new Direct3DContext(&m_WindowHandle);
		m_GraphicsContext->Init();

		// Create Direct3DContext(m_Window)
		// Init Direct3DContext

		SetVSync(true);

		// Set callbacks for window Events
	}

	void WindowsWindow::OnUpdate()
	{
		//MTX_CORE_INFO("Running!!!");
		GetMessage(&m_Msg, nullptr, 0, 0);
		TranslateMessage(&m_Msg);
		DispatchMessage(&m_Msg);

		m_GraphicsContext->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		// Setup VSync settings here
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	inline void* WindowsWindow::GetNativeWindow() const
	{
		return nullptr;
	}

	void WindowsWindow::Shutdown()
	{
		// Destroy window 
	}
	LRESULT WindowsWindow::HandleMsgStatic(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (msg == WM_NCCREATE)
		{
			// extract ptr to window class from creation data
			const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
			WindowsWindow* const pWnd = static_cast<WindowsWindow*>(pCreate->lpCreateParams);
			// set WinAPI-managed user data to store ptr to window instance
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
			// set message proc to normal (non-setup) handler now that setup is finished
			SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&WindowsWindow::HandleMsgThunk));
			// forward message to window instance handler
			return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	LRESULT WindowsWindow::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		// retrieve ptr to window instance
		WindowsWindow* const pWnd = reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		// forward message to window instance handler
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}
	LRESULT WindowsWindow::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
			case WM_CLOSE:
			{
				PostQuitMessage(0);
				WindowCloseEvent event;
				Application::Get().OnEvent(event);
				return 0;
			}
						
			case WM_KEYDOWN:
			{
				KeyPressedEvent event((int)wParam, 0);
				Application::Get().OnEvent(event);
				break;
			}

			case  WM_KEYUP:
			{
				KeyReleasedEvent event((int)wParam);
				Application::Get().OnEvent(event);
				break;
			}

			case WM_CHAR:
			{
				KeyTypedEvent event((int)wParam);
				Application::Get().OnEvent(event);
				break;
			}

			case WM_MOUSEMOVE:
			{
				MouseMovedEvent event((float)GET_X_LPARAM(lParam), (float)GET_Y_LPARAM(lParam));
				Application::Get().OnEvent(event);
				break;
			}

			case WM_LBUTTONDOWN:
			{
				MouseButtonPressedEvent event(1);
				Application::Get().OnEvent(event);
				break;
			}

			case WM_LBUTTONUP:
			{
				MouseButtonReleasedEvent event(1);
				Application::Get().OnEvent(event);
				break;
			}

			case WM_RBUTTONDOWN:
			{
				MouseButtonPressedEvent event(2);
				Application::Get().OnEvent(event);
				break;
			}

			case WM_RBUTTONUP:
			{
				MouseButtonReleasedEvent event(2);
				Application::Get().OnEvent(event);
				break;
			}

			case WM_MOUSEWHEEL:
			{
				MouseScrolledEvent event(0, GET_WHEEL_DELTA_WPARAM(wParam));
				Application::Get().OnEvent(event);
				break;
			}

	
			case WM_SYSKEYDOWN:
			{}
		}
		// Handle the default if we dont implement a different method
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}