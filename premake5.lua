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


Outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "CowboyPewPew"
	location "CowboyPewPew"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

    targetdir ("bin/" .. Outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. Outputdir .. "/%{prj.name}")

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
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Debug"
        runtime "Release"
        symbols "on"

