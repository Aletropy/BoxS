#include "boxspch.h"
#include "Renderer.h"

#include <glad/glad.h>

namespace BoxS
{
    bool Renderer::m_IsInitialized = false;

    bool Renderer::Init()
    {
        if(m_IsInitialized)
        {
            Logger::Warn("Renderer is already initialized!");
            return false;
        }

        if(gladLoadGL())
        {
            Logger::Info("Renderer initialized.");
            m_IsInitialized = true;
            return true;
        }

        Logger::Error("Cannot initialize renderer.");
        return false;
    }
}