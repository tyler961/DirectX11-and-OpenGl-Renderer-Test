#include "pch.h"
#include "Application.h"
#include "Window.h"
#include "Platform/OS/Windows/WindowsWindow.h"

#include "Renderer/GraphicsContext.h"
#include "Platform/GraphicsAPI/Direct3D_11/Direct3DContext.h"
#include "Platform/GraphicsAPI/Direct3D_11/Direct3DRendererAPI.h"
#include "Platform/GraphicsAPI/Direct3D_11/Direct3DShader.h"
#include "Platform/GraphicsAPI/Direct3D_11/Direct3DBuffer.h"

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
		:m_Vertices
		{ {  0.0f,  0.5f },	// top of triangle
		  {  0.5f, -0.5f }, // right corner
		  { -0.5f, -0.5f }, // left corner

		  {  0.5f,  1.0f },
		  {  1.0f,  0.5f },
		  {  0.5f,  0.5f } }    
	
	{
		// Only one instance of application should ever exist
		MTX_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->Init();

		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

	

		// Create Vertex Buffer
		m_VertexBuffer = VertexBuffer::Create(m_Vertices, sizeof(m_Vertices), m_Window->GetGraphicsContext());

		// Create shader binaries, create shaders, set shaders
		m_Shader = new Direct3DShader(L"C:/dev/MTX_Engine/MTX/VertexShader.cso", L"C:/dev/MTX_Engine/MTX/PixelShader.cso", m_Window->GetGraphicsContext());

		// Create Layout for Vertex Buffer
		m_VertexBuffer->SetLayout("Position", ShaderDataType::Float2, m_Window->GetGraphicsContext(), m_Shader);

		RenderCommand::SetRenderTarget(m_Window->GetGraphicsContext(), m_Window->GetGraphicsContext()->GetTargetView());

		RenderCommand::SetViewport(1920, 1080, 0, 1, m_Window->GetGraphicsContext());

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
			RenderCommand::SetClearColor(63.0f / 255.0f, 63.0f / 255.0f, 63.0f / 255.0f, m_Window->GetGraphicsContext());
			
			// Set primitive topology to triangle list (so it knows how to draw the vertices we've given it
			m_Window->GetGraphicsContext()->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			// Number of vertices, which one to start with, draw them
			m_Window->GetGraphicsContext()->GetContext()->Draw((UINT)std::size(m_Vertices), 0u);

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}