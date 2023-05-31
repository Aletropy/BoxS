#include "boxspch.h"
#include "LinuxWindow.h"

#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

namespace BoxS
{
    static bool s_GLFWInitialized = false;

    Window* Window::Create(const WindowProps& props)
    {
        return new LinuxWindow(props);
    }

    LinuxWindow::LinuxWindow(const WindowProps& props)
    {
        Init(props);
    }

    LinuxWindow::~LinuxWindow()
    {
        Shutdown();
    }

    void LinuxWindow::Init(const WindowProps& props)
    {
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        Logger::Info("Creating window %s (%d, %d)", props.Title.c_str(), props.Width, props.Height);

        if(!s_GLFWInitialized)
            glfwInit();

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

        m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* w, int width, int height)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(w);

            WindowResizeEvent event(width, height);
            data.Width = width;
            data.Height = height;
            data.EventCallback(event);
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* w)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(w);

            WindowCloseEvent event;
            data.EventCallback(event);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* w, int key, int scancode, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(w);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* w, int button, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(w);

            switch(action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* w, double xOffset, double yOffset)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(w);

            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* w, double xPos, double yPos)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(w);

            MouseMovedEvent event((float)xPos, (float)yPos);
            data.EventCallback(event);
        });
    }

    void LinuxWindow::Shutdown()
    {
        glfwDestroyWindow(m_Window);
    }

    void LinuxWindow::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void LinuxWindow::SetVSync(bool enabled)
    {
        if(enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_Data.VSync = enabled;
    }

    bool LinuxWindow::IsVSync()
    {
        return m_Data.VSync;
    }
}