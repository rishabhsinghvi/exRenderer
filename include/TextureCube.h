#ifndef TEXTURE_CUBE_H
#define TEXTURE_CUBE_H

#include<vector>
#include<string>
#include<unordered_map>

#include "glad/glad.h"
#include "stb_image/stb_image.h"

class TextureCube
{
private:
	unsigned int texture_id;
	unsigned int texture_unit;
	std::vector<std::string> texture_paths;
	std::vector<unsigned int> widths;
	std::vector<unsigned int> heights;
	std::vector<unsigned int> channels;
	std::vector<unsigned char*> texture_data;

public:
	TextureCube(){}

	TextureCube(const std::vector<std::string>& paths, unsigned int textureUnit = 0);

	~TextureCube();

	inline void bind() const
	{
		glActiveTexture(texture_unit);
		glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);
	}

	inline void unbind() const
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}


};


#endif