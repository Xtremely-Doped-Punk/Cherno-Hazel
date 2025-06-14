#include <Hazel.h> // client side imports necessary from hazel-engine-apps (add the path in additional-include-dirs)
using namespace Hazel;

class Sandbox : public ApplicationBase
{
public:
	void Run() override
	{
		Print("Welcome to Sandbox!");
		ApplicationBase::Run();
	}
};

namespace Hazel // to define entry point inside hazel
{
	ApplicationBase* CreateApplication()
	{
		return new Sandbox();
	}
}
