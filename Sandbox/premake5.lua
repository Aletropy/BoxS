project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    staticruntime "On"

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
        "%{IncludeDirs.BoxS}",
        "%{IncludeDirs.glm}",
        "%{IncludeDirs.GLFW}",
        "%{IncludeDirs.imgui}"
    }

    links
    {
        "BoxS",
        "GLFW",
        "imgui",
        "glad"
    }
    
    filter "system:linux"
        links
        {
            "X11"
        }

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        runtime "Release"
        optimize "On"