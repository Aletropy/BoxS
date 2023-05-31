#pragma once

#include "Renderer/Framebuffer.h"

namespace BoxS
{
    class OpenGLFramebuffer : public Framebuffer
    {
    public:
        OpenGLFramebuffer(const FramebufferSpecification& spec);
        virtual ~OpenGLFramebuffer();

        void Invalidade();

        void Bind() override;
        void Unbind() override;

        const FramebufferSpecification& GetSpec() const override { return m_Specification; }

        uint32_t GetColorAttachmentID() const override { return m_ColorAttachment; }

    private:
        uint32_t m_RendererID;
        uint32_t m_ColorAttachment, m_DepthAttachment;
        FramebufferSpecification m_Specification;
    };
}