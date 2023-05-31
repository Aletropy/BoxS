#include "boxspch.h"
#include "Framebuffer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace BoxS
{
    Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
    {
        return CreateRef<OpenGLFramebuffer>(spec);
    }
}