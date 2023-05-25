#include "BoxS.h"
#include "Core/EntryPoint.h"

#include "GameLayer.h"

class SandboxApp : public BoxS::Application
{
public:
    SandboxApp()
        : BoxS::Application(800, 600, "Sandbox")
    {
        PushLayer(new GameLayer());
    }
};

BoxS::Application* BoxS::CreateApplication()
{
    return new SandboxApp;
}