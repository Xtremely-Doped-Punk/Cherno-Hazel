#pragma once

#include "EventBase.h"

#include <sstream>

namespace Hazel {

	class HAZEL_API KeyEvent : public EventBase
	{
	protected:
		int m_KeyCode;
		KeyEvent(int keycode) : m_KeyCode(keycode) { }

	public:
		inline int GetKeyCode() const { return m_KeyCode; }
		EVENT_CLASS_CATEGORY(EvCat_Keyboard | EvCat_Input)
	};

	class HAZEL_API KeyPressedEvent : public KeyEvent
	{
	private:
		int m_RepeatCount;
		
	public:
		KeyPressedEvent(int keycode, int repeatCount)
		: KeyEvent(keycode), m_RepeatCount(repeatCount) { }

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent called!";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class HAZEL_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode) : KeyEvent(keycode) { }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent called!";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}