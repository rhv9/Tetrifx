workspace "CowboyPewPew"
    architecture "x86_64"
    startproject "CowboyPewPew"

    configurations
    {
        "Debug",
        "Release",
    }

    flags
    {
        "MultiProcessorCompile"
    }


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "CowboyPewPew/vendor/GLFW/include"
IncludeDir["Glad"] = "CowboyPewPew/vendor/Glad/include"
IncludeDir["ImGui"] = "CowboyPewPew/vendor/imgui/include"

include "CowboyPewPew/vendor/glfw_premake5.lua"
include "CowboyPewPew/vendor/Glad"

project "CowboyPewPew"
	location "CowboyPewPew"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "pch.h"
    pchsource "CowboyPewPew/src/pch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
    }

    links 
    {
        "GLFW",
        "Glad",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Debug"
        runtime "Release"
        symbols "on"

