#pragma once

#include <stdint.h>
#include "Events/Event.h"
#include "Layers/LayerStack.h"
#include "ImGui/ImGuiLayer.h"

#include "Events/ApplicationEvent.h"

#include "Window.h"

namespace BoxS
{
    class Application
    {
    public:
        Application(uint32_t width, uint32_t height, const char* title);
        virtual ~Application();
        
        void Run();
        void OnEvent(Event& event);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        inline static Application& Get() { return *s_Instance; }

        inline Window& GetWindow() { return *m_Window; }

    private:
        bool OnWindowClose(WindowCloseEvent& e);

    private:
        Window* m_Window;
        bool m_IsRunning = true;
        LayerStack m_LayerStack;
        ImGuiLayer* m_ImGuiLayer;
    private:
        static Application* s_Instance;
    };

    Application* CreateApplication();
}