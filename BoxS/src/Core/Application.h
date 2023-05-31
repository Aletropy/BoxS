#pragma once

#include <stdint.h>
#include "Events/Event.h"
#include "Layers/LayerStack.h"
#include "ImGui/ImGuiLayer.h"

#include "Events/ApplicationEvent.h"

#include "Timestep.h"

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
        bool OnWindowResize(WindowResizeEvent& e);

    private:
        Window* m_Window;
        bool m_IsRunning = true;
        bool m_IsMinimized = false;

        LayerStack m_LayerStack;
        ImGuiLayer* m_ImGuiLayer;

        Timestep m_Timestep;
        float m_LastFrameTime = 0.0f;
    private:
        static Application* s_Instance;
    };

    Application* CreateApplication();
}