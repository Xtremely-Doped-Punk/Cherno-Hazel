#pragma once
#include "Core.h"
#include "Events/EventBase.h"

namespace Hazel {

	class HAZEL_API ApplicationBase
	{
	public:
		virtual void Run();
	};

	// TO BE DEFINED IN CLIENT
	ApplicationBase* CreateApplication();
}