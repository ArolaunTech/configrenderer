#ifndef VECTOR_H
#define VECTOR_H

struct Vector2 {
	double x;
	double y;
};

struct Vector3 {
	double x;
	double y;
	double z;
};

struct Vector4 {
	double x;
	double y;
	double z;
	double w;
};

Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
Vector2 operator-(const Vector2& lhs, const Vector2& rhs);
Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
Vector3 operator-(const Vector3& lhs, const Vector3& rhs);
Vector4 operator+(const Vector4& lhs, const Vector4& rhs);
Vector4 operator-(const Vector4& lhs, const Vector4& rhs);

Vector3 cross(Vector3 a, Vector3 b);

#endif