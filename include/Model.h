#ifndef MODEL_H
#define MODEL_H


#include "Mesh.h"

#include<vector>
#include<string>

class Model
{
private:
	std::string filePath;
	std::vector<Mesh> meshes;
	
	void loadModel();

public:
	
	Model(const std::string& fp);

	void draw();

};

#endif