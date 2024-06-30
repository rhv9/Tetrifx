#pragma once

#include "Graphics/SubTexture.h"

namespace SpriteCollection {

	void init();

	constexpr glm::vec2 Tile_size { 16.0f, 16.0f };

	constexpr int sand_1 = 0;
	constexpr int sand_rock = 1;
	constexpr int sand_cactus = 2;

	SubTexture* get(int index);

}