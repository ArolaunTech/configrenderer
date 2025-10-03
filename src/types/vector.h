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
Vector2 operator-(const Vector2& lhs);
Vector2 operator*(const Vector2& lhs, const double& rhs);
Vector2 operator*(const double& lhs, const Vector2& rhs);

Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
Vector3 operator-(const Vector3& lhs, const Vector3& rhs);
Vector3 operator-(const Vector3& lhs);
Vector3 operator*(const Vector3& lhs, const double& rhs);
Vector3 operator*(const double& lhs, const Vector3& rhs);

Vector4 operator+(const Vector4& lhs, const Vector4& rhs);
Vector4 operator-(const Vector4& lhs, const Vector4& rhs);
Vector4 operator-(const Vector4& lhs);
Vector4 operator*(const Vector4& lhs, const double& rhs);
Vector4 operator*(const double& lhs, const Vector4& rhs);

double length(Vector2 a);
double length(Vector3 a);
double length(Vector4 a);

Vector2 normalize(Vector2 a);
Vector3 normalize(Vector3 a);
Vector4 normalize(Vector4 a);

Vector3 cross(Vector3 a, Vector3 b);

#endif