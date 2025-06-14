#pragma once

#ifdef HZ_PLATFORM_WINDOWS  

namespace Hazel
{
	// add external references of Hazel namespace within here
	extern ApplicationBase* CreateApplication();
}

void main()  
{  
	Hazel::Print("Application starting through Hazel Engine's Entry-Point :)");
	auto app = Hazel::CreateApplication();
	app->Run();  
	delete app;  
}  

#endif // HZ_PLATFORM_WINDOWS
