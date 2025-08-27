#pragma once

#ifdef HZ_PLATFORM_WINDOWS  

namespace Hazel
{
	// add external references of Hazel namespace within here
	extern ApplicationBase* CreateApplication();
}

void main()  
{
	Hazel::Log::Init("%^[%D %r] %5!n[%7!s|%-7!!]: (%L)%$ %v"); // my format
	HZ_WARN("Application starting through Hazel Engine's Entry-Point :)");
	auto app = Hazel::CreateApplication();
	app->Run();  
	delete app;  
}  

#endif // HZ_PLATFORM_WINDOWS
