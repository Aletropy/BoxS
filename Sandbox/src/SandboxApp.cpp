#include "BoxS.h"

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

static float zoomSize = 5.0f;
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

    Ref<BoxS::PerspectiveCamera> camera = CreateRef<BoxS::PerspectiveCamera>(800.0f, 600.0f, 60.0f);

    camera->SetPosition({ 0.0f, 0.0f, -10.0f });

    int ticksCount = 0;

    while(!glfwWindowShouldClose(window))
    {
        BoxS::RendererCommand::ClearScreen(0.3f, 0.3f, 0.3f);

        BoxS::Renderer3D::Begin(camera);

        BoxS::RendererCommand::SetWireframed(true);
        BoxS::Renderer3D::DrawCube({ 3.0f, 0.0f, 0.0f }, glm::vec3(1.0f), glm::vec3(0.0f));

        BoxS::Renderer3D::NextBatch(); // Jumps to the next batch so the cube above can be rendered in wireframe

        BoxS::RendererCommand::SetWireframed(false);
        BoxS::Renderer3D::DrawCube({ -3.0f, 0.0f, 0.0f }, glm::vec3(1.0f), glm::vec3(0.0f));

        BoxS::Renderer3D::End();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}