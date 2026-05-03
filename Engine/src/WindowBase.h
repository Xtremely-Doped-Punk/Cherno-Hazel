#pragma once
#include "PrecompHead.h"

#include "Hazel/Core.h"
#include "Events/EventBase.h"

namespace Hazel
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Hazel Engine", 
		unsigned int width = 1280, unsigned int height = 720)
		: Title(title), Width(width), Height(height) { }
	};

	// Abstract base Interface representing desktop-sys based (platform independent) Window
	class HAZEL_API WindowBase
	{
	public:
		using EventCallbackFn = std::function<void(EventBase&)>;

		// Default
		virtual ~WindowBase() {}
		virtual void OnUpdate() = 0;

		// Data Members
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window Attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static WindowBase* Create(const WindowProps& props = WindowProps());
	};
}