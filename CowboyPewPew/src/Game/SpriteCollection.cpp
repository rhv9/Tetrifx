#include "pch.h"
#include "SpriteCollection.h"

#include "Graphics/SubTexture.h"


static std::shared_ptr<Texture> spritesheet;
static SubTexture* spriteMap;

static constexpr uint32_t size = 256;



void SpriteCollection::init()
{
	spriteMap = new SubTexture[size];
	spritesheet = std::make_shared<Texture>("assets/textures/spritesheet.png");

	spriteMap[sand_1] = { spritesheet, glm::vec2{ 0.0f, 0.0f }, SpriteCollection::Tile_size };
	spriteMap[sand_rock] = { spritesheet, glm::vec2{ 1.0f, 0.0f }, SpriteCollection::Tile_size };
	spriteMap[sand_cactus] = { spritesheet, glm::vec2{ 2.0f, 0.0f }, SpriteCollection::Tile_size };
}

SubTexture* SpriteCollection::get(int index)
{
	return &spriteMap[index];
}

