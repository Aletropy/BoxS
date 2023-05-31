#pragma once

#include <BoxS.h>
#include <glm/glm.hpp>

class GameLayer : public BoxS::Layer
{
public:
    GameLayer()
        : BoxS::Layer("GameLayer") {}

    void OnAttach() override;
    void OnUpdate(BoxS::Timestep ts) override;
    void OnEvent(BoxS::Event& event) override;
    void OnImGuiRender() override;

private:
    void OnRender();

private:
    glm::vec3 position = { 0.0f, 0.0f, 0.0f };
    glm::vec3 scale = { 1.0f, 1.0f, 1.0f };
    glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };
    glm::vec4 color = { 0.0f, 0.0f, 1.0f, 0.8f };

    bool m_Wireframed = false;

    Ref<BoxS::PerspectiveCamera> m_Camera;
};