#include "Model.h"

#include<iostream>

Model::Model(const std::string& fp) : filePath(fp) 
{
	loadModel();
}

const static std::vector<aiTextureType> textureTypes =
{
	aiTextureType_DIFFUSE,
	aiTextureType_SPECULAR,
	aiTextureType_HEIGHT,
	aiTextureType_AMBIENT
};

void Model::loadModel()
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(filePath, aiProcess_GenNormals | aiProcess_FlipUVs | aiProcess_Triangulate| aiProcess_OptimizeMeshes | aiProcess_OptimizeGraph);

if (!scene)
{
	std::cout << "Assimp Error: Cannot load model " << filePath << "\n";
	std::cout << importer.GetErrorString();
	std::cin.get();
	exit(-1);
}

auto rootNode = scene->mRootNode;
getNodeData(scene, rootNode);
}


void Model::draw(const Shader& shader) const
{
	for (const auto& mesh : meshes)
	{
		mesh->draw(shader);
	}
}

void Model::getNodeData(const aiScene* scene, aiNode* curNode)
{
	for (int i = 0; i < curNode->mNumMeshes; i++)
	{
		auto curMesh = scene->mMeshes[curNode->mMeshes[i]];
		meshes.push_back(getMeshData(scene, curMesh));
	}

	for (int i = 0; i < curNode->mNumChildren; i++)
	{
		getNodeData(scene, curNode->mChildren[i]);
	}
}

std::shared_ptr<Mesh> Model::getMeshData(const aiScene * scene, aiMesh * curMesh)
{
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	//TODO: textures
	vertices.reserve(curMesh->mNumVertices * 8);

	// Push vertices data into vertex buffer
	for (int i = 0; i < curMesh->mNumVertices; i++)
	{
		vertices.push_back(curMesh->mVertices[i].x);
		vertices.push_back(curMesh->mVertices[i].y);
		vertices.push_back(curMesh->mVertices[i].z);

		vertices.push_back(curMesh->mNormals[i].x);
		vertices.push_back(curMesh->mNormals[i].y);
		vertices.push_back(curMesh->mNormals[i].z);

		if (curMesh->mTextureCoords[0])
		{
			vertices.push_back(curMesh->mTextureCoords[0][i].x);
			vertices.push_back(curMesh->mTextureCoords[0][i].y);
		}
		else
		{
			vertices.push_back(0.0f);
			vertices.push_back(0.0f);
		}

	}

	// Push index data into index buffer
	for (int i = 0; i < curMesh->mNumFaces; i++)
	{
		for (int j = 0; j < curMesh->mFaces[i].mNumIndices; j++)
		{
			indices.push_back(curMesh->mFaces[i].mIndices[j]);
		}
	}
	
	auto mat = scene->mMaterials[curMesh->mMaterialIndex];

	std::vector<std::shared_ptr<Texture>> textures_ = getTextures(mat);


	auto vao = std::shared_ptr<VertexArray>(new VertexArray());
	auto vb = std::shared_ptr<VertexBuffer>(new VertexBuffer(vertices));
	auto ib = std::shared_ptr<IndexBuffer>(new IndexBuffer(indices));

	vao->bindVertexBuffer(vb, exRenderer::defaultLayout);
	vao->bindIndexBuffer(ib);



	auto mesh = std::shared_ptr<Mesh>(new Mesh(vao, textures_));

	return mesh;
}

std::vector<std::shared_ptr<Texture>> Model::getTextures(aiMaterial * mat)
{
	std::vector<std::shared_ptr<Texture>> textureList;

	for (int j = 0; j < textureTypes.size(); j++)
	{
		auto TextureType = textureTypes.at(j);
		for (auto i = 0; i < mat->GetTextureCount(TextureType); i++)
		{
			aiString textureName;
			mat->GetTexture(TextureType, i, &textureName);

			auto textureString = textureName.C_Str();
			//if (textureCache.find(textureString) != textureCache.end()) // texture already loaded
			//{
			//	textureList.push_back(textureCache.find(textureString)->second);
			//}
			//else
			//{
				auto directory = filePath.substr(0, filePath.find_last_of('/'));
				auto texture_ = std::shared_ptr<Texture>(new Texture(directory + '/' + std::string(textureString), TextureType));

				textureList.push_back(texture_);
			//	textureCache.insert({ textureString, texture_ });
			//}
		}
	}

	return textureList;
}
