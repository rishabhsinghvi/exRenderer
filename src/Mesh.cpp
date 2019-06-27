#include "Mesh.h"

#include<utility>


void Mesh::draw() const
{
	vertexArray->bind();
	vertexArray->draw();
	vertexArray->unbind();
}