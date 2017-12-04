#pragma once
#include <math.h>
#include <iostream>


/* Forward Declarations */
struct Vector2;
struct Vector3;
struct Vector4;


/* Vector2 */
struct Vector2
{
public:
	float x, y;

	Vector2() : x(0.0), y(0.0) {}
	Vector2(float n) : x(n), y(n) {}
	Vector2(float x, float y) : x(x), y(y) {}

	Vector2 operator*(const float& k) const
	{
		return Vector2(x * k, y * k);
	}
	bool operator==(const Vector2& u) const
	{
		return (x == u.x && y == u.y);
	}
	Vector2 operator-(const Vector2& u) const
	{
		return Vector2(x - u.x, y - u.y);
	}
	Vector2 operator+(const Vector2& u) const
	{
		return Vector2(x + u.x, y + u.y);
	}
	float operator[](int i)
	{
		if (i == 0)
			return x;
		return y;
	}
	friend std::ostream& operator<< (std::ostream& stream, const Vector2& u);
};
inline std::ostream& operator<<(std::ostream& stream, const Vector2& u)
{
	stream << "(" << u.x << ", " << u.y << ");";
	return stream;
}
inline float Dot(const Vector2& u, const Vector2& v)
{
	return u.x * v.x + u.y * v.y;
}
inline float Magnitude(const Vector2& u)
{
	return sqrt(u.x * u.x + u.y * u.y);
}
inline Vector2 Normalize(const Vector2& v)
{
	float kk = 1 / Magnitude(v);
	return v * kk;
}
inline Vector2 Center(const Vector2& a, const Vector2& b)
{
	return Vector2((a.x + b.x) / 2, (a.y + b.y) / 2);
}
inline Vector2 operator-(const Vector2& v)
{
	return Vector2(-v.x, -v.y);
}


/* Vector3 */
struct Vector3
{
public:
	float x, y, z;

	explicit Vector3() : x(0.0), y(0.0), z(0.0) { }
	explicit Vector3(float n) : x(n), y(n), z(n) {}
	explicit Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

	Vector3 operator*(const float& k) const
	{
		return Vector3(x * k, y * k, z * k);
	}
	bool operator==(const Vector3& u) const
	{
		return (x == u.x && y == u.y && z == u.z);
	}
	Vector3 operator-(const Vector3& u) const
	{
		return Vector3(x - u.x, y - u.y, z - u.z);
	}
	Vector3 operator+(const Vector3& u) const
	{
		return Vector3(x + u.x, y + u.y, z + u.z);
	}
	float operator[](int i)
	{
		if (i == 0)
			return x;
		else if (i == 1)
			return y;
		return z;
	}
	friend std::ostream& operator<<(std::ostream& stream, const Vector3& u);
};
inline std::ostream& operator<<(std::ostream& stream, const Vector3& u)
{
	stream << "(" << u.x << ", " << u.y << ", " << u.z << ");";
	return stream;
}
inline Vector3 Cross(const Vector3& u, const Vector3& v)
{
	return Vector3(
		(u.y * v.z) - (u.z * v.y),
		(u.z * v.x) - (u.x * v.z),
		(u.x * v.y) - (u.y * v.x));
}
inline float Dot(const Vector3& u, const Vector3& v)
{
	return u.x * v.x + u.y * v.y + u.z * v.z;
}
inline float Magnitude(const Vector3& u)
{
	return sqrt(u.x * u.x + u.y * u.y + u.z * u.z);
}
inline Vector3 Normalize(const Vector3& v)
{
	float kk = 1 / Magnitude(v);
	return v * kk;
}
inline Vector3 Center(const Vector3& a, const Vector3& b)
{
	return Vector3((a.x + b.x) / 2, (a.y + b.y) / 2, (a.z + b.z) / 2);
}
inline Vector3 operator-(const Vector3& v)
{
	return Vector3(-v.x, -v.y, -v.z);
}


/* Vector4 */
struct Vector4
{
public:
	float x, y, z, w;

	Vector4() : x(0.0), y(0.0), z(0.0), w(0.0) {}
	Vector4(float n) : x(n), y(n), z(n), w(n) {}
	Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

	Vector4 operator*(const float& k) const
	{
		return Vector4(x * k, y * k, z * k, w * k);
	}
	bool operator==(const Vector4& u) const
	{
		return (x == u.x && y == u.y && z == u.z && w == u.w);
	}
	Vector4 operator-(const Vector4& u) const
	{
		return Vector4(x - u.x, y - u.y, z - u.z, w - u.w);
	}
	Vector4 operator+(const Vector4& u) const
	{
		return Vector4(x + u.x, y + u.y, z + u.z, w + u.w);
	}
	float operator[](int i)
	{
		if (i == 0)
			return x;
		else if (i == 1)
			return y;
		else if (i == 2)
			return z;
		return w;
	}
	friend std::ostream& operator<<(std::ostream& stream, const Vector4& u);
};
inline float Magnitude(const Vector4& u)
{
	return sqrt(u.x * u.x + u.y * u.y + u.z * u.z + u.w * u.w);
}
inline Vector4 Normalize(const Vector4& v)
{
	float kk = 1 / Magnitude(v);
	return v * kk;
}
inline std::ostream& operator<<(std::ostream& stream, const Vector4& u)
{
	stream << "(" << u.x << ", " << u.y << ", " << u.z << ", " << u.w << ");";
	return stream;
}
inline Vector4 operator-(const Vector4& v)
{
	return Vector4(-v.x, -v.y, -v.z, -v.w);
}


/* Bounds */
struct Bounds
{
	Vector3 min;
	Vector3 max;
};