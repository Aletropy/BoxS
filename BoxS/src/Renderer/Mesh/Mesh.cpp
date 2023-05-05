#include "boxspch.h"
#include "Mesh.h"

#include <glad/glad.h>

namespace BoxS
{
    Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
    {
        m_VertexArray = VertexArray::Create();

        m_VertexBuffer = VertexBuffer::Create((void*)vertices.data(), vertices.size() * sizeof(Vertex));

        m_BufferLayout = VertexBufferLayout();

        m_BufferLayout.Push<float>(4);
        m_BufferLayout.Push<float>(4);

        m_IndexBuffer = IndexBuffer::Create((void*)indices.data(), indices.size() * sizeof(uint32_t), indices.size());

        m_VertexArray->AddVertexBuffer(m_VertexBuffer, m_BufferLayout);
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);
    }

    Mesh::Mesh()
        : m_Vertices(), m_Indices() { }

    void Mesh::RecalculateMesh()
    {
        m_VertexArray = VertexArray::Create();

        m_VertexBuffer = VertexBuffer::Create((void*)m_Vertices.data(), m_Vertices.size() * sizeof(Vertex));

        m_BufferLayout = VertexBufferLayout();

        m_BufferLayout.Push<float>(4);
        m_BufferLayout.Push<float>(4);

        m_IndexBuffer = IndexBuffer::Create((void*)m_Indices.data(), m_Indices.size() * sizeof(uint32_t), m_Indices.size());

        m_VertexArray->AddVertexBuffer(m_VertexBuffer, m_BufferLayout);
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);
    }
}