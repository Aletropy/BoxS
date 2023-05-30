#include "boxspch.h"
#include "LinuxInput.h"

#include "Core/Application.h"
#include "GLFW/glfw3.h"

namespace BoxS
{
    bool LinuxInput::IsKeyPressedImpl(int keycode)
    {
        auto window = Application::Get().GetWindow();
        auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool LinuxInput::IsMouseButtonPressedImpl(int button)
    {
        auto window = Application::Get().GetWindow();
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    float LinuxInput::GetMouseXImpl()
    {
        auto[x, y] = GetMousePositionImpl();

        return x;
    }

    float LinuxInput::GetMouseYImpl()
    {
        auto [x, y] = GetMousePositionImpl();
        return y;
    }

    std::pair<float, float> LinuxInput::GetMousePositionImpl()
    {
        auto window = Application::Get().GetWindow();
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        return { (float)xpos, (float)ypos };
    }
}