#include "boxspch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

namespace BoxS
{
    OpenGLShader::OpenGLShader(const std::string& vertexPath, const std::string& fragmentPath)
    {
        m_RendererID = glCreateProgram();

        uint32_t vs = CompileShader(GL_VERTEX_SHADER, ShaderSource(vertexPath).c_str());
        uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, ShaderSource(fragmentPath).c_str());

        glAttachShader(m_RendererID, vs);
        glAttachShader(m_RendererID, fs);

        glLinkProgram(m_RendererID);

        int success;
        glGetProgramiv(m_RendererID, GL_LINK_STATUS, &success);
        if(!success)
        {
            char message[1024];
            int lenght;
            glGetProgramInfoLog(m_RendererID, 1024, &lenght, message);
            Logger::Error("Error while linking program: %s", message);
        }

        glDeleteShader(vs);
        glDeleteShader(fs);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_RendererID);
    }

    void OpenGLShader::Bind()
    {
        glUseProgram(m_RendererID);
    }

    void OpenGLShader::SetMat4(const std::string& name, float* values)
    {
        int location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, values);
    }

    uint32_t OpenGLShader::CompileShader(uint32_t type, const char* source)
    {
        uint32_t id = glCreateShader(type);
        glShaderSource(id, 1, &source, nullptr);
        glCompileShader(id);

        int success;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            char message[1024];
            int lenght;
            glGetShaderInfoLog(id, 1024, &lenght, message);
            Logger::Error("Cannot compile shader: %s", message);
        }

        return id;
    }
}