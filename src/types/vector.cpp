#include "vector.h"

Vector2 operator+(const Vector2& lhs, const Vector2& rhs) {
	return Vector2 {lhs.x + rhs.x, lhs.y + rhs.y};
}

Vector2 operator-(const Vector2& lhs, const Vector2& rhs) {
	return Vector2 {lhs.x - rhs.x, lhs.y - rhs.y};
}

Vector3 operator+(const Vector3& lhs, const Vector3& rhs) {
	return Vector3 {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

Vector3 operator-(const Vector3& lhs, const Vector3& rhs) {
	return Vector3 {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

Vector4 operator+(const Vector4& lhs, const Vector4& rhs) {
	return Vector4 {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w};
}

Vector4 operator-(const Vector4& lhs, const Vector4& rhs) {
	return Vector4 {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w};
}


Vector3 cross(Vector3 a, Vector3 b) {
	return Vector3{
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	};
}