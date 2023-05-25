#pragma once

#include <BoxS.h>

class GameLayer : public BoxS::Layer
{
public:
    GameLayer()
        : BoxS::Layer("GameLayer") {}

    virtual void OnAttach() override;
    virtual void OnUpdate() override;

private:
    void OnRender();

private:
    float xIncrement = -0.05f;
    float x = 0.0f;
    float x2Increment = 0.05f;
    float x2 = 0.0f;
    Ref<BoxS::OrthographicCamera> m_Camera;
};