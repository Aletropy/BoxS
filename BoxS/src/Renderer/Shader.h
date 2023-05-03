#pragma once

#include <string>
#include "Core/Base.h"

namespace BoxS
{
    class Shader
    {
    public:
        Shader() = default;
        virtual ~Shader() = default;

        virtual void Bind() = 0;

        virtual void SetMat4(const std::string& name, float* values) = 0;

        static Ref<Shader> Create(const std::string& vertexPath, const std::string& fragmentPath);
    protected:
        static std::string ShaderSource(const std::string& path);
    };
}