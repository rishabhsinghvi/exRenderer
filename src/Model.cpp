#include "Model.h"

#include<iostream>

Model::Model(const std::string& fp) : filePath(fp) 
{
	loadModel();
}


void Model::loadModel()
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(filePath, aiProcess_GenNormals | aiProcess_FlipUVs | aiProcess_Triangulate | aiProcess_OptimizeMeshes);

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


void Model::draw() const
{
	for (const auto& mesh : meshes)
	{
		mesh->draw();
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

	for (int i = 0; i < curMesh->mNumFaces; i++)
	{
		for (int j = 0; j < curMesh->mFaces[i].mNumIndices; j++)
		{
			indices.push_back(curMesh->mFaces[i].mIndices[j]);
		}
	}

	auto vao = std::shared_ptr<VertexArray>(new VertexArray());
	auto vb = std::shared_ptr<VertexBuffer>(new VertexBuffer(vertices));
	auto ib = std::shared_ptr<IndexBuffer>(new IndexBuffer(indices));
	//VertexBuffer vb(vertices.data(), vertices.size() * sizeof(float), curMesh->mNumVertices);
	//vao->bindBuffer(vb, )
	//VertexArray vao;
	vao->bindVertexBuffer(vb, exRenderer::defaultLayout);
	vao->bindIndexBuffer(ib);

	//std::cout << "VA id is: " << vao->getId() << std::endl;

	//IndexBuffer ib(indices.data(), indices.size());
	auto mesh = std::shared_ptr<Mesh>(new Mesh(vao));
	//std::shared_ptr<Mesh> mesh = std::shared_ptr<Mesh>(new Mesh(vao, ib));

	return mesh;
	//return std::make_shared<Mesh>();
}
