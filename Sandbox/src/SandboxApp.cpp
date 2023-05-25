#include "BoxS.h"
#include "Core/EntryPoint.h"

class TestLayer : public BoxS::Layer
{
public:
    TestLayer()
        : Layer("TestLayer") { }

    virtual void OnAttach() override
    {
        m_Camera = CreateRef<BoxS::OrthographicCamera>(800, 600, 5.0f);
    }

    virtual void OnUpdate() override
    {
        BoxS::Renderer2D::Begin(m_Camera);
        BoxS::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, 0.0f);
        BoxS::Renderer2D::End();
    }

private:
    Ref<BoxS::OrthographicCamera> m_Camera;
};

class SandboxApp : public BoxS::Application
{
public:
    SandboxApp()
        : BoxS::Application(800, 600, "Sandbox App")
    {
        PushLayer(new TestLayer());
    }

    ~SandboxApp()
    {

    }
};

BoxS::Application* BoxS::CreateApplication()
{
    return new SandboxApp();
}