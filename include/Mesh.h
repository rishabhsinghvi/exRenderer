#ifndef MESH_H
#define MESH_H

#include<glm/vec3.hpp>

#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include<vector>
#include<utility>

class Mesh
{
private:
	std::shared_ptr<VertexArray> vertexArray;
	std::vector<std::shared_ptr<Texture>> textures;
public:
	Mesh() 
	{

	}
	
	Mesh(const std::shared_ptr<VertexArray>& vArray): vertexArray(std::move(vArray))
	{
	}


	Mesh(const std::shared_ptr<VertexArray>& vArray, const std::vector<std::shared_ptr<Texture>>& textures_) : vertexArray(std::move(vArray)), textures(std::move(textures_))
	{
	}

	void draw() const;
private:


};

#endif