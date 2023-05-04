#include "boxspch.h"
#include "RendererCommand.h"

#include "Renderer.h"

#include <glad/glad.h>

namespace BoxS
{
    void RendererCommand::ClearScreen(float r, float g, float b, float a)
    {
        if(!Renderer::IsInitialized())
        {
            Logger::Error("Cannot clear screen with renderer off. Please initialize renderer first.");
            return;
        }

        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RendererCommand::DrawIndexed(const Ref<VertexArray>& va, uint32_t count)
    {
        va->Bind();
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }

    void RendererCommand::Viewport(int width, int height)
    {
        glViewport(0, 0, width, height);
    }
    
    void RendererCommand::SetWireframed(bool active)
    {
        if(active)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}