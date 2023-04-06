#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4x4.h"
#include <math.h>

namespace Math {
	constexpr float Pi = 3.14159265359f;
	constexpr float TwoPi = 2.0f * Pi;
	constexpr float PiDiv2 = Pi / 2.0f;
}; // namespace Math

inline float Sin(float x) { return sinf(x); }
inline float Cos(float x) { return cosf(x); }
inline float Tan(float x) { return tanf(x); }
inline float Asin(float x) { return asinf(x); }
inline float Acos(float x) { return acosf(x); }
inline float Atan(float x) { return atanf(x); }
inline float Atan2(float x, float y) { return atan2f(y, x); }
inline float ToRad(float deg) { return deg * Math::Pi / 180.0f; }
inline float ToDeg(float rad) { return rad * 180.0f / Math::Pi; }
inline float Abs(float x) { return fabsf(x); }
inline float Sqrt(float x) { return sqrtf(x); }
inline float Fmod(float x, float y) { return fmodf(x, y); }
inline float Pow(float x, float y) { return powf(x, y); } 

template<typename T> inline T Max(const T& x, const T& y) { return x < y ? y : x; }
template<typename T> inline T Min(const T& x, const T& y) { return x < y ? x : y; }
template<typename T>
inline T Clamp(const T& x, const T& lower = (T)0, const T& upper = (T)1) {
	return Min(upper, Max(lower, x));
}
template<typename T> 
inline T Swap(T& x, T& y) { 
	T tmp = x;
	x = y;
	y = tmp;
}

inline Vector2 operator+(const Vector2& a, const Vector2& b) { return {a.x + b.x, a.y + b.y}; }
inline Vector2 operator-(const Vector2& a, const Vector2& b) { return {a.x - b.x, a.y - b.y}; }
inline Vector2 operator*(const Vector2& a, const Vector2& b) { return {a.x * b.x, a.y * b.y}; }
inline Vector2 operator*(const Vector2& a, float s) { return {a.x * s, a.y * s}; }
inline Vector2 operator*(float s, const Vector2& a) { return {s * a.x, s * a.y}; }
inline Vector2 operator/(const Vector2& a, float s) { return {a.x / s, a.y / s}; }

inline Vector3 operator+(const Vector3& a, const Vector3& b) { return {a.x + b.x, a.y + b.y, a.z + b.z}; }
inline Vector3 operator-(const Vector3& a, const Vector3& b) { return {a.x - b.x, a.y - b.y, a.z - b.z}; }
inline Vector3 operator*(const Vector3& a, const Vector3& b) { return {a.x * b.x, a.y * b.y, a.z * a.z}; }
inline Vector3 operator*(const Vector3& a, float s) { return {a.x * s, a.y * s, a.z * s}; }
inline Vector3 operator*(float s, const Vector3& a) { return {s * a.x, s * a.y, s * a.z}; }
inline Vector3 operator/(const Vector3& a, float s) { return {a.x / s, a.y / s, a.z / s}; }

inline Vector4 operator+(const Vector4& a, const Vector4& b) { return {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w}; }
inline Vector4 operator-(const Vector4& a, const Vector4& b) { return {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w}; }
inline Vector4 operator*(const Vector4& a, float s) { return {a.x * s, a.y * s, a.z * s, a.w * s}; }
inline Vector4 operator*(float s, const Vector4& a) { return {s * a.x, s * a.y, s * a.z, s * a.w}; }
inline Vector4 operator/(const Vector4& a, float s) { return {a.x / s, a.y / s, a.z / s, a.w * s}; }

inline float Dot(const Vector2& a, const Vector2& b) { return a.x * b.x + a.y * b.y; }
inline float Dot(const Vector3& a, const Vector3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
inline float Dot(const Vector4& a, const Vector4& b) { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }

inline float LengthSquare(const Vector2& a) { return Dot(a, a); }
inline float LengthSquare(const Vector3& a) { return Dot(a, a); }
inline float LengthSquare(const Vector4& a) { return Dot(a, a); }

inline float Length(const Vector2& a) { return Sqrt(LengthSquare(a)); }
inline float Length(const Vector3& a) { return Sqrt(LengthSquare(a)); }
inline float Length(const Vector4& a) { return Sqrt(LengthSquare(a)); }

inline Vector2 Normalize(const Vector2& a) { return a / Length(a); }
inline Vector3 Normalize(const Vector3& a) { return a / Length(a); }
inline Vector4 Normalize(const Vector4& a) { return a / Length(a); }

inline float Lerp(float t, float s, float e) { return s + t * (e - s); }
inline Vector2 Lerp(float t, const Vector2& s, const Vector2& e) { return s + t * (e - s); }
inline Vector3 Lerp(float t, const Vector3& s, const Vector3& e) { return s + t * (e - s); }
inline Vector4 Lerp(float t, const Vector4& s, const Vector4& e) { return s + t * (e - s); }

inline Vector2 Slerp(float t, const Vector2& s, const Vector2& e) { 
	float dot = Dot(Normalize(s), Normalize(e));
	if (Abs(dot) > 0.999f) {
		return Lerp(t, s, e);
	}
	float theta = Acos(dot);
	float sinTheta = Sin(theta);
	float t1 = Sin((1.0f - t) * theta) / sinTheta;
	float t2 = Sin(t * theta) / sinTheta;

	return t1 * s + t2 * e;
}
inline Vector3 Slerp(float t, const Vector3& s, const Vector3& e) {
	float dot = Dot(Normalize(s), Normalize(e));
	if (Abs(dot) > 0.999f) {
		return Lerp(t, s, e);
	}
	float theta = Acos(dot);
	float sinTheta = Sin(theta);
	float t1 = Sin((1.0f - t) * theta) / sinTheta;
	float t2 = Sin(t * theta) / sinTheta;

	return t1 * s + t2 * e;
}

inline float Cross(const Vector2& a, const Vector2& b) { return a.x * b.y - a.y * b.x; }
inline Vector3 Cross(const Vector3& a, const Vector3& b) { return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x}; } 

namespace Color {
	static Vector4 Black = {0.0f, 0.0f, 0.0f, 1.0f};
	static Vector4 White = {1.0f, 1.0f, 1.0f, 1.0f};
	static Vector4 Red = {1.0f, 0.0f, 0.0f, 1.0f};
	static Vector4 Green = {0.0f, 1.0f, 0.0f, 1.0f};
	static Vector4 Blue = {0.0f, 0.0f, 1.0f, 1.0f};
	static Vector4 Yellow = {1.0f, 1.0f, 0.0f, 1.0f};
	static Vector4 LightBlue = {0.0f, 1.0f, 1.0f, 1.0f};
	static Vector4 Purple = {1.0f, 0.0f, 1.0f, 1.0f};
} // namespace Color
