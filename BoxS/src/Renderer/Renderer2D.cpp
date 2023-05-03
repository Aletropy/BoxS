#include "boxspch.h"
#include "Renderer2D.h"

#include "Buffer/Buffer.h"
#include "Buffer/VertexArray.h"
#include "Shader.h"

#include "RendererCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace BoxS
{
    static const glm::vec4 QuadVertexPositions[] =
    {
        { -1.0f, -1.0f, 0.0f, 1.0f },
        { -1.0f, 1.0f, 0.0f, 1.0f },
        { 1.0f, 1.0f, 0.0f, 1.0f },
        { 1.0f, -1.0f, 0.0f, 1.0f }
    };

    struct Vertex
    {
        glm::vec4 Position;
        glm::vec4 Color;
    };

    struct Renderer2DData
    {
        const static uint32_t MaxQuads = 10000;
        const static uint32_t MaxVertices = MaxQuads * 4;
        const static uint32_t MaxIndices = MaxQuads * 6;

        Vertex* QuadVertexBufferPtr;
        Vertex* QuadVertexBufferBase;

        Ref<VertexArray> QuadVa;
        Ref<VertexBuffer> QuadVb;
        Ref<IndexBuffer> QuadIb;

        Ref<Shader> QuadShader;

        uint32_t QuadIndexCount = 0;
    };

    static Renderer2DData s_Data;
    void Renderer2D::Init()
    {
        s_Data.QuadVa = VertexArray::Create();

        s_Data.QuadVb = VertexBuffer::Create(s_Data.MaxVertices * sizeof(Vertex));

        s_Data.QuadVertexBufferBase = new Vertex[s_Data.MaxVertices];

        VertexBufferLayout layout;

        layout.Push<float>(4);
        layout.Push<float>(4);

        s_Data.QuadVa->AddVertexBuffer(s_Data.QuadVb, layout);

        uint32_t* indices = new uint32_t[s_Data.MaxIndices];
        uint32_t offset = 0;
        for(uint32_t i = 0; i < s_Data.MaxIndices; i += 6)
        {
            indices[i + 0] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;
            indices[i + 3] = offset + 2;
            indices[i + 4] = offset + 3;
            indices[i + 5] = offset + 0;

            offset += 4;
        }

        s_Data.QuadIb = IndexBuffer::Create((void*)indices, s_Data.MaxIndices * sizeof(uint32_t));

        s_Data.QuadVa->SetIndexBuffer(s_Data.QuadIb);

        s_Data.QuadShader = Shader::Create("assets/shaders/Default.vert", "assets/shaders/Default.frag");
    }

    void Renderer2D::Begin()
    {
        BeginBatch();
    }

    void Renderer2D::End()
    {
        Flush();
    }

    void Renderer2D::BeginBatch()
    {
        s_Data.QuadIndexCount = 0;
        s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
    }

    void Renderer2D::NextBatch()
    {
        Flush();
        BeginBatch();
    }

    void Renderer2D::Flush()
    {
        uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase);
        s_Data.QuadVb->SetData(s_Data.QuadVertexBufferBase, dataSize);

        s_Data.QuadShader->Bind();

        RendererCommand::DrawIndexed(s_Data.QuadVa, s_Data.QuadIndexCount);
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec3 &scale, float rotation, const glm::vec4 &color)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
        * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
        * glm::scale(glm::mat4(1.0f), scale);

        if(s_Data.QuadIndexCount >= s_Data.MaxIndices)
            NextBatch();

        for(uint32_t i = 0; i < 4; i++)
        {
            s_Data.QuadVertexBufferPtr->Position = transform * QuadVertexPositions[i];
            s_Data.QuadVertexBufferPtr->Color = color;

            s_Data.QuadVertexBufferPtr++;
        }

        s_Data.QuadIndexCount += 6;
    }
}