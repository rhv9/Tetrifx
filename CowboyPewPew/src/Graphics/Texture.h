#pragma once

struct TextureCoords
{
	glm::vec2 bottomLeft;
	glm::vec2 topRight;

	TextureCoords()
		: bottomLeft({ 0.0f, 0.0f }), topRight({ 1.0f, 1.0f }) {}

	TextureCoords(const glm::vec2& bottomLeftCoords, const glm::vec2& topRightCoords)
		: bottomLeft(bottomLeftCoords), topRight(topRightCoords) {}
};

class Texture
{
public:
	Texture(const std::string& path);
	virtual ~Texture();

	uint32_t GetWidth() const { return width; }
	uint32_t GetHeight() const { return height; }

	uint32_t GetTextureId() const { return textureId; }

	void Bind(uint32_t slot = 0) const;

	const TextureCoords& GetTexCoords() const { return textureCoords; }

protected:
	Texture() = default;

protected:
	uint32_t textureId;
	uint32_t width, height;

	TextureCoords textureCoords;

	int internalFormat, dataFormat;
};
