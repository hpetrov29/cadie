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
IncludeDir["glm"] = "CADie/external/glm"

group "Dependencies"
	include "CADie/external/GLFW"
	include "CADie/external/GLAD"
	include "CADie/external/imgui"
group ""

project "CADie"
	location "CADie"
	kind "StaticLib"
	language "C++"
	staticruntime "on"

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
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
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
			"_CRT_SECURE_NO_WARNINGS",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "CADIE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "CADIE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "CADIE_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"CADie/src",
		"CADie/external",
		"%{IncludeDir.glm}"
	}

	links
	{
		"CADie"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"CADIE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "CADIE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "CADIE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "CADIE_DIST"
		runtime "Release"
		optimize "on"
