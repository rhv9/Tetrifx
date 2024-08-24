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
IncludeDir["ImGui"] = "CowboyPewPew/vendor/imgui/"
IncludeDir["Glm"] = "CowboyPewPew/vendor/glm"
IncludeDir["Emscripten"] = "CowboyPewPew/vendor/emscripten/system/include/emscripten"
IncludeDir["Stb_image"] = "CowboyPewPew/vendor/stb_image"
IncludeDir["Entt"] = "CowboyPewPew/vendor/entt/include"


include "CowboyPewPew/vendor/glfw_premake5.lua"
include "CowboyPewPew/vendor/Glad"
include "CowboyPewPew/vendor/imgui_premake5.lua"

project "CowboyPewPew"
	location "CowboyPewPew"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "pch.h"
    --pchsource "CowboyPewPew/src/pch.cpp"

    --buildoptions { "NoPCH" }

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.inl",
        "%{prj.name}/vendor/glm/**.hpp",
        "%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",

        --"%{prj.name}/vendor/imgui/backends/imgui_impl_opengl3.cpp",
		--"%{prj.name}/vendor/imgui/backends/imgui_impl_glfw.cpp",1
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.Spdlog}",
        "%{IncludeDir.Emscripten}",
        "%{IncludeDir.Glm}",
        "%{IncludeDir.Stb_image}",
        "%{IncludeDir.Entt}",
        "%{IncludeDir.ImGui}",

        "CowboyPewPew/include",
    }

    links 
    {
        "GLFW",
        "Glad",
        "ImGui",
        "GL"
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

