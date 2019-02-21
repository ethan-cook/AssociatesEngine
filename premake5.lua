workspace "Associates"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Associates/ThirdParty/GLFW/include/"
IncludeDir["glad"] = "Associates/ThirdParty/glad/include/"
IncludeDir["imgui"] = "Associates/ThirdParty/imgui/"

include "Associates/ThirdParty/GLFW/"
include "Associates/ThirdParty/glad/"
include "Associates/ThirdParty/imgui"

project "Associates"
    location "Associates"
    kind "SharedLib"
    language "C++"
    
    targetdir ("Bin/" .. outputdir .. "/%{prj.name}")
    objdir ("Bin-Int/" .. outputdir .. "/%{prj.name}")

    pchheader "Assoc_pch.h"
    pchsource "Associates/Source/Assoc_pch.cpp"

    files
    {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp"  
    }

    includedirs
    {
		"%{prj.name}/Source",
       "%{prj.name}/ThirdParty/spdlog/include",
       "%{IncludeDir.GLFW}",
       "%{IncludeDir.glad}",
       "%{IncludeDir.imgui}"
    }

    links
    {
        "GLFW",
        "glad",
        "ImGUI",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "ASSOC_PLATFORM_WINDOWS",
            "ASSOC_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../Bin/" .. outputdir .. "/TechGame")
        }

    filter "configurations:Debug"
        defines "ASSOC_DEBUG"
		buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "ASSOC_RELEASE"
		buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "ASSOC_DIST"
		buildoptions "/MD"
        optimize "On"

project "TechGame"
    location "TechGame"
    kind "ConsoleApp"
    language "C++"
    
    targetdir ("Bin/" .. outputdir .. "/%{prj.name}")
    objdir ("Bin-Int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp"  
    }

    includedirs
    {
       "Associates/ThirdParty/spdlog/include",
       "Associates/Source"
    }

    links
    {
        "Associates"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "ASSOC_PLATFORM_WINDOWS",
        }

    filter "configurations:Debug"
        defines "ASSOC_DEBUG"
		buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "ASSOC_RELEASE"
		buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "ASSOC_DIST"
		buildoptions "/MD"
        optimize "On"
