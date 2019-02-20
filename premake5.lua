workspace "Associates"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

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
       "%{prj.name}/ThirdParty/spdlog/include"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "ASSOC_PLATFORM_WINDOWS",
            "ASSOC_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../Bin/" .. outputdir .. "/TechGame")
        }

    filter "configurations:Debug"
        defines "ASSOC_DEBUG"
        symbols "On"

    filter "configurations:Debug"
        defines "ASSOC_RELEASE"
        optimize "On"

    filter "configurations:Debug"
        defines "ASSOC_DIST"
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
        symbols "On"

    filter "configurations:Debug"
        defines "ASSOC_RELEASE"
        optimize "On"

    filter "configurations:Debug"
        defines "ASSOC_DIST"
        optimize "On"
