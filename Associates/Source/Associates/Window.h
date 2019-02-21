#pragma once
#include "Assoc_pch.h"

#include "Core.h"
#include "Events/Event.h"

namespace Associates
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& Title = "Associates", unsigned int Width = 1280, unsigned int Height = 720) : Title(Title), Width(Width), Height(Height) {}
	};


	//Interface representing a desktop system based window.
	class ASSOC_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;
		
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		
		//Window attributes
		virtual void SetEventCallback(const EventCallbackFn& Callback) = 0;
		virtual void SetVSync(bool bEnabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& Props = WindowProps());
	};
}