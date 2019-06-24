#ifndef TEXTURE_H
#define TEXTURE_H

#include<iostream>
#include<string>

#include "glad/glad.h"
#include "stb_image/stb_image.h"

#include<unordered_map>

class Texture;

static std::unordered_map<std::string, Texture*> textureCache;

class Texture
{
private:
	unsigned int texture_id;
	std::string texture_path;
	unsigned char* texture_data;
	int width, height, channels;

public:
	Texture() { /* Nothing */ }

	Texture(const std::string& path);

	~Texture();

	inline void bind(unsigned int textureUnit = 0) const
	{
		glActiveTexture(GL_TEXTURE0 + textureUnit);
		glBindTexture(GL_TEXTURE_2D, texture_id);
	}

	inline void unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
};

#endif