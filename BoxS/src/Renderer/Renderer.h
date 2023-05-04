#pragma once

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

        static const inline bool IsInitialized() { return m_IsInitialized; }

    private:
        static bool m_IsInitialized;
    };
}
