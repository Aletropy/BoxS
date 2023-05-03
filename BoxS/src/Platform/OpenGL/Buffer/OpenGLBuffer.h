#pragma once

#include "Renderer/Buffer/Buffer.h"

namespace BoxS
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(void* data, uint32_t size);
        OpenGLVertexBuffer(uint32_t size);
        virtual ~OpenGLVertexBuffer() override;

        virtual void Bind() override;
        virtual void Unbind() override;

        virtual void SetData(void* data, uint32_t size) override;

    private:
        uint32_t m_RendererID;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(void* data, uint32_t size);
        virtual ~OpenGLIndexBuffer() override;

        virtual void Bind() override;
        virtual void Unbind() override;

    private:
        uint32_t m_RendererID;
    };
}
