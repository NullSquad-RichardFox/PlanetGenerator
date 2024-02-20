workspace "PlanetGenerator"
    architecture "x64"
    
    configurations 
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}/%{cfg.architecture}"

group "Dependencies"
include "ThirdParty/Glad/Glad.lua"
include "ThirdParty/GLFW/GLFW.lua"
include "ThirdParty/msdf-atlas-gen/msdf-atlas-gen.lua"
include "ThirdParty/ImGui/ImGui.lua"
group ""

group "Generator"
project "Generator"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir("Binaries/" .. outputdir)
    objdir("Intermediate/" .. outputdir)

    pchheader("epch.h")
    pchsource("Source/epch.cpp")

    files
    {
        "Source/**.cpp",
        "Source/**.h"
    }

    includedirs
    {
        "Source",
        "ThirdParty/Glad/include",
        "ThirdParty/GLFW/include",
        "ThirdParty/spdlog/include",
        "ThirdParty/stb_image/include",
        "ThirdParty/glm/include",
        "ThirdParty/msdf-atlas-gen",
        "ThirdParty/msdf-atlas-gen/msdfgen",
        "ThirdParty/ImGui"
    }

    links 
    {
        "Glad",
        "GLFW",
        "msdf-atlas-gen",
        "ImGui"
    }

group ""