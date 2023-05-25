#pragma once

#include <stdint.h>
#include "Events/Event.h"
#include "Layers/LayerStack.h"

struct GLFWwindow;

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

        uint32_t GetWindowWidth() const { return m_Width; }
        uint32_t GetWindowHeight() const { return m_Height; }

    private:
        GLFWwindow* m_Window;
        uint32_t m_Width, m_Height;
        LayerStack m_LayerStack;
    };

    Application* CreateApplication();
}