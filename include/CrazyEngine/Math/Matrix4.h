#ifndef CRAZYENGINE_MATH_MATRIX4_H_
#define CRAZYENGINE_MATH_MATRIX4_H_

#include "CrazyEngine/Math/Vector3.h"
#include "CrazyEngine/Math/Vector4.h"

namespace CrazyEngine
{
    class Matrix4
    {
    public:
        // float M11, M12, M13, M14,
        //       M21, M22, M23, M24,
        //       M31, M32, M33, M34,
        //       M41, M42, M43, M44;

        float M11, M21, M31, M41,
              M12, M22, M32, M42,
              M13, M23, M33, M43,
              M14, M24, M34, M44;
        
        static const Matrix4 Zero;
        static const Matrix4 Identity;

        Matrix4() noexcept;
        Matrix4(const Matrix4& matrix);
        Matrix4(const float m11, const float m12, const float m13, const float m14,
                const float m21, const float m22, const float m23, const float m24,
                const float m31, const float m32, const float m33, const float m34,
                const float m41, const float m42, const float m43, const float m44) noexcept;
        Matrix4(const Vector3& rightVector, const Vector3& upVector, const Vector3& forwardVector, const Vector3& translationVector) noexcept;

        float GetDeterminant() const noexcept;
        Matrix4 GetInverse() const;
        Matrix4 GetMinors() const;
        Matrix4 GetCofactors() const;
        Matrix4 GetAdjoint() const;

        void Transpose() noexcept;
        void Add(const Matrix4& matrix) noexcept;
        void Subtract(const Matrix4& matrix) noexcept;
        void Multiply(const float scalar) noexcept;
        void Multiply(const Matrix4& matrix) noexcept;
        void Divide(const float scalar);
        bool Equals(const Matrix4& matrix) const noexcept;
        const std::vector<float> ToArray() const noexcept;
        std::string ToString() const noexcept;
        std::string ToStringInline() const noexcept;

        Vector3 Transform(const Vector3& vector) const noexcept;
        Vector4 Transform(const Vector4& vector) const noexcept;

        void SetRight(const Vector3& rightVector) noexcept;
        void SetUp(const Vector3& upVector) noexcept;
        void SetForward(const Vector3& forwardVector) noexcept;
        void SetTranslation(const Vector3& translationVector) noexcept;
        void SetTranslation(const float translationX, const float translationY, const float translationZ) noexcept;
        void SetScale(const float scale) noexcept;
        void SetScale(const float scaleX, const float scaleY, const float scaleZ) noexcept;
        
        Vector3 GetRight() const noexcept;
        Vector3 GetUp() const noexcept;
        Vector3 GetForward() const noexcept;
        Vector3 GetTranslation() const noexcept;
        Vector3 GetScale() const noexcept;

        void operator+=(const Matrix4& matrix) noexcept;
        void operator-=(const Matrix4& matrix) noexcept;
        void operator*=(const float scalar) noexcept;
        void operator*=(const Matrix4& matrix) noexcept;
        void operator/=(const float scalar);
        Matrix4 operator-() const noexcept;

        float operator[](int index) const;
        float& operator[](int index);

        static Matrix4 CreateBillboard(const Vector3& objectPos, const Vector3& cameraPos, const Vector3& upVector, const Vector3& forwardVector) noexcept;
        static Matrix4 CreateConstrainedBillboard(const Vector3& oobjectPos, const Vector3& ocameraPos, const Vector3& oupVector, const Vector3& oforwardVector, const Vector3& orotationAxis) noexcept;
        static Matrix4 CreateLookAt(const Vector3& cameraPos, const Vector3& targetPos, const Vector3& upVector);
        static Matrix4 CreateOrthographic(const float width, const float height) noexcept;
        static Matrix4 CreateOrthographic(const float width, const float height, const float zNearPlane, const float zFarPlane) noexcept;
        static Matrix4 CreateOrthographicOffCentre(const float left, const float right, const float bottom, const float top, const float zNearPlane, const float zFarPlane) noexcept;
        static Matrix4 CreatePerspective(const float width, const float height, const float near, const float far) noexcept;
        static Matrix4 CreatePerspectiveFOV(const float fov, const float aspectRatio, const float near, const float far) noexcept;
        static Matrix4 CreatePerspectiveOffCentre(const float left, const float right, const float width, const float height, const float nearPlaneDistance, const float farPlaneDistance) noexcept;
        static Matrix4 CreateWorld(const Vector3& objectPos, const Vector3& upVector, const Vector3& forwardVector) noexcept;
        static Matrix4 CreateRotationX(const float angle) noexcept;
        static Matrix4 CreateRotationX(const float angle, const Vector3& position) noexcept;
        static Matrix4 CreateRotationY(const float angle) noexcept;
        static Matrix4 CreateRotationY(const float angle, const Vector3& position) noexcept;
        static Matrix4 CreateRotationZ(const float angle) noexcept;
        static Matrix4 CreateRotationZ(const float angle, const Vector3& position) noexcept;
        static Matrix4 CreateScale(const float scale) noexcept;
        static Matrix4 CreateScale(const float scaleX, const float scaleY, const float scaleZ) noexcept;
        static Matrix4 CreateTranslation(const float translationX, const float translationY, const float translationZ) noexcept;
        static Matrix4 CreateTranslation(const Vector3& translation) noexcept;
        static Matrix4 Lerp(const Matrix4& firstMatrix, const Matrix4& secondMatrix, const float t) noexcept;
    };
}

CrazyEngine::Matrix4 operator+(const CrazyEngine::Matrix4& firstMatrix, const CrazyEngine::Matrix4& secondMatrix) noexcept;
CrazyEngine::Matrix4 operator-(const CrazyEngine::Matrix4& firstMatrix, const CrazyEngine::Matrix4& secondMatrix) noexcept;
CrazyEngine::Matrix4 operator*(const CrazyEngine::Matrix4& matrix, const float scalar) noexcept;
CrazyEngine::Matrix4 operator*(const CrazyEngine::Matrix4& firstMatrix, const CrazyEngine::Matrix4& secondMatrix) noexcept;
CrazyEngine::Matrix4 operator/(const CrazyEngine::Matrix4& matrix, const float scalar) noexcept;
bool operator==(const CrazyEngine::Matrix4& firstMatrix, const CrazyEngine::Matrix4& secondMatrix) noexcept;
bool operator!=(const CrazyEngine::Matrix4& firstMatrix, const CrazyEngine::Matrix4& secondMatrix) noexcept;
std::ostream& operator<<(std::ostream& cout, const CrazyEngine::Matrix4& matrix);

#endif