#include "boxspch.h"
#include "PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace BoxS
{
    PerspectiveCamera::PerspectiveCamera(float width, float height, float fov)
        : m_Fov(fov), m_Position(1.0f), m_Rotation(0.0f), m_AspectRatio(width / height)
    {
        float aspect = width / height;

        m_ViewMatrix = glm::mat4(1.0f);
        m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspect, 0.1f, 1000.0f);

        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void PerspectiveCamera::RecalculateViewMatrix()
    {
        glm::vec3 pos = { -m_Position.x, -m_Position.y, m_Position.z };
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos);

        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.x), { 1.0f, 0.0f, 0.0f })
        * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.y), { 0.0f, 1.0f, 0.0f })
        * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.z), { 0.0f, 0.0f, 1.0f });

        m_ViewMatrix = rotation * transform;

        RecalculateViewProjMatrix();
    }

    void PerspectiveCamera::RecalculateViewProjMatrix()
    {
        m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), m_AspectRatio, 0.1f, 1000.0f);

        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }
}