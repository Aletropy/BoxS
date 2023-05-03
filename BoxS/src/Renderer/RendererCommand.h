#pragma once

#include "Renderer/Buffer/VertexArray.h"

namespace BoxS
{
    class RendererCommand
    {
    public:
        RendererCommand() = delete;
        RendererCommand(const RendererCommand&&) = delete;

        static void ClearScreen(float r, float g, float b, float a = 1.0f);
        static void DrawIndexed(const Ref<VertexArray>& va, uint32_t count);
    };
}