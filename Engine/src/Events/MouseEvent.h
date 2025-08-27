#pragma once

#include "EventBase.h"

namespace Hazel {

	class HAZEL_API MouseMovedEvent : public EventBase
	{
	private:
		float m_MouseX, m_MouseY;

	public:
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) { }

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << GetX() << ", " << GetY();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EvCat_Mouse | EvCat_Input)
	};

	class HAZEL_API MouseScrolledEvent : public EventBase
	{
	private:
		float m_OffsetX, m_OffsetY;

	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_OffsetX(xOffset), m_OffsetY(yOffset) {
		}

		inline float GetXOffset() const { return m_OffsetX; }
		inline float GetYOffset() const { return m_OffsetY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
			EVENT_CLASS_CATEGORY(EvCat_Mouse | EvCat_Input)
	};

	// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- //

	class HAZEL_API MouseBtnEvent : public EventBase
	{
	protected:
		int m_Button;
		MouseBtnEvent(int button) : m_Button(button) { }

	public:
		inline int GetMouseButton() { return m_Button; }

		EVENT_CLASS_CATEGORY(EvCat_Mouse | EvCat_Input)
	};

	class HAZEL_API MouseBtnPressedEvent : public MouseBtnEvent
	{
	public:
		MouseBtnPressedEvent(int button) : MouseBtnEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseBtnPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseBtnPressed)
	};

	class HAZEL_API MouseBtnReleasedEvent : public MouseBtnEvent
	{
	public:
		MouseBtnReleasedEvent(int button) : MouseBtnEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseBtnReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseBtnReleased)
	};
}