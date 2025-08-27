#include "PrecompHead.h"
#include "ApplicationBase.h"

#include "Events/AppEvent.h"
#include <GLFW/glfw3.h>

namespace Hazel 
{
	ApplicationBase::ApplicationBase()
	{
		m_Window = std::unique_ptr<WindowBase>(WindowBase::Create());
		// unique ptr ? means we dont have to delete the ptr ourselved when the application terminates
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
