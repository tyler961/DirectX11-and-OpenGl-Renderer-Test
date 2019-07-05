#pragma once

#include "Core.h"

#include "Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include <memory>

namespace MTX {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		bool m_Running = true;
		static Application* s_Instance;

		std::unique_ptr<Window> m_Window;
	};

	// To be defined in client app
	Application* CreateApplication();
}