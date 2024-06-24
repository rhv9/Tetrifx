#include "pch.h"
#include "Texture.h"

#include "glad/glad.h"
#include <stb_image.h>


Texture::Texture(const std::string& path)
{
	stbi_set_flip_vertically_on_load(1);
	int width, height, channels;
	stbi_uc* data = nullptr;

	data = stbi_load(path.c_str(), &width, &height, &channels, 0);

	this->width = width;
	this->height = height;

	internalFormat = 0, dataFormat = 0;
	if (channels == 4)
	{
		internalFormat = GL_RGBA8;
		dataFormat = GL_RGBA;
	}
	else if (channels == 3)
	{
		internalFormat = GL_RGB8;
		dataFormat = GL_RGB;
	}

	textureId = -1;

	glCreateTextures(GL_TEXTURE_2D, 1, &textureId);
	glTextureStorage2D(textureId, 1, internalFormat, this->width, this->height);

	glTextureParameteri(textureId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(textureId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureSubImage2D(textureId, 0, 0, 0, this->width, this->height, dataFormat, GL_UNSIGNED_BYTE, (void*) data);

	stbi_image_free(data);
}

Texture::~Texture()
{
	glDeleteTextures(1, &textureId);
}


void Texture::Bind(uint32_t slot) const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTextureUnit(slot, textureId);
}
