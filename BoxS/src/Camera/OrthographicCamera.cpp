#include "boxspch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace BoxS
{
    OrthographicCamera::OrthographicCamera(float width, float height, float zoomSize)
        : m_AspectRatio(width / height), m_ZoomSize(zoomSize), m_Rotation(0.0f), m_Position(0.0f)
    {
        float aspectRatio = width / height;

        m_ViewMatrix = glm::mat4(1.0f);
        m_ProjectionMatrix = glm::ortho(-aspectRatio * zoomSize, aspectRatio * zoomSize, -zoomSize, zoomSize);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void OrthographicCamera::RecalculateViewMatrix()
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position)
        * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), { 0.0f, 0.0f, 1.0f });

        m_ViewMatrix = glm::inverse(transform);

        RecalculateViewProjMatrix();
    }

    void OrthographicCamera::RecalculateViewProjMatrix()
    {
        m_ProjectionMatrix = glm::ortho(-m_AspectRatio * m_ZoomSize, m_AspectRatio * m_ZoomSize, -m_ZoomSize, m_ZoomSize);

        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }
}