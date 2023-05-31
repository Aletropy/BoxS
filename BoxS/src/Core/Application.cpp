#include "boxspch.h"
#include "Application.h"

#include "Renderer/Renderer.h"
#include "Renderer/RendererCommand.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "Platform/Linux/LinuxInput.h" //TODO: Remove direct platform to application
#include "Platform/Linux/LinuxWindow.h"

namespace BoxS
{

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;

    Input* Input::s_Instance = new LinuxInput(); // TODO: REMOVE THIS FAST

    Application::Application(uint32_t width, uint32_t height, const char *title)
    {
        s_Instance = this;

        m_Window = new LinuxWindow({ title, width, height });

        m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
    
        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        Renderer::Init();
    }

    Application::~Application()
    {

    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* overlay)
    {
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

    void Application::OnEvent(Event &event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (event.Handled) 
				break;
			(*it)->OnEvent(event);
		}
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_IsRunning = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent& e)
    {
        if(e.GetWidth() == 0 || e.GetHeight() == 0)
        {
            m_IsMinimized = true;
            return false;
        }

        m_IsMinimized = false;

        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

        return false;
    }

    void Application::Run()
    {
        while(m_IsRunning)
        {
            float time = (float)glfwGetTime();
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            RendererCommand::ClearScreen(0.0f, 0.0f, 0.0f);
            
            if(!m_IsMinimized)
            {
                for(Layer* layer : m_LayerStack)
                    layer->OnUpdate(timestep);
            }

            m_ImGuiLayer->Begin();
            for(Layer* layer : m_LayerStack)
                layer->OnImGuiRender();
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }
    
}