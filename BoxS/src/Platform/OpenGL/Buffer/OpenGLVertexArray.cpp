#include "boxspch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace BoxS
{
    OpenGLVertexArray::OpenGLVertexArray()
    {
        glGenVertexArrays(1, &m_RendererID);
        glBindVertexArray(m_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void OpenGLVertexArray::Bind()
    {
        glBindVertexArray(m_RendererID);
    }

    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer> &vb, const VertexBufferLayout& layout)
    {
        glBindVertexArray(m_RendererID);
        vb->Bind();
        
        auto& elements = layout.GetElements();

        for(int i = 0; i < elements.size(); i++)
        {
            auto element = elements[i];

            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, element.Count, element.Type, element.Normalized, layout.GetStride(), (void*)element.Offset);
        }
    }

    void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer> &ib)
    {
        glBindVertexArray(m_RendererID);
        ib->Bind();
    }
}