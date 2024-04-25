#include "CrazyEngine/Math/Matrix4.h"

namespace CrazyEngine
{
    const Matrix4 Matrix4::Zero = Matrix4(0, 0, 0, 0, 
                                          0, 0, 0, 0, 
                                          0, 0, 0, 0, 
                                          0, 0, 0, 0);

    const Matrix4 Matrix4::Identity = Matrix4(1, 0, 0, 0, 
                                              0, 1, 0, 0, 
                                              0, 0, 1, 0, 
                                              0, 0, 0, 1);

    Matrix4::Matrix4() noexcept : M11(0), M12(0), M13(0), M14(0), 
                                  M21(0), M22(0), M23(0), M24(0), 
                                  M31(0), M32(0), M33(0), M34(0), 
                                  M41(0), M42(0), M43(0), M44(0) 
    {
    }

    Matrix4::Matrix4(const Matrix4& matrix) : M11(matrix.M11), M12(matrix.M12), M13(matrix.M13), M14(matrix.M14), 
                                              M21(matrix.M21), M22(matrix.M22), M23(matrix.M23), M24(matrix.M24), 
                                              M31(matrix.M31), M32(matrix.M32), M33(matrix.M33), M34(matrix.M34), 
                                              M41(matrix.M41), M42(matrix.M42), M43(matrix.M43), M44(matrix.M44) 
    {
    }

    Matrix4::Matrix4(const float m11, const float m12, const float m13, const float m14,
                     const float m21, const float m22, const float m23, const float m24,
                     const float m31, const float m32, const float m33, const float m34,
                     const float m41, const float m42, const float m43, const float m44) noexcept :
                     M11(m11), M12(m12), M13(m13), M14(m14), 
                     M21(m21), M22(m22), M23(m23), M24(m24), 
                     M31(m31), M32(m32), M33(m33), M34(m34), 
                     M41(m41), M42(m42), M43(m43), M44(m44) 
    {
    }

    Matrix4::Matrix4(const Vector3& rightVector, const Vector3& upVector, const Vector3& forwardVector, const Vector3& translationVector) noexcept
      : M11(rightVector.X), M12(upVector.X), M13(forwardVector.X), M14(translationVector.X),
        M21(rightVector.Y), M22(upVector.Y), M23(forwardVector.Y), M24(translationVector.Y),
        M31(rightVector.Z), M32(upVector.Z), M33(forwardVector.Z), M34(translationVector.Z),
        M41(0),             M42(0),          M43(0),               M44(1)
    {
    }

    float Matrix4::GetDeterminant() const noexcept
    {
        return M11 * (M22 * (M33 * M44 - M34 * M43) - M23 * (M32 * M44 - M34 * M42) + M24 * (M32 * M43 - M33 * M42))
             - M12 * (M21 * (M33 * M44 - M34 * M43) - M23 * (M31 * M44 - M34 * M41) + M24 * (M31 * M43 - M33 * M41))
             + M13 * (M21 * (M32 * M44 - M34 * M42) - M22 * (M31 * M44 - M34 * M41) + M24 * (M31 * M42 - M32 * M41))
             - M14 * (M21 * (M33 * M43 - M32 * M42) - M22 * (M31 * M43 - M32 * M41) + M23 * (M31 * M43 - M33 * M41));
    }

    Matrix4 Matrix4::GetInverse() const
    {
        Matrix4 adjoint = GetAdjoint();
        float determinant = GetDeterminant();

        if (determinant == 0)
        {
            throw std::string("Matrix4<T>::GetInverse(): Matrix4 is not invertible as the determinant is zero.");
        }

        adjoint *= 1 / determinant;

        return adjoint;
    }

