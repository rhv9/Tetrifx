#pragma once


class Texture
{
public:
	Texture(const std::string& path);
	~Texture();

	uint32_t GetWidth() const { return width; }
	uint32_t GetHeight() const { return height; }

	void Bind(uint32_t slot = 0) const;

private:
	uint32_t textureId;
	uint32_t width, height;

	int internalFormat, dataFormat;
};
