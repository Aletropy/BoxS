#pragma once

#include "Core/Base.h"
#include <stdint.h>

namespace BoxS
{
    class VertexBuffer
    {
    public:
        VertexBuffer() = default;
        virtual ~VertexBuffer() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void SetData(void* data, uint32_t size) = 0;

        static Ref<VertexBuffer> Create(void* data, uint32_t size);
        static Ref<VertexBuffer> Create(uint32_t size);
    };

    class IndexBuffer
    {
    public:
        IndexBuffer() = default;
        virtual ~IndexBuffer() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        static Ref<IndexBuffer> Create(void* data, uint32_t size);
    };
}