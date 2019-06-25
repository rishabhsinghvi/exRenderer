#include "Model.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include<utility>
#include<iostream>

Model::Model(const std::string & fp)
{
	filePath = std::move(fp);
	loadModel();
}

void Model::loadModel()
{
	//TODO
}


void Model::draw()
{
	//TODO
}
