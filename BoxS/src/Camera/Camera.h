#pragma once

#include <glm/glm.hpp>

namespace BoxS
{
    class Camera
    {
    public:
        Camera() = default;

        virtual void SetPosition(const glm::vec3& position) = 0;
        virtual inline const glm::mat4& GetViewProjectionMatrix() const = 0;
    };
}