    Matrix4 Matrix4::GetMinors() const
    {
        Matrix4 minors;

        // minors.M11 = Matrix3(M22, M23, M24, M32, M33, M34, M42, M43, M44).GetDeterminant();
        // minors.M12 = Matrix3(M21, M23, M24, M31, M33, M34, M41, M43, M33).GetDeterminant();
        // minors.M13 = Matrix3(M21, M22, M24, M31, M32, M34, M41, M42, M44).GetDeterminant();
        // minors.M14 = Matrix3(M21, M22, M23, M31, M32, M33, M41, M42, M43).GetDeterminant();
        // minors.M21 = Matrix3(M12, M13, M14, M32, M33, M34, M42, M43, M44).GetDeterminant();
        // minors.M22 = Matrix3(M11, M13, M14, M31, M33, M34, M41, M43, M44).GetDeterminant();
        // minors.M23 = Matrix3(M11, M12, M14, M31, M32, M34, M41, M42, M44).GetDeterminant();
        // minors.M24 = Matrix3(M11, M12, M13, M31, M32, M33, M41, M42, M43).GetDeterminant();
        // minors.M31 = Matrix3(M12, M13, M14, M22, M23, M24, M42, M43, M44).GetDeterminant();
        // minors.M32 = Matrix3(M11, M13, M14, M21, M23, M24, M41, M43, M44).GetDeterminant();
        // minors.M33 = Matrix3(M11, M12, M14, M21, M22, M24, M41, M42, M44).GetDeterminant();
        // minors.M34 = Matrix3(M11, M12, M13, M21, M22, M23, M41, M42, M43).GetDeterminant();
        // minors.M41 = Matrix3(M12, M13, M14, M22, M23, M24, M32, M33, M34).GetDeterminant();
        // minors.M42 = Matrix3(M11, M13, M14, M21, M23, M24, M31, M33, M34).GetDeterminant();
        // minors.M43 = Matrix3(M11, M12, M14, M21, M22, M24, M31, M32, M34).GetDeterminant();
        // minors.M44 = Matrix3(M11, M12, M13, M21, M22, M23, M31, M32, M33).GetDeterminant();

        return minors;
    }

    Matrix4 Matrix4::GetCofactors() const
    {
        Matrix4 cofactors = GetMinors();

        cofactors.M12 *= -1;
        cofactors.M14 *= -1;
        cofactors.M21 *= -1;
        cofactors.M23 *= -1;
        cofactors.M32 *= -1;
        cofactors.M34 *= -1;
        cofactors.M41 *= -1;
        cofactors.M43 *= -1;

        return cofactors;
    }

    Matrix4 Matrix4::GetAdjoint() const
    {
        Matrix4 adjoint = GetCofactors();
        adjoint.Transpose();

        return adjoint;
    }

    void Matrix4::Transpose() noexcept
    {
        float tempM12 = M12;
        float tempM13 = M13;
        float tempM14 = M14;
        float tempM23 = M23;
        float tempM24 = M24;
        float tempM34 = M34;

        M12 = M21;
        M13 = M31;
        M14 = M41;
        M23 = M32;
        M24 = M42;
        M34 = M43;

        M21 = tempM12;
        M31 = tempM13;
        M41 = tempM14;
        M32 = tempM23;
        M42 = tempM24;
        M43 = tempM34;
    }

    void Matrix4::Add(const Matrix4& matrix) noexcept
    {
        M11 += matrix.M11;
        M12 += matrix.M12;
        M13 += matrix.M13;
        M14 += matrix.M14;
        M21 += matrix.M21;
        M22 += matrix.M22;
        M23 += matrix.M23;
        M24 += matrix.M24;
        M31 += matrix.M31;
        M32 += matrix.M32;
        M33 += matrix.M33;
        M34 += matrix.M34;
        M41 += matrix.M41;
        M42 += matrix.M42;
        M43 += matrix.M43;
        M44 += matrix.M44;
    }

    void Matrix4::Subtract(const Matrix4& matrix) noexcept
    {
        M11 -= matrix.M11;
        M12 -= matrix.M12;
        M13 -= matrix.M13;
        M14 -= matrix.M14;
        M21 -= matrix.M21;
        M22 -= matrix.M22;
        M23 -= matrix.M23;
        M24 -= matrix.M24;
        M31 -= matrix.M31;
        M32 -= matrix.M32;
        M33 -= matrix.M33;
        M34 -= matrix.M34;
        M41 -= matrix.M41;
        M42 -= matrix.M42;
        M43 -= matrix.M43;
        M44 -= matrix.M44;
    }

