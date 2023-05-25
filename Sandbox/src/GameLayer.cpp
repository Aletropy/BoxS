#include "GameLayer.h"

#include <glm/glm.hpp>

void GameLayer::OnAttach()
{
    m_Camera = CreateRef<BoxS::OrthographicCamera>(800.0f, 600.0f, 5.0f);
}

void GameLayer::OnUpdate()
{

    x += xIncrement;
    x2 += x2Increment;

    if(x < -5.0f || x > 5.0f)
        xIncrement = -xIncrement;

    if(x2 > 5.0f || x2 < -5.0f)
        x2Increment = -x2Increment;

    OnRender();
}

glm::vec4 color1 = { 0.0f, 0.0f, 1.0f, 0.8f };
glm::vec4 color2 = { 1.0f, 0.0f, 0.0f, 0.8f };

void GameLayer::OnRender()
{
    BoxS::Renderer2D::Begin(m_Camera);

    BoxS::Renderer2D::DrawQuad({ x2, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, 0.0f, color2);

    BoxS::Renderer2D::DrawQuad({ x, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, 0.0f, color1);

    BoxS::Renderer2D::End();
}