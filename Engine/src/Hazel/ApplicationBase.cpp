#include "PrecompHead.h"
#include "ApplicationBase.h"

#include "Events/AppEvent.h"
#include "Hazel/Log.h"

namespace Hazel {

	void ApplicationBase::Run()
	{
		WindowResizeEvent e(1280, 720);
		HZ_TRACE(e); // printing event into log stream directly to check overloaded fn workin crtly
		LOG_ERROR("Check if event -> \"{}\" in Application Category? {}", e.GetName(), e.IsInCategory(EvCat_Application));
		
		while (true); // keep application open indefnitely for starters
	}

}
