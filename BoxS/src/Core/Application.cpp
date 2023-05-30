#include "Application.h"

#include "Renderer/Renderer.h"
#include "Renderer/RendererCommand.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Platform/Linux/LinuxInput.h" //TODO: Remove direct platform to application

namespace BoxS
{
    Application* Application::s_Instance = nullptr;

    Input* Input::s_Instance = new LinuxInput(); // TODO: REMOVE THIS FAST

    Application::Application(uint32_t width, uint32_t height, const char *title)
        : m_Width(width), m_Height(height)
    {
        s_Instance = this;

        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);

        glfwMakeContextCurrent(m_Window);

        glfwSwapInterval(1);

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
        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (event.Handled) 
				break;
			(*it)->OnEvent(event);
		}
    }

    void Application::Run()
    {
        while(!glfwWindowShouldClose(m_Window))
        {
            RendererCommand::ClearScreen(0.0f, 0.0f, 0.0f);
            
            for(Layer* layer : m_LayerStack)
                layer->OnUpdate();

            glfwSwapBuffers(m_Window);
            glfwPollEvents();
        }
    }
    
}