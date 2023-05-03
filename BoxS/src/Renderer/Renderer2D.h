#pragma once

#include <stdint.h>

#include "Camera/Camera.h"
#include <glm/glm.hpp>

namespace BoxS
{
    class Renderer2D
    {
    public:
        Renderer2D() = delete;
        Renderer2D(const Renderer2D&&) = delete;

        static void Init();

        static void Begin(const Ref<Camera>& camera);
        static void End();

        static void DrawQuad(const glm::vec3& position, const glm::vec3& scale, float rotation, const glm::vec4& color = glm::vec4(1.0f));

    private:
        static void NextBatch();
        static void BeginBatch();
        static void Flush();

    private:
        static Ref<Camera> m_CurrentCamera;
    };
}