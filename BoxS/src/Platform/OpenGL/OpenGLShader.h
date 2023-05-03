#pragma once

#include "Renderer/Shader.h"

namespace BoxS
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& vertexPath, const std::string& fragmentPath);
        virtual ~OpenGLShader() override;

        virtual void Bind() override;

    private:
        uint32_t CompileShader(uint32_t type, const char* source);

    private:
        uint32_t m_RendererID;
    };
}