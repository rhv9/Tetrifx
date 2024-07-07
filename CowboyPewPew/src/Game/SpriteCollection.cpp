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

	spriteMap[null] = { spritesheet, glm::vec2{ 1, 1 }, SpriteCollection::Tile_size };
	spriteMap[sand_1] = { spritesheet, glm::vec2{ 0, 0 }, SpriteCollection::Tile_size };
	spriteMap[sand_rock] = { spritesheet, glm::vec2{ 1, 0 }, SpriteCollection::Tile_size };
	spriteMap[sand_cactus] = { spritesheet, glm::vec2{ 2, 0 }, SpriteCollection::Tile_size };
	spriteMap[fire] = { spritesheet, glm::vec2{ 0, 1 }, SpriteCollection::Tile_size };

	spriteMap[player_head] = { spritesheet, glm::vec2{ 0, 2 }, SpriteCollection::Tile_size };
}

SubTexture* SpriteCollection::get(int index)
{
	return &spriteMap[index];
}

