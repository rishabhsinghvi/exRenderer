#ifndef MODEL_H
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "VertexArray.h"
#include "Texture.h"

#include<vector>
#include<string>
#include<memory>
#include<unordered_map>

namespace exRenderer
{
	const static std::vector<AttributeLayout> defaultLayout = {
		{3, GL_FLOAT, GL_TRUE},
		{3, GL_FLOAT, GL_TRUE},
		{2, GL_FLOAT, GL_TRUE}
	};
}

class Model
{
private:
	std::string filePath;
	std::vector<std::shared_ptr<Mesh>> meshes;
	std::unordered_map<const char *, std::shared_ptr<Texture>> textureCache;
	void loadModel();

public:
	
	Model(const std::string& fp);

	void draw() const;

private:

	void getNodeData(const aiScene* scene, aiNode* curNode);
	std::shared_ptr<Mesh> getMeshData(const aiScene* scene, aiMesh* curMesh);

	std::vector<std::shared_ptr<Texture>> getTextures(aiMaterial* mat);
};

#endif