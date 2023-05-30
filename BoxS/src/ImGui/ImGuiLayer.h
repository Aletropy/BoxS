#pragma once

#include "Layers/Layer.h"

namespace BoxS
{
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach();
        void OnDetach();

        void Begin();
        void End();
    private:
        float m_Time = 0;
    };
}