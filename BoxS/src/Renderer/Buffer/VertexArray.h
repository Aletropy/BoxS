#pragma once

#include "Buffer.h"
#include "VertexBufferLayout.h"

namespace BoxS
{
    class VertexArray
    {
    public:
        VertexArray() = default;
        virtual ~VertexArray() = default;

        virtual void Bind() = 0;
        virtual void AddVertexBuffer(const Ref<VertexBuffer>& vb, const VertexBufferLayout& layout) = 0;
        virtual void SetIndexBuffer(const Ref<IndexBuffer>& ib) = 0;

        static Ref<VertexArray> Create();
    };
}