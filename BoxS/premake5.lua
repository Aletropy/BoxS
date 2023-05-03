project "BoxS"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "On"

    pchheader "src/boxspch.h"
    pchsource "src/boxspch.cpp"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "src/**.cpp",
        "src/**.h"
    }

    includedirs
    {
        "src/",
        "%{IncludeDirs.glad}",
        "%{IncludeDirs.glm}"
    }

    links
    {
        "glad"
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        runtime "Release"
        optimize "On"