    void Matrix4::Multiply(const float scalar) noexcept
    {
        M11 *= scalar;
        M12 *= scalar;
        M13 *= scalar;
        M14 *= scalar;
        M21 *= scalar;
        M22 *= scalar;
        M23 *= scalar;
        M24 *= scalar;
        M31 *= scalar;
        M32 *= scalar;
        M33 *= scalar;
        M34 *= scalar;
        M41 *= scalar;
        M42 *= scalar;
        M43 *= scalar;
        M44 *= scalar;
    }

    void Matrix4::Multiply(const Matrix4& matrix) noexcept
    {
        Matrix4 original = Matrix4(*this);

        M11 = original.M11 * matrix.M11 + original.M12 * matrix.M21 + original.M13 * matrix.M31 + original.M14 * matrix.M41;
        M12 = original.M11 * matrix.M12 + original.M12 * matrix.M22 + original.M13 * matrix.M32 + original.M14 * matrix.M42;
        M13 = original.M11 * matrix.M13 + original.M12 * matrix.M23 + original.M13 * matrix.M33 + original.M14 * matrix.M43;
        M14 = original.M11 * matrix.M14 + original.M12 * matrix.M24 + original.M13 * matrix.M34 + original.M14 * matrix.M44;
        M21 = original.M21 * matrix.M11 + original.M22 * matrix.M21 + original.M23 * matrix.M31 + original.M24 * matrix.M41;
        M22 = original.M21 * matrix.M12 + original.M22 * matrix.M22 + original.M23 * matrix.M32 + original.M24 * matrix.M42;
        M23 = original.M21 * matrix.M13 + original.M22 * matrix.M23 + original.M23 * matrix.M33 + original.M24 * matrix.M43;
        M24 = original.M21 * matrix.M14 + original.M22 * matrix.M24 + original.M23 * matrix.M34 + original.M24 * matrix.M44;
        M31 = original.M31 * matrix.M11 + original.M32 * matrix.M21 + original.M33 * matrix.M31 + original.M34 * matrix.M41;
        M32 = original.M31 * matrix.M12 + original.M32 * matrix.M22 + original.M33 * matrix.M32 + original.M34 * matrix.M42;
        M33 = original.M31 * matrix.M13 + original.M32 * matrix.M23 + original.M33 * matrix.M33 + original.M34 * matrix.M43;
        M34 = original.M31 * matrix.M14 + original.M32 * matrix.M24 + original.M33 * matrix.M34 + original.M34 * matrix.M44;
        M41 = original.M41 * matrix.M11 + original.M42 * matrix.M21 + original.M43 * matrix.M31 + original.M44 * matrix.M41;
        M42 = original.M41 * matrix.M12 + original.M42 * matrix.M22 + original.M43 * matrix.M32 + original.M44 * matrix.M42;
        M43 = original.M41 * matrix.M13 + original.M42 * matrix.M23 + original.M43 * matrix.M33 + original.M44 * matrix.M43;
        M44 = original.M41 * matrix.M14 + original.M42 * matrix.M24 + original.M43 * matrix.M34 + original.M44 * matrix.M44;
    }

    void Matrix4::Divide(const float scalar)
    {
        if (scalar == 0)
        {
            throw std::string("Matrix4::Divide: Divisor cannot be zero.");
        }

        M11 /= scalar;
        M12 /= scalar;
        M13 /= scalar;
        M14 /= scalar;
        M21 /= scalar;
        M22 /= scalar;
        M23 /= scalar;
        M24 /= scalar;
        M31 /= scalar;
        M32 /= scalar;
        M33 /= scalar;
        M34 /= scalar;
        M41 /= scalar;
        M42 /= scalar;
        M43 /= scalar;
        M44 /= scalar;
    }

