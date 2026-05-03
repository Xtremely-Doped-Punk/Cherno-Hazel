#include "PrecompHead.h"
#include "ApplicationBase.h"

#include <GLFW/glfw3.h>

namespace Hazel 
{
#define BIND_EVENT_FN(x) std::bind(&ApplicationBase::x, this, std::placeholders::_1)
/*
- wrap a NON-STATIC member so the API only sees (Event&) — _1 is that arg; `this` is fixed.
- std::bind: build a callable by fixing some args now; use _1,_2 for args supplied at call time.
- Why not &ClassName::FunctionName, i.e direct fn pointer?
	- That's a POINTER-TO-MEMBER — needs (object, event). Dispatch<Event>(func) only passes event (func(T&)).
	- std::bind / lambda captures `this` so the call becomes this->Fn(event).
	- Modern alt: [this](T& e) { return OnFoo(e); }  // using lambda fn declaration
*/
	ApplicationBase::ApplicationBase()
	{
		m_Window = std::unique_ptr<WindowBase>(WindowBase::Create());
		// unique ptr ? means we dont have to delete the ptr ourselves when the application terminates

		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	void ApplicationBase::OnEvent(EventBase& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		HZ_TRACE(e); // just debug the events into trace log for now
	}

	bool ApplicationBase::OnWindowClose(WindowCloseEvent& e) // EventFn template: <bool(T&)>
	{
		m_Running = false;
		return true;
	}

	void ApplicationBase::Run()
	{
		WindowResizeEvent e(1280, 720);
		HZ_TRACE(e); // printing event into log stream directly to check overloaded fn workin crtly
		LOG_ERROR("Check if event -> \"{}\" in Application Category? {}", e.GetName(), e.IsInCategory(EvCat_Application));
		
		while (m_Running) // keep application open indefnitely for starters
		{
			// testing glfw window color
			glClearColor(0, .5f, .6f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Window->OnUpdate();
		}
	}
}
