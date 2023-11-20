-- premake5.lua
workspace "PistolOnlyMod"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "PistolOnlyMod"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "PistolOnlyMod"
    location "%{prj.name}"
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"
    targetname "PistolOnly"
    targetextension ".asi"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp"
    }

    includedirs {
        "%{prj.name}/Source",
        "ThirdParty/ScriptHookV/inc"
    }

    libdirs { "ThirdParty/ScriptHookV/lib" }
    links { "ScriptHookV" }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        runtime "Release"
        optimize "On"
        symbols "On"