    bool Matrix4::Equals(const Matrix4& matrix) const noexcept
    {
        return M11 == matrix.M11 && M12 == matrix.M12 && M13 == matrix.M13 && M14 == matrix.M14 &&
               M21 == matrix.M21 && M22 == matrix.M22 && M23 == matrix.M23 && M24 == matrix.M24 &&
               M31 == matrix.M31 && M32 == matrix.M32 && M33 == matrix.M33 && M34 == matrix.M34 &&
               M41 == matrix.M41 && M42 == matrix.M42 && M43 == matrix.M43 && M44 == matrix.M44;
    }

    const std::vector<float> Matrix4::ToArray() const noexcept
    {
        return {M11, M21, M31, M41, M12, M22, M32, M42, M13, M23, M33, M43, M14, M24, M34, M44};
    }

    std::string Matrix4::ToString() const noexcept
    {
        return "Matrix4: [" + std::to_string(M11) + " " + std::to_string(M12) + " " + std::to_string(M13) + " " + std::to_string(M14) + "\n "
                            + std::to_string(M21) + " " + std::to_string(M22) + " " + std::to_string(M23) + " " + std::to_string(M24) + "\n "
                            + std::to_string(M31) + " " + std::to_string(M32) + " " + std::to_string(M33) + " " + std::to_string(M34) + "\n "
                            + std::to_string(M41) + " " + std::to_string(M42) + " " + std::to_string(M43) + " " + std::to_string(M44) + "]";
    }

    std::string Matrix4::ToStringInline() const noexcept
    {
        return "Matrix4: [" + std::to_string(M11) + " " + std::to_string(M12) + " " + std::to_string(M13) + " " + std::to_string(M14) + " "
                            + std::to_string(M21) + " " + std::to_string(M22) + " " + std::to_string(M23) + " " + std::to_string(M24) + " "
                            + std::to_string(M31) + " " + std::to_string(M32) + " " + std::to_string(M33) + " " + std::to_string(M34) + " "
                            + std::to_string(M41) + " " + std::to_string(M42) + " " + std::to_string(M43) + " " + std::to_string(M44) + "]";
    }

    Vector3 Matrix4::Transform(const Vector3& vector) const noexcept
    {
        return Vector3(vector.X * M11 + vector.Y * M12 + vector.Z * M13 + M14, 
                       vector.X * M21 + vector.Y * M22 + vector.Z * M23 + M24,
                       vector.X * M31 + vector.Y * M32 + vector.Z * M33 + M34);
    }

    Vector4 Matrix4::Transform(const Vector4& vector) const noexcept
    {
        return Vector4(vector.X * M11 + vector.Y * M12 + vector.Z * M13 + vector.W * M14,
                       vector.X * M21 + vector.Y * M22 + vector.Z * M23 + vector.W * M24,
                       vector.X * M31 + vector.Y * M32 + vector.Z * M33 + vector.W * M34,
                       vector.X * M41 + vector.Y * M42 + vector.Z * M43 + vector.W * M44);
    }

    void Matrix4::SetRight(const Vector3& rightVector) noexcept
    {
        M11 = rightVector.X;
        M21 = rightVector.Y;
        M31 = rightVector.Z;
    }

    void Matrix4::SetUp(const Vector3& upVector) noexcept
    {
        M12 = upVector.X;
        M22 = upVector.Y;
        M32 = upVector.Z;
    }

    void Matrix4::SetForward(const Vector3& forwardVector) noexcept
    {
        M13 = forwardVector.X;
        M23 = forwardVector.Y;
        M33 = forwardVector.Z;
    }

    void Matrix4::SetTranslation(const Vector3& translationVector) noexcept
    {
        M14 = translationVector.X;
        M24 = translationVector.Y;
        M34 = translationVector.Z;
    }

    void Matrix4::SetTranslation(const float translationX, const float translationY, const float translationZ) noexcept
    {
        M14 = translationX;
        M24 = translationY;
        M34 = translationZ;
    }

    void Matrix4::SetScale(const float scale) noexcept
    {
        M11 = scale;
        M22 = scale;
        M33 = scale;
    }

    void Matrix4::SetScale(const float scaleX, const float scaleY, const float scaleZ) noexcept
    {
        M11 = scaleX;
        M22 = scaleY;
        M33 = scaleZ;
    }
    
