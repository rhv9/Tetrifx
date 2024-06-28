#include "pch.h"
#include "SubTexture.h"

SubTexture::SubTexture(const std::shared_ptr<Texture>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize)
{
	textureId = texture->GetTextureId();
	textureParent = texture;

	const glm::vec2 bottomLeftCoords{
		(coords.x * cellSize.x) / texture->GetWidth(),
		(coords.y * cellSize.y) / texture->GetHeight(),
	};

	const glm::vec2 topRightCoords = {
		((coords.x + spriteSize.x) * cellSize.x) / texture->GetWidth(),
		((coords.y + spriteSize.y) * cellSize.y) / texture->GetHeight()
	};

	width = cellSize.x * spriteSize.x;
	height = cellSize.y * spriteSize.y;

	textureCoords = { bottomLeftCoords, topRightCoords };
}
