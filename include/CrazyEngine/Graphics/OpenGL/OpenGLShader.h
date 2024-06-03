#ifndef CRAZYENGINE_GRAPHICS_OPENGL_OPENGLSHADER_H_
#define CRAZYENGINE_GRAPHICS_OPENGL_OPENGLSHADER_H_

#include "CrazyEngine/Graphics/Shader.h"

namespace CrazyEngine
{
    class OpenGLShader : public Shader
    {
    private:

        std::uint32_t m_ShaderID;

    public:

        OpenGLShader(const char* vertexFilePath, const char* fragmentFilePath, int textureSlots = 0);
        ~OpenGLShader();

        void Bind() const override;
        void Unbind() const override;

        void SetBool(const char* name, bool value) override;
        void SetInt(const char* name, int value) override;
        void SetIntArray(const char* name, const int count, int* value) override;
        void SetFloat(const char* name, float value) override;
        void SetFloat3(const char* name, float value1, float value2, float value3) override;
        void SetFloatArray(const char* name, const int count, float* value) override;
        void SetFloat3Array(const char* name, const int count, CrazyEngine::Vector3* value) override;
        void SetFloat2Array(const char* name, const int count, CrazyEngine::Vector2* value) override;
        void SetMatrix4(const char* name, const Matrix4& matrix) override;
    };
}

#endif