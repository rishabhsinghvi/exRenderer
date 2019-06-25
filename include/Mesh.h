#ifndef MESH_H
#define MESH_H

#include<glm/vec3.hpp>

#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include<vector>


class Mesh
{
private:
	VertexArray vertexArray;
	IndexBuffer indexBuffer;
	std::vector<Texture> textures;

public:
	Mesh(const VertexArray& va, const IndexBuffer& ib, const std::vector<Texture>& tex);

	void draw() const;

	void initializeMesh() const;
};


#endif