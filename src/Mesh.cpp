#include "Mesh.h"

#include<utility>


void Mesh::draw(const Shader& shader) const
{
	int diffuseIndex = 0, specIndex = 0, normalIndex = 0, heightIndex = 0;

	for (auto i = 0; i < textures.size(); i++)
	{
		auto curTexture = textures.at(i);
		curTexture->bind(i);
		std::string uniformName;

		switch (curTexture->getType())
		{
		case aiTextureType_DIFFUSE:
 			uniformName = "diffuse" + std::to_string(diffuseIndex);
			++diffuseIndex;
			break;
		case aiTextureType_SPECULAR:
			uniformName = "specular" + std::to_string(diffuseIndex);
			++specIndex;
			break;
		case aiTextureType_HEIGHT:
			uniformName = "normal" + std::to_string(diffuseIndex);
			++normalIndex;
			break;
		case aiTextureType_AMBIENT:
			uniformName = "ambient" + std::to_string(diffuseIndex);
			++heightIndex;
			break;

		default: break;
		}
		shader.setUniformInt(uniformName, { i });
	}
	vertexArray->bind();
	vertexArray->draw();
	vertexArray->unbind();
}