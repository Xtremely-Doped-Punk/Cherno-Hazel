#include "PrecompHead.h"
#include "WindowsWindow.h"

#include "Events/AppEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

namespace Hazel
{
	// ---- Static Declarations -----

	static bool s_GLFWInitialized = false; // to flag inititalization only once, as there can be many windows as well
	WindowBase* WindowBase::Create(const WindowProps& props) 
	{
		return new WindowsWindow(props); // directly setting to return plat_windows-type glfw_Window for now
	}

	static void GLFWErrorCallback(int code, const char* description)
	{
		HZ_ERROR("GLFW Error ({0}): {1}", code, description);
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
			glfwSetErrorCallback(GLFWErrorCallback); // set common error callbacks to a static debugger
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr);
		
		glfwMakeContextCurrent(m_Window); // set the created window as current window
		// glfw.user_ptr -> a spot (void ptr) for us to put any kinda data we want
		// this is like a attachment to the glfw.Window obj, using window ref, we can get this user data as well
		glfwSetWindowUserPointer(m_Window, &m_Data); // resp struct ptr ref data is passed to event callbacks
		SetVSync(true);

		
		// <<< Set GLFW Callbacks >>>
		// Lambda exp syntax: [capture-clause] (parameters) -> return-type { definition }
		// []		Capture nothing from outside (only globals / constexpr-ish cases).
		// [=]		Capture everything used in the body by copy (default by value).
		// [&]		Capture everything used by reference.
		// [x, &y]	Capture x by copy, y by reference.
		// [this]	Only capture this (typical in member functions when the lambda calls members).
		// [=, &y]	Default copy, but y by reference.
		
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				auto data = (WindowData*)glfwGetWindowUserPointer(window);
				data->Width = width;
				data->Height = height;

				WindowResizeEvent event(width, height);
				data->EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				auto data = (WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data->EventCallback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				auto data = (WindowData*)glfwGetWindowUserPointer(window);
				EventBase *event;

				switch (action)
				{
					case GLFW_PRESS:
					{
						event = new KeyPressedEvent(key, 0);
						break;
					}
					case GLFW_RELEASE:
					{
						event = new KeyReleasedEvent(key);
						break;
					}
					case GLFW_REPEAT:
					{
						event = new KeyPressedEvent(key, 1);						
						break;
					}
				}
				if (data) data->EventCallback(*event);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				auto data = (WindowData*)glfwGetWindowUserPointer(window);
				EventBase *event;

				switch (action)
				{
					case GLFW_PRESS:
					{
						event = new MouseBtnPressedEvent(button);
						break;
					}
					case GLFW_RELEASE:
					{
						event = new MouseBtnReleasedEvent(button);
						break;
					}
				}
				if (data) data->EventCallback(*event);
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
			{
				auto data = (WindowData*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent event((float)xoffset, (float)yoffset);
				data->EventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
			{
				auto data = (WindowData*)glfwGetWindowUserPointer(window);
				MouseMovedEvent event((float)xpos, (float)ypos);
				data->EventCallback(event);
			});
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