project "GLFW"
	location "master"
	kind "StaticLib"
	language "C"

	files -- common file dependencies for all platforms
	{
		"%{prj.location}/include/GLFW/glfw3.h",
		"%{prj.location}/include/GLFW/glfw3native.h",
		"%{prj.location}/src/glfw_config.h",
		"%{prj.location}/src/context.c",
		"%{prj.location}/src/init.c",
		"%{prj.location}/src/input.c",
		"%{prj.location}/src/monitor.c",
		"%{prj.location}/src/vulkan.c",
		"%{prj.location}/src/window.c",
		-- changes w.r.t latest glfw version, extra files to be included
		"%{prj.location}/src/platform.c",
		"%{prj.location}/src/null_**.c", -- add all '.c' files starting with 'null_'
	}

	filter "system:linux" -- linux-platform based dependencies
		pic "On"
		systemversion "latest"
		staticruntime "On"
		files
		{
			"%{prj.location}/src/x11_init.c",
			"%{prj.location}/src/x11_monitor.c",
			"%{prj.location}/src/x11_window.c",
			"%{prj.location}/src/xkb_unicode.c",
			"%{prj.location}/src/posix_time.c",
			"%{prj.location}/src/posix_thread.c",
			"%{prj.location}/src/glx_context.c",
			"%{prj.location}/src/egl_context.c",
			"%{prj.location}/src/osmesa_context.c",
			"%{prj.location}/src/linux_joystick.c",
			-- changes w.r.t latest glfw version, extra files to be included
			"%{prj.location}/src/posix_module.c",
		}
		defines
		{
			"_GLFW_X11"
		}

	filter "system:windows" -- windows-platform based dependencies
		systemversion "latest"
		staticruntime "On"
		files
		{
			"%{prj.location}/src/win32_init.c",
			"%{prj.location}/src/win32_joystick.c",
			"%{prj.location}/src/win32_monitor.c",
			"%{prj.location}/src/win32_time.c",
			"%{prj.location}/src/win32_thread.c",
			"%{prj.location}/src/win32_window.c",
			"%{prj.location}/src/wgl_context.c",
			"%{prj.location}/src/egl_context.c",
			"%{prj.location}/src/osmesa_context.c",
			-- changes w.r.t latest glfw version, extra files to be included
			"%{prj.location}/src/win32_module.c",
		}
		defines 
		{ 
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
