#pragma once

#include "Camera.h"

namespace BoxS
{
    class OrthographicCamera : public Camera
    {
    public:
        OrthographicCamera(float width, float height, float zoomSize);

        virtual void SetPosition(const glm::vec3& position) override { m_Position = position; RecalculateViewMatrix(); }
        void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }
        void SetZoomSize(float zoomSize) { m_ZoomSize = zoomSize; RecalculateViewProjMatrix(); }

        virtual inline const glm::mat4& GetViewProjectionMatrix() const override { return m_ViewProjectionMatrix; }

    private:
        void RecalculateViewMatrix();
        void RecalculateViewProjMatrix();

    private:
        glm::vec3 m_Position;
        float m_Rotation;
        float m_ZoomSize;
        float m_AspectRatio;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewProjectionMatrix;
    };
}