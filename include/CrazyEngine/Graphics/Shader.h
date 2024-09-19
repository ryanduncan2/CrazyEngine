#ifndef CRAZYENGINE_GRAPHICS_SHADER_H_
#define CRAZYENGINE_GRAPHICS_SHADER_H_

#include "CrazyEngine/Math/Matrix4.h"

namespace CrazyEngine
{
    class Shader
    {
    public:

        static Shader* Create(const char* vertexFilePath, const char* fragmentFilePath);
        static Shader* Create(const char* vertexFilePath, const char* fragmentFilePath, int textureSlots);

        Shader();
        ~Shader();

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetBool(const char* name, bool value) = 0;
        virtual void SetInt(const char* name, int value) = 0;
        virtual void SetIntArray(const char* name, const int count, int* value) = 0;
        virtual void SetFloat(const char* name, float value) = 0;
        virtual void SetFloat3(const char* name, float value1, float value2, float value3) = 0;
        virtual void SetFloatArray(const char* name, const int count, float* value) = 0;
        virtual void SetFloat2Array(const char* name, const int count, CrazyEngine::Vector2* value) = 0;
        virtual void SetFloat3Array(const char* name, const int count, CrazyEngine::Vector3* value) = 0;
        virtual void SetMatrix4(const char* name, const Matrix4& matrix) = 0;
    };
}

#endif