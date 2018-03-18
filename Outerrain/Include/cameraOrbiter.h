#pragma once

#include "vec.h"
#include "transform.h"
#include "box.h"
#include "camera.h"

class CameraOrbiter : public Camera
{
protected:
	Vector3 center;
	Vector2 position;
	Vector2 rotation;
	float size;

public:
	CameraOrbiter();
	CameraOrbiter(const Vector3& center, const float size, const float zNear, const float zFar);
	CameraOrbiter(const Vector3& pmin, const Vector3& pmax);

	void LookAt(const Vector3& center, const float size);
	void LookAt(const Vector3& pmin, const Vector3& pmax);
	void LookAt(const Box&);

	float GetSize() const { return size; }
	void Rotation(float x, float y);
	void Translation(float x, float y);
	void Move(float z);
	Transform View() const;
	Transform Projection(float width, float height, float fov) const;
	void Frame(float width, float height, float z, float fov, Vector3& dO, Vector3& dx, Vector3& dy) const;
	 
	Vector3 Position() const;

};
