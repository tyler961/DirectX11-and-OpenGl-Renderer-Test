#include "pch.h"
#include "Application.h"
#include "Window.h"
#include "Platform/OS/Windows/WindowsWindow.h"

#include "Renderer/GraphicsContext.h"
#include "Platform/GraphicsAPI/Direct3D_11/Direct3DContext.h"

#include "Renderer/RenderCommand.h"
#include "Renderer/RendererAPI.h"

#include "Events/KeyEvent.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"

#include "Log.h"

namespace MTX {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		// Only one instance of application should ever exist
		MTX_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->Init();

		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		MTX_CORE_TRACE(e.ToString());
	}


	void Application::Run()
	{
		while (m_Running)
		{
			RenderCommand::SetClearColor(63.0f / 255.0f, 63.0f / 255.0f, 63.0f / 255.0f, m_Window->GetContext());
			m_Window->GetContext()->TmpDraw();
			//RenderCommand::Clear();
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}