#pragma once

#include "Core/Base.h"

namespace BoxS
{
    struct FramebufferSpecification
    {
        uint32_t Width, Height;
        uint32_t Samples = 1;
        bool SwapChainTarget = false;
    };

    class Framebuffer
    {
    public:        
        virtual const FramebufferSpecification& GetSpec() const = 0;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual uint32_t GetColorAttachmentID() const = 0;

        static Ref<Framebuffer> Create(const FramebufferSpecification& spec);
    };
}