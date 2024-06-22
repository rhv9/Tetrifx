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
IncludeDir["Spdlog"] = "CowboyPewPew/vendor/spdlog/include"
IncludeDir["Glad"] = "CowboyPewPew/vendor/Glad/include"
IncludeDir["ImGui"] = "CowboyPewPew/vendor/imgui/include"
IncludeDir["Glm"] = "CowboyPewPew/vendor/glm"
IncludeDir["Emscripten"] = "CowboyPewPew/vendor/emscripten/system/include/emscripten"

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
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.inl",
        "%{prj.name}/vendor/glm/**.hpp",
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.Spdlog}",
        "%{IncludeDir.Emscripten}",
        "%{IncludeDir.Glm}",
        "CowboyPewPew/include",
    }

    links 
    {
        "GLFW",
        "Glad",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"
        defines { "PLATFORM_WINDOWS", "GLM_ENABLE_EXPERIMENTAL" }

    filter "configurations:Debug"
        runtime "Debug"
        defines "DEBUG"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        symbols "on"

