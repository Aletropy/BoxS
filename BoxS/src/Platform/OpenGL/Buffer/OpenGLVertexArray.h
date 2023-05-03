#pragma once

#include "Renderer/Buffer/VertexArray.h"

namespace BoxS
{
    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray() override;

        virtual void Bind() override;
        virtual void AddVertexBuffer(const Ref<VertexBuffer>& vb, const VertexBufferLayout& layout) override;
        virtual void SetIndexBuffer(const Ref<IndexBuffer>& ib) override;
        
    private:
        uint32_t m_RendererID;
    };
}