#pragma once
#include "Core.h"

namespace Hazel {

	class HAZEL_API ApplicationBase
	{
	public:
		virtual void Run();
	};

	// TO BE DEFINED IN CLIENT
	ApplicationBase* CreateApplication();
}