    Vector3 Matrix4::GetRight() const noexcept
    {
        return Vector3(M11, M21, M31);
    }

    Vector3 Matrix4::GetUp() const noexcept
    {
        return Vector3(M21, M22, M23);
    }

    Vector3 Matrix4::GetForward() const noexcept
    {
        return Vector3(M31, M32, M33);
    }

    Vector3 Matrix4::GetTranslation() const noexcept
    {
        return Vector3(M14, M24, M34);
    }

    Vector3 Matrix4::GetScale() const noexcept
    {
        return Vector3(M11, M22, M33);
    }

    void Matrix4::operator+=(const Matrix4& matrix) noexcept
    {
        Add(matrix);
    }

    void Matrix4::operator-=(const Matrix4& matrix) noexcept
    {
        Subtract(matrix);
    }

    void Matrix4::operator*=(const float scalar) noexcept
    {
        Multiply(scalar);
    }

    void Matrix4::operator*=(const Matrix4& matrix) noexcept
    {
        Multiply(matrix);
    }

    void Matrix4::operator/=(const float scalar)
    {
        Divide(scalar);
    }

    Matrix4 Matrix4::operator-() const noexcept
    {
        Matrix4 matrix = Matrix4(*this);
        matrix.Multiply(-1);
        return matrix;
    }

    float Matrix4::operator[](int index) const
    {
        if (index < 0 || index > 15)
        {
            throw std::string("Matrix4::operator[](int): Index out of bounds of Matrix4.");
        }

        switch (index)
        {
        case 0:
            return M11;
        case 1:
            return M12;
        case 2:
            return M13;
        case 3:
            return M14;
        case 4:
            return M21;
        case 5:
            return M22;
        case 6:
            return M23;
        case 7:
            return M24;
        case 8:
            return M31;
        case 9:
            return M32;
        case 10:
            return M33;
        case 11:
            return M34;
        case 12:
            return M41;
        case 13:
            return M42;
        case 14:
            return M43;
        case 15:
            return M44;
        default:
            return 0.0f;
        }
    }

    float& Matrix4::operator[](int index)
    {
        if (index < 0 || index > 15)
        {
            throw std::string("Matrix4::operator[](int): Index out of bounds of Matrix4.");
        }

        switch (index)
        {
        case 0:
            return M11;
        case 1:
            return M12;
        case 2:
            return M13;
        case 3:
            return M14;
        case 4:
            return M21;
        case 5:
            return M22;
        case 6:
            return M23;
        case 7:
            return M24;
        case 8:
            return M31;
        case 9:
            return M32;
        case 10:
            return M33;
        case 11:
            return M34;
        case 12:
            return M41;
        case 13:
            return M42;
        case 14:
            return M43;
        case 15:
            return M44;
        default:
            return M11;
        }
    }

    Matrix4 Matrix4::CreateBillboard(const Vector3& objectPos, const Vector3& cameraPos, const Vector3& upVector, const Vector3& forwardVector) noexcept
    {
        return Identity;
    }

    Matrix4 Matrix4::CreateConstrainedBillboard(const Vector3& oobjectPos, const Vector3& ocameraPos, const Vector3& oupVector, const Vector3& oforwardVector, const Vector3& orotationAxis) noexcept
    {
        return Identity;
    }

    Matrix4 Matrix4::CreateLookAt(const Vector3& cameraPos, const Vector3& targetPos, const Vector3& upVector)
    {
        return Identity;
    }

    Matrix4 Matrix4::CreateOrthographic(const float width, const float height) noexcept
    {
        return Matrix4(2.0f / width, 0.0f,         0.0f, -1.0f,
                       0.0f,         -2.0f / height, 0.0f, 1.0f,
                       0.0f,         0.0f,         1.0f, 0.0f,
                       0.0f,         0.0f,         0.0f, 1.0f);
    }

    Matrix4 Matrix4::CreateOrthographic(const float width, const float height, const float zNearPlane, const float zFarPlane) noexcept
    {
        return Matrix4(2.0f / width, 0.0f,         0.0f,                            -1.0f,
                       0.0f,         2.0 / height, 0.0f,                            -1.0f,
                       0.0f,         0.0f,         1.0f / (zFarPlane - zNearPlane), 0.0f,
                       0.0f,         0.0f,         0.0f,                            1.0f);
    }

