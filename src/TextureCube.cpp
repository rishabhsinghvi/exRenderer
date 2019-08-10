#include "TextureCube.h"

#include<iostream>
#include<utility>

TextureCube::TextureCube(const std::vector<std::string>& paths)
{	
	//stbi_set_flip_vertically_on_load(true);
	texture_paths = std::move(paths);
	
	glGenTextures(1, &texture_id);
	
	int width, height, channel;

	for (int i = 0; i < texture_paths.size(); i++)
	{
		const std::string path = texture_paths.at(i);
		unsigned char* texData = stbi_load(path.c_str(), &width, &height, &channel, 0);
		if (texData)
		{
			widths.push_back(width);
			heights.push_back(height);
			channels.push_back(channel);
			texture_data.push_back(texData);

			if (path.find(".jpg") != std::string::npos)
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
			else if (path.find(".png") != std::string::npos)
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);

		}
		else
		{
			std::cout << "Unable to load texture: " << path << "\n";
			std::cin.get();
			exit(-1);
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

TextureCube::~TextureCube()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glDeleteTextures(1, &texture_id);
}
