#pragma once
#include "Hazel/Core.h"
#include "Events/EventBase.h"
#include "WindowBase.h"

namespace Hazel {

	class HAZEL_API ApplicationBase
	{
	private:
		// since application class is supposed to a be a singleton, 
		// uniq ptr automatically gets deleted without redundancy when app terminates
		std::unique_ptr<WindowBase> m_Window;
		bool m_Running = true;

	public:
		ApplicationBase();
		virtual void Run();
	};

	// TO BE DEFINED IN CLIENT
	ApplicationBase* CreateApplication();
}