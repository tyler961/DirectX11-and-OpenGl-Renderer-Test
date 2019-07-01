workspace "MTX_Engine"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--Include directories relative to root folder (solution directory)

--include "VAPR/External/GLFW"
--include "VAPR/External/GLAD"
--include "VAPR/External/imgui"


project "MTX"
	location "MTX"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "MTX/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
		--"%{prj.name}/External/GLM/glm/**.hpp",
		--"%{prj.name}/External/GLM/glm/**.inl"

	}

	defines 
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src"
		--"%{prj.name}/External/spdlog/include",
		--"%{prj.name}/External/GLFW/include",
		--"%{prj.name}/External/GLAD/include",
		--"%{prj.name}/External/imgui",
		--"%{prj.name}/External/GLM"
	}

	links
	{
		--"GLFW",
		--"GLAD",
		--"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"MTX_PLATFORM_WINDOWS",
			"MTX_BUILD_DLL",
			"MTX_ENABLE_ASSERTS"
			--"GLFW_INCLUDE_NONE"	
		}

	filter "configurations:Debug"
		defines "MX_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "MX_RELEASE"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		--"VAPR/External/spdlog/include",
		"MTX/src"
		--"VAPR/External",
		--"VAPR/External/GLM"
	}

	links
	{
		"MTX"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"VP_PLATFORM_WINDOWS"		
		}

	filter "configurations:Debug"
		defines "MX_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "MX_RELEASE"
		runtime "Release"
		optimize "on"