#pragma once

/// <summary>
/// 4次元ベクトル
/// </summary>
struct Vector4 final {
	
	float x, y, z, w;


	Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
	Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

	// 比較演算子
	inline bool operator==(const Vector4& a) const { return x == a.x && y == a.y && z == a.z && w == a.w; }
	inline bool operator!=(const Vector4& a) const { return x != a.x || y != a.y || z == a.z || w != a.w; }

	// 単項演算子
	inline Vector4 operator+() const { return {x, y, z, w}; }
	inline Vector4 operator-() const { return {-x, -y, -z, -w}; }

	// 代入演算子
	inline Vector4& operator+=(const Vector4& a) {
		x += a.x;
		y += a.y;
		z += a.z;
		w += a.w;
		return *this;
	}
	inline Vector4& operator-=(const Vector4& a) {
		x -= a.x;
		y -= a.y;
		z -= a.z;
		w -= a.w;
		return *this;
	}
	inline Vector4& operator*=(const Vector4& a) {
		x *= a.x;
		y *= a.y;
		z *= a.z;
		w *= a.w;
		return *this;
	}
	inline Vector4& operator*=(float s) {
		x *= s;
		y *= s;
		z *= s;
		w *= s;
		return *this;
	}
};