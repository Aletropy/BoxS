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


    while(!glfwWindowShouldClose(window))
    {
        BoxS::RendererCommand::ClearScreen(0.3f, 0.3f, 0.3f);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}