#ifndef TEXTURE_H
#define TEXTURE_H

#include<string>
#include<unordered_map>

#include "glad/glad.h"
#include "stb_image/stb_image.h"


class Texture;

static std::unordered_map<std::string, Texture*> textureCache;

class Texture
{
private:
	unsigned int texture_id;
	std::string texture_path;
	unsigned char* texture_data;
	int width, height, channels;
	unsigned int texture_unit;

public:
	Texture() { /* Nothing */ }

	Texture(const std::string& path, unsigned int textUnit = 0);

	~Texture();

	inline void bind() const
	{
		glActiveTexture(GL_TEXTURE0 + texture_unit);
		glBindTexture(GL_TEXTURE_2D, texture_id);
	}

	inline void unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
};

#endif