#pragma once
#include <vector>
#include "vec.h"
#include "mesh.h"

class Scalarfield2D
{
protected:
	int nx, ny;
	Vector2 bottomLeft, topRight;
	std::vector<double> values;

public:
	Scalarfield2D() { }
	Scalarfield2D(int, int, Vector2, Vector2);

	int Index(int, int) const;
	double At(int, int) const;
	double GetValueBilinear(const Vector2&) const;
	bool Inside(const Vector3&) const; // TODO Nathan
};

class Heightfield : public Scalarfield2D
{
public:
	Heightfield() : Scalarfield2D() { }
	Heightfield(int, int, Vector2, Vector2);

	void InitFromFile(const char* file, float blackAltitude, float whiteAltitude);
	void InitFromNoise(int, int);

	Vector3 Normal(int, int) const;
	Vector3 Vertex(int, int) const;
	double Height(const Vector2&) const;
	Mesh GetMesh() const;

private:
	float Lerp(float a, float b, float f);
};
