#include "PrecompHead.h"
#include "WindowsWindow.h"

namespace Hazel
{
	// ---- Static Declarations -----

	static bool s_GLFWInitialized = false; // to flag inititalization only once, as there can be many windows as well
	WindowBase* WindowBase::Create(const WindowProps& props) 
	{
		return new WindowsWindow(props); // directly setting to return plat_windows-type glfw_Window for now
	}

	// ----- Class (Methods) ----

	WindowsWindow::WindowsWindow(const WindowProps& props) { Init(props); }
	WindowsWindow::~WindowsWindow() { Shutdown(); }
	
	// ----- Startups ------

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		HZ_INFO("Creating window \"{0}\" with resolution: ({1}x{2})", props.Title, props.Width, props.Height);
		if (!s_GLFWInitialized)
		{
			// ToDo: glfwTerminate on system shutdown
			int success = glfwInit(); // initialize glfw lib
			HZ_ASSERT(success, "Could not intialize GLFW!");

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr);
		
		glfwMakeContextCurrent(m_Window); // set the created window as current window
		glfwSetWindowUserPointer(m_Window, &m_Data); // resp struct ptr ref data is passed to event callbacks
		SetVSync(true);
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	// ----- Essentials -----

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	// ----- VSync (Methods) -----

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		
		m_Data.VSync = enabled;
	}
	bool WindowsWindow::IsVSync() const { return m_Data.VSync; }
}