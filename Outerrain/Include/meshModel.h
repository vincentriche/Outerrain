#pragma once

#include<vector>
#include<fstream>
#include<cstring>
#include<sstream>

#include "component.h"
#include "vec.h"

class MeshModel : public Component
{
	friend class MeshRenderer;

private:
	std::vector<Vector3> vertices;
	std::vector<Vector3> normals;
	std::vector<Vector2> texcoords;
	std::vector<unsigned int> indices;

	bool isDirty;

public:
	MeshModel();

	void AddVertex(const Vector3&);
	void AddNormal(const Vector3&);
	void AddTriangle(const unsigned int, const unsigned int, const unsigned int);
	void AddTexcoord(const Vector2&);

	Bounds GetBounds() const;
	bool LoadObj(const std::string& path);
	void ClearBuffers();
	void PrintInfos();


	/* Getter */
	size_t VerticeCount() const { return vertices.size(); }
	size_t NormalCount() const { return normals.size(); }
	size_t TexcoordCount() const { return texcoords.size(); }
	size_t IndicesCount() const { return indices.size(); }

	const float* VertexBufferPtr() const { return &vertices.front().x; }
	size_t VertexBufferSize() const { return vertices.size() * sizeof(Vector3); }

	const float *NormalBufferPtr() const { return &normals.front().x; }
	size_t NormalBufferSize() const { return normals.size() * sizeof(Vector3); }

	const float *TexcoordBufferPtr() const { return &texcoords.front().x; }
	size_t TexcoordBufferSize() const { return texcoords.size() * sizeof(Vector2); }

	const void *IndexBufferPtr() const { return &indices.front(); }
	size_t IndexBufferSize() const { return indices.size() * sizeof(unsigned int); }
};
