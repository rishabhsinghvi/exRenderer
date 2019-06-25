#include "Mesh.h"

#include<utility>

Mesh::Mesh(const VertexArray & va, const IndexBuffer & ib, const std::vector<Texture>& tex)
{
	vertexArray = std::move(va);
	indexBuffer = std::move(ib);
	textures = std::move(tex);
	
	initializeMesh();
}

void Mesh::draw() const
{
	vertexArray.bind();
	glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, 0);
	vertexArray.unbind();
}

void Mesh::initializeMesh() const
{
	vertexArray.bind();
	indexBuffer.bind();
	vertexArray.unbind();
}