    Matrix4 Matrix4::CreateOrthographicOffCentre(const float left, const float right, const float bottom, const float top, const float zNearPlane, const float zFarPlane) noexcept
    {
        return Matrix4(2.0f / (right - left), 0.0f,                 0.0f,                            -(right + left) / (right - left),
                       0.0f,                  2.0 / (bottom - top), 0.0f,                            -(bottom + top) / (bottom - top),
                       0.0f,                  0.0f,                 1.0f / (zFarPlane - zNearPlane), -zNearPlane / (zFarPlane - zNearPlane),
                       0.0f,                  0.0f,                 0.0f,                            1.0f);
    }

    Matrix4 Matrix4::CreatePerspective(const float width, const float height, const float near, const float far) noexcept
    {
        return Matrix4(near, 0,    0,          0,
                       0,    near, 0,          0,
                       0,    0,    far + near, -far * near,
                       0,    0,    1,          0);
    }

    Matrix4 Matrix4::CreatePerspectiveFOV(const float fov, const float aspectRatio, const float near, const float far) noexcept
    {
        float scale = 1.0f / std::tanf(fov * 0.5f * 3.1415926f / 180.0f);

        return Matrix4(scale * (1.0f / aspectRatio), 0,     0,                            0,
                       0,                            scale, 0,                            0,
                       0,                            0,     far / (far - near),           -1.0f,
                       0,                            0,     (far * near) / (far - near), 0);
    }

    Matrix4 Matrix4::CreatePerspectiveOffCentre(const float left, const float right, const float width, const float height, const float nearPlaneDistnace, const float farPlaneDistance) noexcept
    {
        return Identity;
    }

    Matrix4 Matrix4::CreateWorld(const Vector3& objectPos, const Vector3& upVector, const Vector3& forwardVector) noexcept
    {
        return Identity;
    }

    Matrix4 Matrix4::CreateRotationX(const float angle) noexcept
    {
        return Matrix4(1, 0,                0,                 0,
                       0, std::cosf(angle), -std::sinf(angle), 0,
                       0, std::sinf(angle), std::cosf(angle),  0,
                       0, 0,                0,                 1);
    }

    Matrix4 Matrix4::CreateRotationX(const float angle, const Vector3& position) noexcept
    {
        return Identity;        
    }

    Matrix4 Matrix4::CreateRotationY(const float angle) noexcept
    {
        return Matrix4(std::cosf(angle),  0, std::sinf(angle), 0,
                       0,                 1, 0,                0,
                       -std::sinf(angle), 0, std::cosf(angle), 0,
                       0,                 0, 0,                1);
    }

    Matrix4 Matrix4::CreateRotationY(const float angle, const Vector3& position) noexcept
    {
        return Identity;
    }

    Matrix4 Matrix4::CreateRotationZ(const float angle) noexcept
    {
        return Matrix4(std::cosf(angle), -std::sinf(angle), 0, 0,
                       std::sinf(angle), std::cosf(angle), 0, 0,
                       0, 0, 1, 0,
                       0, 0, 0, 1);
    }

    Matrix4 Matrix4::CreateRotationZ(const float angle, const Vector3& position) noexcept
    {
        return Identity;
    }

    Matrix4 Matrix4::CreateScale(const float scale) noexcept
    {
        return Matrix4::CreateScale(scale, scale, scale);
    }

    Matrix4 Matrix4::CreateScale(const float scaleX, const float scaleY, const float scaleZ) noexcept
    {
        return Matrix4(scaleX, 0, 0, 0,
                       0, scaleY, 0, 0,
                       0, 0, scaleZ, 0,
                       0, 0, 0, 1);
    }

    Matrix4 Matrix4::CreateTranslation(const float translationX, const float translationY, const float translationZ) noexcept
    {
        return Matrix4(1, 0, 0, translationX,
                       0, 1, 0, translationY,
                       0, 0, 1, translationZ,
                       0, 0, 0, 1);
    }

