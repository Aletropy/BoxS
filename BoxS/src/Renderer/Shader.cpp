#include "boxspch.h"
#include "Shader.h"

#include <glad/glad.h>

#include "Platform/OpenGL/OpenGLShader.h"

namespace BoxS
{
    Ref<Shader> Shader::Create(const std::string& vertexPath, const std::string& fragmentPath)
    {
        return CreateRef<OpenGLShader>(vertexPath, fragmentPath);
    }

    std::string Shader::ShaderSource(const std::string& path)
    {
        std::ifstream stream(path);

        if(!stream.is_open())
        {
            Logger::Error("Cannot open file: %s", path.c_str());
            return "";
        }

        std::stringstream ss;
        std::string line;

        while(getline(stream, line))
        {
            ss << line << "\n";
        }

        return ss.str();
    }
}