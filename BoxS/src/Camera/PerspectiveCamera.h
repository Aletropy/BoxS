#pragma once

#include "Camera.h"

namespace BoxS
{
    class PerspectiveCamera : public Camera
    {
    public:
        PerspectiveCamera(float width, float height, float fov);

        virtual void SetPosition(const glm::vec3& position) override { m_Position = position; RecalculateViewMatrix(); }
        void SetRotation(const glm::vec3& rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }
        void SetFov(float fov) { m_Fov = fov; RecalculateViewProjMatrix(); }
        void SetViewport(float width, float height) { m_AspectRatio = width/height; RecalculateViewProjMatrix(); }

        virtual inline const glm::mat4& GetViewProjectionMatrix() const override { return m_ViewProjectionMatrix; }

    private:
        void RecalculateViewMatrix();
        void RecalculateViewProjMatrix();

    private:
        glm::vec3 m_Position;
        glm::vec3 m_Rotation;
        float m_Fov;
        float m_AspectRatio;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewProjectionMatrix;
    };
}