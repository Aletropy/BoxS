#include "boxspch.h"
#include "Buffer.h"

#include "Platform/OpenGL/Buffer/OpenGLBuffer.h"

namespace BoxS
{
    Ref<VertexBuffer> VertexBuffer::Create(void* data, uint32_t size)
    {
        return CreateRef<OpenGLVertexBuffer>(data, size);
    }

    Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
    {
        return CreateRef<OpenGLVertexBuffer>(size);
    }

    Ref<IndexBuffer> IndexBuffer::Create(void* data, uint32_t size)
    {
        return CreateRef<OpenGLIndexBuffer>(data, size);
    }
}