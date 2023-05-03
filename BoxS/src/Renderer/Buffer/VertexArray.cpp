#include "boxspch.h"
#include "VertexArray.h"

#include "Platform/OpenGL/Buffer/OpenGLVertexArray.h"

namespace BoxS
{
    Ref<VertexArray> VertexArray::Create()
    {
        return CreateRef<OpenGLVertexArray>();
    }
}