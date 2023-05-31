#pragma once

#include <stdint.h>

namespace BoxS
{
    enum class InitMode
    {
        Only2D,
        Only3D,
        Both
    };

    class Renderer
    {
    public:
        Renderer() = delete;
        Renderer(const Renderer&&) = delete;

        static bool Init(InitMode mode = InitMode::Both);
        static void OnWindowResize(uint32_t width, uint32_t height);

        static const inline bool IsInitialized() { return m_IsInitialized; }

    private:
        static bool m_IsInitialized;
    };
}
