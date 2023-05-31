#include "GameLayer.h"

#include <glm/glm.hpp>
#include <imgui.h>

void GameLayer::OnAttach()
{
    m_Camera = CreateRef<BoxS::PerspectiveCamera>(1600.0f, 900.0f, 70.0f);

    m_Camera->SetPosition({ 0.0f, 0.0f, -10.0f });
}

void GameLayer::OnUpdate(BoxS::Timestep ts)
{
    OnRender();
}

void GameLayer::OnEvent(BoxS::Event& event)
{
    if(event.GetEventType() == BoxS::EventType::WindowResize)
    {
        BoxS::WindowResizeEvent& e = (BoxS::WindowResizeEvent&)event;

        m_Camera->SetViewport((float)e.GetWidth(), (float)e.GetHeight());
    }
}


void GameLayer::OnImGuiRender()
{
    ImGui::Begin("Square");

    ImGui::ColorEdit4("Color", &color.r);
    ImGui::DragFloat3("Position", &position.r, 0.2f);
    ImGui::DragFloat3("Scale", &scale.r, 0.2f);
    ImGui::DragFloat3("Rotation", &rotation.r, 0.2f);
    ImGui::Checkbox("Wireframed", &m_Wireframed);

    uint32_t textureID = m_Framebuffer->GetColorAttachmentID();
    ImGui::Image((void*)textureID, ImVec2{ 1600.0f, 900.0f });

    ImGui::End();
}

void GameLayer::OnRender()
{
    BoxS::Renderer3D::Begin(m_Camera);

    BoxS::RendererCommand::SetWireframed(m_Wireframed);
    BoxS::Renderer3D::DrawCube(position, scale, rotation, color);

    BoxS::Renderer3D::End();
}