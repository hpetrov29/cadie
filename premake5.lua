workspace "CADie"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "CADie/external/GLFW/include"
IncludeDir["GLAD"] = "CADie/external/GLAD/include"
IncludeDir["ImGui"] = "CADie/external/imgui"

group "Dependencies"
	include "CADie/external/GLFW"
	include "CADie/external/GLAD"
	include "CADie/external/imgui"
group ""

project "CADie"
	location "CADie"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "CADie/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/external/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"CADIE_BUILD_DLL",
			"CADIE_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "CADIE_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "CADIE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "CADIE_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"CADie/external/spdlog/include",
		"CADie/src"
	}

	links
	{
		"CADie"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"CADIE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "CADIE_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "CADIE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "CADIE_DIST"
		runtime "Release"
		optimize "On"
