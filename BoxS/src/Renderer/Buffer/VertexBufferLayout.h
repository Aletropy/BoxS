#pragma once

#include "Core/Base.h"
#include "Core/Logger.h"

#include <stdint.h>
#include <vector>

#define GL_FLOAT 0x1406

namespace BoxS
{
    struct VertexBufferElement
    {
        uint32_t Type;
        uint32_t Count;
        uint32_t Offset;
        bool Normalized;
    };

    class VertexBufferLayout
    {
    public:
        template<typename T>
        void Push(uint32_t count)
        {
            Logger::Error("Unrecognized type to push into vertex buffer layout.");
        }

        template<>
        inline void Push<float>(uint32_t count)
        {
            m_Elements.push_back({ GL_FLOAT, count, m_Stride, false });
            m_Stride += count * sizeof(float);
        }

        const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }
        const uint32_t GetStride() const { return m_Stride; }

    private:
        uint32_t m_Stride = 0;
        std::vector<VertexBufferElement> m_Elements;
    };
}