    Matrix4 Matrix4::CreateTranslation(const Vector3& translation) noexcept
    {
        return Identity;
    }

    Matrix4 Matrix4::Lerp(const Matrix4& firstMatrix, const Matrix4& secondMatrix, const float t) noexcept
    {
        return Identity;
    }
}

CrazyEngine::Matrix4 operator+(const CrazyEngine::Matrix4& firstMatrix, const CrazyEngine::Matrix4& secondMatrix) noexcept
{
    CrazyEngine::Matrix4 matrix(firstMatrix);
    matrix.Add(secondMatrix);
    return matrix;
}

CrazyEngine::Matrix4 operator-(const CrazyEngine::Matrix4& firstMatrix, const CrazyEngine::Matrix4& secondMatrix) noexcept
{
    CrazyEngine::Matrix4 matrix(firstMatrix);
    matrix.Subtract(secondMatrix);
    return matrix;
}

CrazyEngine::Matrix4 operator*(const CrazyEngine::Matrix4& matrix, const float scalar) noexcept
{
    CrazyEngine::Matrix4 mat(matrix);
    mat.Multiply(scalar);
    return mat;
}

CrazyEngine::Matrix4 operator*(const CrazyEngine::Matrix4& firstMatrix, const CrazyEngine::Matrix4& secondMatrix) noexcept
{
    CrazyEngine::Matrix4 matrix(firstMatrix);
    matrix.Multiply(secondMatrix);
    return matrix;
}

CrazyEngine::Matrix4 operator/(const CrazyEngine::Matrix4& matrix, const float scalar) noexcept
{
    CrazyEngine::Matrix4 mat(matrix);
    mat.Divide(scalar);
    return mat;
}

bool operator==(const CrazyEngine::Matrix4& firstMatrix, const CrazyEngine::Matrix4& secondMatrix) noexcept
{
    return firstMatrix.M11 == secondMatrix.M11 && firstMatrix.M12 == secondMatrix.M12 &&
           firstMatrix.M13 == secondMatrix.M13 && firstMatrix.M14 == secondMatrix.M14 &&
           firstMatrix.M21 == secondMatrix.M21 && firstMatrix.M22 == secondMatrix.M22 &&
           firstMatrix.M23 == secondMatrix.M23 && firstMatrix.M24 == secondMatrix.M24 &&
           firstMatrix.M31 == secondMatrix.M31 && firstMatrix.M32 == secondMatrix.M32 &&
           firstMatrix.M33 == secondMatrix.M33 && firstMatrix.M34 == secondMatrix.M34 &&
           firstMatrix.M41 == secondMatrix.M41 && firstMatrix.M42 == secondMatrix.M42 &&
           firstMatrix.M43 == secondMatrix.M43 && firstMatrix.M44 == secondMatrix.M44;
}

bool operator!=(const CrazyEngine::Matrix4& firstMatrix, const CrazyEngine::Matrix4& secondMatrix) noexcept
{
    return firstMatrix.M11 != secondMatrix.M11 || firstMatrix.M12 != secondMatrix.M12 ||
           firstMatrix.M13 != secondMatrix.M13 || firstMatrix.M14 != secondMatrix.M14 ||
           firstMatrix.M21 != secondMatrix.M21 || firstMatrix.M22 != secondMatrix.M22 ||
           firstMatrix.M23 != secondMatrix.M23 || firstMatrix.M24 != secondMatrix.M24 ||
           firstMatrix.M31 != secondMatrix.M31 || firstMatrix.M32 != secondMatrix.M32 ||
           firstMatrix.M33 != secondMatrix.M33 || firstMatrix.M34 != secondMatrix.M34 ||
           firstMatrix.M41 != secondMatrix.M41 || firstMatrix.M42 != secondMatrix.M42 ||
           firstMatrix.M43 != secondMatrix.M43 || firstMatrix.M44 != secondMatrix.M44;
}

std::ostream& operator<<(std::ostream& cout, const CrazyEngine::Matrix4& matrix)
{
    cout << matrix.ToStringInline();
    return cout;
}
