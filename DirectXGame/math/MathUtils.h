#pragma once
#include <cmath>
#include <Vector2.h>
#include <Vector3.h>
#include <Vector4.h>
#include <Matrix4x4.h>

namespace Math {
	constexpr float Pi = 3.141592653589793f;
	constexpr float TwoPi = Pi * 2.0f;
	constexpr float HalfPi = Pi * 0.5f;
}

inline Vector2 operator+(const Vector2& v);
inline Vector2 operator-(const Vector2& v);
inline Vector2 operator+(const Vector2& v1, const Vector2& v2);
inline Vector2 operator-(const Vector2& v1, const Vector2& v2);
inline Vector2 operator*(const Vector2& v, float s);
inline Vector2 operator*(float s, const Vector2& v);
inline Vector2& operator+=(Vector2& v1, const Vector2& v2);
inline Vector2& operator-=(Vector2& v1, const Vector2& v2);
inline Vector2& operator*=(Vector2& v, float s);
inline bool operator==(const Vector2& v1, const Vector2& v2);
inline bool operator!=(const Vector2& v1, const Vector2& v2);
inline float Dot(const Vector2& v1, const Vector2& v2);
inline float Cross(const Vector2& v1, const Vector2& v2);
inline float LengthSquare(const Vector2& v);
inline float Length(const Vector2& v);
inline Vector2 Normalize(const Vector2& v);

inline Vector3 operator+(const Vector3& v);
inline Vector3 operator-(const Vector3& v);
inline Vector3 operator+(const Vector3& v1, const Vector3& v2);
inline Vector3 operator-(const Vector3& v1, const Vector3& v2);
inline Vector3 operator*(const Vector3& v, float s);
inline Vector3 operator*(float s, const Vector3& v);
inline Vector3& operator+=(Vector3& v1, const Vector3& v2);
inline Vector3& operator-=(Vector3& v1, const Vector3& v2);
inline Vector3& operator*=(Vector3& v, float s);
inline bool operator==(const Vector3& v1, const Vector3& v2);
inline bool operator!=(const Vector3& v1, const Vector3& v2);
inline float Dot(const Vector3& v1, const Vector3& v2);
inline Vector3 Cross(const Vector3& v1, const Vector3& v2);
inline float LengthSquare(const Vector3& v);
inline float Length(const Vector3& v);
inline Vector3 Normalize(const Vector3& v);

inline Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2);
inline Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2);
inline Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2);
inline Matrix4x4 operator*(const Matrix4x4& m, float s);
inline Matrix4x4 operator*(float s, const Matrix4x4& m);
inline Matrix4x4 operator*=(Matrix4x4& m1, const Matrix4x4& m2);
inline Matrix4x4 Transpose(const Matrix4x4& m);
float Determinant(const Matrix4x4& m);
Matrix4x4 Adjugate(const Matrix4x4& m);
inline Matrix4x4 Inverse(const Matrix4x4& m);
inline Matrix4x4 MakeIdentityMatrix();
inline Matrix4x4 MakeScaleMatrix(const Vector3& scale);
inline Matrix4x4 MakeRotateXMatrix(float rad);
inline Matrix4x4 MakeRotateYMatrix(float rad);
inline Matrix4x4 MakeRotateZMatrix(float rad);
inline Matrix4x4 MakeTranslateMatrix(const Vector3& trans);
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& trans);

Vector3 Transform(const Vector3& v, const Matrix4x4& m);
inline Vector3 operator*(const Vector3& v, const Matrix4x4& m);
