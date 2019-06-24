#include "Texture.h"

Texture::Texture(const std::string & path): texture_data(nullptr)
{
	if (textureCache.find(path) != textureCache.end())
	{
		std::cout << "Texture already loaded! Binding that texture to GL_TEXTURE_2D...\n";
		textureCache.find(path)->second->bind();
		return;
	}

	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
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
	if (texture_path.find(".jpg") != std::string::npos)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
	}
	else if (texture_path.find(".png") != std::string::npos)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);
	}
	// Only jpg and png so far

	glGenerateMipmap(GL_TEXTURE_2D);

	textureCache.insert({ texture_path, this });
}

Texture::~Texture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &texture_id);
}



