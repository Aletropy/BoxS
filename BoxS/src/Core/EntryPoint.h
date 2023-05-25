#pragma once
#include "Application.h"

namespace BoxS
{
    extern Application* CreateApplication();
}

int main()
{
    auto app = BoxS::CreateApplication();
    app->Run();
    delete app;
    return 0;
}