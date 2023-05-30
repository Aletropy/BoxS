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
IncludeDirs["imgui"] = "%{wks.location}/BoxS/vendor/imgui"

include "BoxS/vendor/GLFW"
include "BoxS/vendor/glad"
include "BoxS/vendor/imgui"

include "BoxS"
include "Sandbox"