#include "BoxS.h"

#include <GLFW/glfw3.h>

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Sandbox App", nullptr, nullptr);

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    BoxS::Renderer::Init();
    BoxS::Renderer2D::Init();

    Ref<BoxS::OrthographicCamera> camera = CreateRef<BoxS::OrthographicCamera>(800.0f, 600.0f, 5.0f);

    float x = 0.0f;

    while(!glfwWindowShouldClose(window))
    {
        BoxS::RendererCommand::ClearScreen(0.8f, 0.35f, 0.45f);

        camera->SetPosition({ x, 0.0f, 0.0f });

        BoxS::Renderer2D::Begin(camera);
        BoxS::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, 0.0f);
        BoxS::Renderer2D::End();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}