#pragma once

/// <summary>
/// 2次元ベクトル
/// </summary>
struct Vector2 final {
	static Vector2 Zero;
	static Vector2 UnitX;
	static Vector2 UnitY;

	float x, y;

	Vector2() : x(0.0f), y(0.0f) {}
	Vector2(float x, float y) : x(x), y(y) {}
	
	// 比較演算子
	inline bool operator==(const Vector2& a) const { return x == a.x && y == a.y; }
	inline bool operator!=(const Vector2& a) const { return x != a.x || y != a.y; }

	// 単項演算子
	inline Vector2 operator+() const { return {x, y}; }
	inline Vector2 operator-() const { return {-x, -y}; }
	
	// 代入演算子
	inline Vector2& operator+=(const Vector2& a) {
		x += a.x;
		y += a.y;
		return *this;
	}
	inline Vector2& operator-=(const Vector2& a) {
		x -= a.x;
		y -= a.y;
		return *this;
	}
	inline Vector2& operator*=(const Vector2& a) {
		x *= a.x;
		y *= a.y;
		return *this;
	}
	inline Vector2& operator*=(float s) { 
		x *= s;
		y *= s;
		return *this;
	}
};