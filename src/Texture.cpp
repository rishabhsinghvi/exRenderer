#include "Texture.h"
#include<iostream>

Texture::Texture(const std::string & path) : texture_data(nullptr)
{
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	texture_path = path;

	stbi_set_flip_vertically_on_load(true);
	texture_data = stbi_load(texture_path.c_str(), &width, &height, &channels, 0);

	if (!texture_data)
	{
		std::cout << "Failed to load texture: " << texture_path << "\n";
		exit(-1);
	}

	// Need to check extension. jpg requires GL_RGB as the format, png requires GL_RGBA. Using GL_RGBA with jpg will result in a seg fault
	//if (texture_path.find(".jpg") != std::string::npos)
	if(channels == 3)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
	}
	//else if (texture_path.find(".png") != std::string::npos)
	else if(channels == 4)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);
	}
	// Only jpg and png so far

	glGenerateMipmap(GL_TEXTURE_2D);

}

Texture::~Texture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &texture_id);
}



