#pragma once

#include "EventBase.h"

namespace Hazel {

	class HAZEL_API WindowResizeEvent : public EventBase
	{
	private:
		unsigned int m_Width, m_Height;
	
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) { }

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowCloseEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EvCat_Application)
	};

	class HAZEL_API WindowCloseEvent : public EventBase
	{
	public:
		WindowCloseEvent() { }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowCloseEvent called!";
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EvCat_Application)
	};

	// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- //
	// non-modular events that are always to be present, but for the sake of intrinsic event module, implemented for now

	class HAZEL_API AppTickEvent : public EventBase
	{
	public:
		AppTickEvent() {}
		std::string ToString() const override { return "AppTickEvent called!"; }

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EvCat_Application)
	};

	class HAZEL_API AppUpdateEvent : public EventBase
	{
	public:
		AppUpdateEvent() {}
		std::string ToString() const override { return "AppUpdateEvent called!"; }

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EvCat_Application)
	};

	class HAZEL_API AppRenderEvent : public EventBase
	{
	public:
		AppRenderEvent() {}
		std::string ToString() const override { return "AppRenderEvent called!"; }

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EvCat_Application)
	};


}