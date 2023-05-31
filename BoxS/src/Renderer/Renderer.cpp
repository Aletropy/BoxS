#include "boxspch.h"
#include "Renderer.h"

#include <glad/glad.h>
#include "Renderer2D.h"
#include "Renderer3D.h"

#include "RendererCommand.h"

namespace BoxS
{
    bool Renderer::m_IsInitialized = false;

    bool Renderer::Init(InitMode mode)
    {
        if(m_IsInitialized)
        {
            Logger::Warn("Renderer is already initialized!");
            return false;
        }

        if(!gladLoadGL())
        {
            Logger::Error("Cannot initialize renderer.");
            return false;
        }

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CW);

        if(mode == InitMode::Only2D)
            Renderer2D::Init();
        else if(mode == InitMode::Only3D)
            Renderer3D::Init();
        else
        {
            Renderer2D::Init();
            Renderer3D::Init();
        }

        Logger::Info("Renderer initialized.");
        m_IsInitialized = true;

        return true;
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height)
    {
        RendererCommand::Viewport((int)width, (int)height);
    }
}