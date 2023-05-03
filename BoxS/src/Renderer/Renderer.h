#pragma once

namespace BoxS
{
    class Renderer
    {
    public:
        Renderer() = delete;
        Renderer(const Renderer&&) = delete;

        static bool Init();

        static const inline bool IsInitialized() { return m_IsInitialized; }

    private:
        static bool m_IsInitialized;
    };
}
