outdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" -- using variable common for multiple projects, ex: Debug-Win-x64
-- NOTE: this beta/aplha is not properly exporting for relative paths, so i have kept absolute paths with macros exactly how we define inside the VS

workspace "ChernoHazel" -- solution workspace
	architecture "x64"
	configurations 
	{
		"Debug", -- all logging included
		"Release", -- optim ver with lesser logging
		"Distribution" -- final actual release, with no logging
	}
	-- applying common filters for all projects
	language "C++"
	
	targetdir ("%{wks.location}/_bin/" .. outdir .. "/%{prj.name}") -- output directory: _bin/Debug-Win-x64/ProjectName
	objdir ("%{wks.location}/_obj/" .. outdir .. "/%{prj.name}") -- intermediate directory: _obj/Debug-Win-x64/ProjectName
	
	files
	{
		"%{prj.location}/src/**.h", -- recursively include all files inside Engin/src/ folder
		"%{prj.location}/src/**.cpp", -- mention which file types to inclue, like .h, .cpp for now
	}

	filter "system:windows" -- filters specific to platform
		cppdialect "C++17" -- standard libraries version
		staticruntime "On" -- linking runtime libraries staticly
		systemversion "latest" -- windows SDK version
		defines -- Preprocessor Definitions
		{
			"HZ_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug" -- filters specific to type of config: debug
		defines "HZ_DEBG"
		symbols "On"
	filter "configurations:Release" -- filters specific to type of config: release
		defines "HZ_RELS"
		optimize "On"
	filter "configurations:Distribution" -- filters specific to type of config: distribution
		defines "HZ_DIST"
		optimize "On"

	filter { "toolset:msc*" } -- Add /utf-8 only for MSVC-based toolchains (Visual Studio)
    	buildoptions { "/utf-8" }

-- path root inside projects: relative to the .vcxproj file, i.e. inside project folder

project "Engine"
	location "Engine" -- relative folder location
	kind "SharedLib" -- config-type: Dynamic Library (.dll)
	
	includedirs -- Additional Include Directories
	{
		"%{prj.location}/vendor/spdlog/include",
	}

	filter {"system:windows"}
		defines -- Preprocessor Definitions
		{
			"HZ_BUILD_DLL", -- macro only for engine
		}
		postbuildcommands
		{
			("{MKDIR} ../_bin/" ..outdir .."/Sandbox"), -- create dir just to be safe o first build
			("{COPYFILE} %{cfg.buildtarget.relpath} ../_bin/" .. outdir .. "/Sandbox")
		}


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp" -- config-type: Application (.exe)

	includedirs -- Additional Include Directories
	{
		"%{wks.location}/Engine/vendor/spdlog/include",
		"%{wks.location}/Engine/src",
	}
	links -- add other project refernces here
	{
		"Engine",
	}
