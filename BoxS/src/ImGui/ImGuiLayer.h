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
        void OnUpdate();
    private:
        float m_Time = 0;
    };
}