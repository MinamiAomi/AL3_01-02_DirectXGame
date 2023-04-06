#include "MyMath.h"

Vector2 Vector2::Zero = {0.0f, 0.0f};
Vector2 Vector2::UnitX = {1.0f, 0.0f};
Vector2 Vector2::UnitY = {0.0f, 1.0f};

Vector3 Vector3::Zero = {0.0f, 0.0f, 0.0f};
Vector3 Vector3::UnitX = {1.0f, 0.0f, 0.0f};
Vector3 Vector3::UnitY = {0.0f, 1.0f, 0.0f};
Vector3 Vector3::UnitZ = {0.0f, 0.0f, 1.0f};

Matrix4x4 Matrix4x4::Identity = { 
	1.0f, 0.0f, 0.0f, 0.0f, 
	0.0f, 1.0f, 0.0f, 0.0f, 
	0.0f, 0.0f, 1.0f, 0.0f, 
	0.0f, 0.0f, 0.0f, 1.0f	};

