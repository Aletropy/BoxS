#pragma once

#include <stdint.h>

#include "Camera/Camera.h"

#include "Core/Base.h"

#include <glm/glm.hpp>

namespace BoxS
{
    class Renderer3D
    {
    public:
        Renderer3D() = delete;
        Renderer3D(const Renderer3D&&) = delete;

        static void Init();

        static void Begin(const Ref<Camera>& camera);
        static void End();

        static void DrawCube(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation, const glm::vec4& color = glm::vec4(1.0f));
        
        static void NextBatch();

    private:
        static void BeginBatch();
        static void Flush();

    private:
        static Ref<Camera> m_CurrentCamera;
    };
}