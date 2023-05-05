#pragma once

#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Buffer/Buffer.h"
#include "Renderer/Buffer/VertexBufferLayout.h"

#include <glm/glm.hpp>

namespace BoxS
{
    struct Vertex
    {
        glm::vec4 Position;
        glm::vec4 Color;
    };

    class Mesh
    {
    public:
        Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
        Mesh();

        void RecalculateMesh();

        const Ref<VertexArray>& GetVertexArray() const { return m_VertexArray; }

        inline uint32_t GetIndexCount() const { return m_IndicesCount; }
    protected:
        std::vector<Vertex> m_Vertices;
        std::vector<uint32_t> m_Indices;
        uint32_t m_IndicesCount = 0;
        Ref<VertexArray> m_VertexArray;
        Ref<VertexBuffer> m_VertexBuffer;
        Ref<IndexBuffer> m_IndexBuffer;
        VertexBufferLayout m_BufferLayout;
    };
}