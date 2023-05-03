workspace "BoxS"
    architecture "x64"
    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDirs = {}
IncludeDirs["BoxS"] = "%{wks.location}/BoxS/src/"
IncludeDirs["glad"] = "%{wks.location}/BoxS/vendor/glad/include"
IncludeDirs["GLFW"] = "%{wks.location}/BoxS/vendor/GLFW/include"
IncludeDirs["glm"] = "%{wks.location}/BoxS/vendor/glm"

include "BoxS/vendor/GLFW"
include "BoxS/vendor/glad"

include "BoxS"
include "Sandbox"