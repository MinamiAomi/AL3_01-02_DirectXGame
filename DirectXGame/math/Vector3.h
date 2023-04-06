#pragma once

/// <summary>
/// 3次元ベクトル
/// </summary>
struct Vector3 final {
	static Vector3 Zero;
	static Vector3 UnitX;
	static Vector3 UnitY;
	static Vector3 UnitZ;

	float x, y, z;

	Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

	// 比較演算子
	inline bool operator==(const Vector3& a) const { return x == a.x && y == a.y && z == a.z; }
	inline bool operator!=(const Vector3& a) const { return x != a.x || y != a.y || z == a.z; }

	// 単項演算子
	inline Vector3 operator+() const { return {x, y, z}; }
	inline Vector3 operator-() const { return {-x, -y, -z}; }

	// 代入演算子
	inline Vector3& operator+=(const Vector3& a) {
		x += a.x;
		y += a.y;
		z += a.z;
		return *this;
	}
	inline Vector3& operator-=(const Vector3& a) {
		x -= a.x;
		y -= a.y;
		z -= a.z;
		return *this;
	}
	inline Vector3& operator*=(const Vector3& a) {
		x *= a.x;
		y *= a.y;
		z *= a.z;
		return *this;
	}
	inline Vector3& operator*=(float s) {
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}
};