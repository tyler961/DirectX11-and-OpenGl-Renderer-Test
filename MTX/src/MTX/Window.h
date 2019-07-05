#pragma once

#include "pch.h"
#include "Core.h"
#include "Events/Event.h"

#include "Renderer/GraphicsContext.h"

namespace MTX {

	struct WindowProperties
	{
		std::string Title;
		unsigned int Width, Height;

		WindowProperties(const std::string& title = "MTX Engine",
			unsigned int width = 1920, unsigned int height = 1080)
			:Title(title), Width(width), Height(height)
		{}
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {};

		virtual void Init(const WindowProperties& props = WindowProperties()) = 0;

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
		virtual GraphicsContext* GetContext() const = 0;
		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProperties& props = WindowProperties());
	};
}

