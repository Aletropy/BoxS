#include "boxspch.h"
#include "Renderer3D.h"

#include "Buffer/Buffer.h"
#include "Buffer/VertexArray.h"
#include "Shader.h"

#include "RendererCommand.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace BoxS
{
    Ref<Camera> Renderer3D::m_CurrentCamera = nullptr;

    static const glm::vec4 CubeVertexPositions[] =
    {
        { -1.0f, -1.0f, 1.0f, 1.0f }, // 0 Front L-B
        { -1.0f, 1.0f, 1.0f, 1.0f }, // 1 Front L-U
        { 1.0f, 1.0f, 1.0f, 1.0f }, // 2 Front R-U
        { 1.0f, -1.0f, 1.0f, 1.0f }, // 3 Front R-B

        { -1.0f, -1.0f, -1.0f, 1.0f }, // 4 Back L-B
        { -1.0f, 1.0f, -1.0f, 1.0f }, // 5 Back L-U
        { 1.0f, 1.0f, -1.0f, 1.0f }, // 6 Back R-U
        { 1.0f, -1.0f, -1.0f, 1.0f } // 7 Back R-B
    };

    

    struct Vertex
    {
        glm::vec4 Position;
        glm::vec4 Color;
    };

    struct Renderer3DData
    {
        const static uint32_t MaxCubes = 1000;
        const static uint32_t MaxVertices = MaxCubes * 8;
        const static uint32_t MaxIndices = MaxCubes * 36;

        Vertex* CubeVertexBufferPtr;
        Vertex* CubeVertexBufferBase;

        Ref<VertexArray> CubeVa;
        Ref<VertexBuffer> CubeVb;
        Ref<IndexBuffer> CubeIb;

        Ref<Shader> CubeShader;

        uint32_t CubeIndexCount = 0;
    };

    static Renderer3DData s_Data;
    void Renderer3D::Init()
    {
        s_Data.CubeVa = VertexArray::Create();

        s_Data.CubeVb = VertexBuffer::Create(s_Data.MaxVertices * sizeof(Vertex));

        s_Data.CubeVertexBufferBase = new Vertex[s_Data.MaxVertices];

        VertexBufferLayout layout;

        layout.Push<float>(4);
        layout.Push<float>(4);

        s_Data.CubeVa->AddVertexBuffer(s_Data.CubeVb, layout);

        uint32_t* indices = new uint32_t[s_Data.MaxIndices];
        uint32_t offset = 0;
        for(uint32_t i = 0; i < s_Data.MaxIndices; i += 36)
        {
            indices[i + 0] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;
            indices[i + 3] = offset + 2;
            indices[i + 4] = offset + 3;
            indices[i + 5] = offset + 0;

            indices[i + 6] = offset + 3;
            indices[i + 7] = offset + 2;
            indices[i + 8] = offset + 6;
            indices[i + 9] = offset + 6;
            indices[i + 10] = offset + 7;
            indices[i + 11] = offset + 3;

            indices[i + 12] = offset + 4;
            indices[i + 13] = offset + 5;
            indices[i + 14] = offset + 6;
            indices[i + 15] = offset + 6;
            indices[i + 16] = offset + 7;
            indices[i + 17] = offset + 4;

            indices[i + 18] = offset + 4;
            indices[i + 19] = offset + 5;
            indices[i + 20] = offset + 1;
            indices[i + 21] = offset + 1;
            indices[i + 22] = offset + 0;
            indices[i + 23] = offset + 4;

            indices[i + 24] = offset + 2;
            indices[i + 25] = offset + 1;
            indices[i + 26] = offset + 5;
            indices[i + 27] = offset + 5;
            indices[i + 28] = offset + 6;
            indices[i + 29] = offset + 2;

            indices[i + 30] = offset + 0;
            indices[i + 31] = offset + 4;
            indices[i + 32] = offset + 7;
            indices[i + 33] = offset + 7;
            indices[i + 34] = offset + 3;
            indices[i + 35] = offset + 0;

            offset += 8;
        }

        s_Data.CubeIb = IndexBuffer::Create((void*)indices, s_Data.MaxIndices * sizeof(uint32_t));

        s_Data.CubeVa->SetIndexBuffer(s_Data.CubeIb);

        s_Data.CubeShader = Shader::Create("assets/shaders/Default.vert", "assets/shaders/Default.frag");
    }

    void Renderer3D::Begin(const Ref<Camera>& camera)
    {
        m_CurrentCamera = camera;
        BeginBatch();
    }

    void Renderer3D::End()
    {
        Flush();
    }

    void Renderer3D::BeginBatch()
    {
        s_Data.CubeIndexCount = 0;
        s_Data.CubeVertexBufferPtr = s_Data.CubeVertexBufferBase;
    }

    void Renderer3D::NextBatch()
    {
        Flush();
        BeginBatch();
    }

    void Renderer3D::Flush()
    {
        uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.CubeVertexBufferPtr - (uint8_t*)s_Data.CubeVertexBufferBase);
        s_Data.CubeVb->SetData(s_Data.CubeVertexBufferBase, dataSize);

        glm::mat4 viewProj = m_CurrentCamera->GetViewProjectionMatrix();

        s_Data.CubeShader->Bind();
        s_Data.CubeShader->SetMat4("u_ViewProjMatrix", glm::value_ptr(viewProj));

        RendererCommand::DrawIndexed(s_Data.CubeVa, s_Data.CubeIndexCount);
    }

    void Renderer3D::DrawCube(const glm::vec3 &position, const glm::vec3 &scale, const glm::vec3& rotation, const glm::vec4 &color)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
        * glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), { 1.0f, 0.0f, 0.0f })
        * glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), { 0.0f, 1.0f, 0.0f })
        * glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), { 0.0f, 0.0f, 1.0f })
        * glm::scale(glm::mat4(1.0f), scale);

        if(s_Data.CubeIndexCount >= s_Data.MaxIndices)
            NextBatch();

        for(uint32_t i = 0; i < 8; i++)
        {
            s_Data.CubeVertexBufferPtr->Position = transform * CubeVertexPositions[i];
            s_Data.CubeVertexBufferPtr->Color = color;

            s_Data.CubeVertexBufferPtr++;
        }

        s_Data.CubeIndexCount += 36;
    }
}