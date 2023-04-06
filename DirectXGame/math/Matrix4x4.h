#pragma once
/// <summary>
/// 4x4行列
/// </summary>
struct Matrix4x4 final {

	static Matrix4x4 Identity;
	
	float m[4][4];

	Matrix4x4() { 
		*this = Identity;
	}
	Matrix4x4(
		float _00, float _01, float _02, float _03,
		float _10, float _11, float _12, float _13,
		float _20, float _21, float _22, float _23, 
		float _30, float _31, float _32, float _33) {
		m[0][0] = _00, m[0][1] = _01, m[0][2] = _02, m[0][3] = _03;
		m[1][0] = _10, m[1][1] = _11, m[1][2] = _12, m[1][3] = _13;
		m[2][0] = _20, m[2][1] = _21, m[2][2] = _22, m[2][3] = _23;
		m[3][0] = _30, m[3][1] = _31, m[3][2] = _32, m[3][3] = _33;
	}
	friend inline Matrix4x4 operator*(const Matrix4x4& a, const Matrix4x4& b) {
		return {
		    a.m[0][0] * b.m[0][0] + a.m[0][1] * b.m[1][0] + a.m[0][2] * b.m[2][0] + a.m[0][3] * b.m[3][0],
		    a.m[0][0] * b.m[0][1] + a.m[0][1] * b.m[1][1] + a.m[0][2] * b.m[2][1] + a.m[0][3] * b.m[3][1],
		    a.m[0][0] * b.m[0][2] + a.m[0][1] * b.m[1][2] + a.m[0][2] * b.m[2][2] + a.m[0][3] * b.m[3][2],
		    a.m[0][0] * b.m[0][3] + a.m[0][1] * b.m[1][3] + a.m[0][2] * b.m[2][3] + a.m[0][3] * b.m[3][3],

		    a.m[1][0] * b.m[0][0] + a.m[1][1] * b.m[1][0] + a.m[1][2] * b.m[2][0] + a.m[1][3] * b.m[3][0],
		    a.m[1][0] * b.m[0][1] + a.m[1][1] * b.m[1][1] + a.m[1][2] * b.m[2][1] + a.m[1][3] * b.m[3][1],
		    a.m[1][0] * b.m[0][2] + a.m[1][1] * b.m[1][2] + a.m[1][2] * b.m[2][2] + a.m[1][3] * b.m[3][2],
		    a.m[1][0] * b.m[0][3] + a.m[1][1] * b.m[1][3] + a.m[1][2] * b.m[2][3] + a.m[1][3] * b.m[3][3],

		    a.m[2][0] * b.m[0][0] + a.m[2][1] * b.m[1][0] + a.m[2][2] * b.m[2][0] + a.m[2][3] * b.m[3][0],
		    a.m[2][0] * b.m[0][1] + a.m[2][1] * b.m[1][1] + a.m[2][2] * b.m[2][1] + a.m[2][3] * b.m[3][1],
		    a.m[2][0] * b.m[0][2] + a.m[2][1] * b.m[1][2] + a.m[2][2] * b.m[2][2] + a.m[2][3] * b.m[3][2],
		    a.m[2][0] * b.m[0][3] + a.m[2][1] * b.m[1][3] + a.m[2][2] * b.m[2][3] + a.m[2][3] * b.m[3][3],

		    a.m[3][0] * b.m[0][0] + a.m[3][1] * b.m[1][0] + a.m[3][2] * b.m[2][0] + a.m[3][3] * b.m[3][0],
		    a.m[3][0] * b.m[0][1] + a.m[3][1] * b.m[1][1] + a.m[3][2] * b.m[2][1] + a.m[3][3] * b.m[3][1],
		    a.m[3][0] * b.m[0][2] + a.m[3][1] * b.m[1][2] + a.m[3][2] * b.m[2][2] + a.m[3][3] * b.m[3][2],
		    a.m[3][0] * b.m[0][3] + a.m[3][1] * b.m[1][3] + a.m[3][2] * b.m[2][3] + a.m[3][3] * b.m[3][3]};
	}
	friend inline Matrix4x4 operator*(const Matrix4x4& a, float s) {
		return {a.m[0][0] * s, a.m[0][1] * s, a.m[0][2] * s, a.m[0][3] * s,
		        a.m[1][0] * s, a.m[1][1] * s, a.m[1][2] * s, a.m[1][3] * s,
		        a.m[2][0] * s, a.m[2][1] * s, a.m[2][2] * s, a.m[2][3] * s,
		        a.m[3][0] * s, a.m[3][1] * s, a.m[3][2] * s, a.m[3][3] * s};
	}
	inline Matrix4x4& operator*=(const Matrix4x4& a) { 
		*this = *this * a;
		return *this;
	}
	inline Matrix4x4& operator*=(float s) { 
		*this = *this * s;
		return *this;
	}

};
