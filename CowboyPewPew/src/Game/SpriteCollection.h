#pragma once

#include "Graphics/SubTexture.h"

namespace SpriteCollection {

	void init();

	constexpr glm::vec2 Tile_size { 16.0f, 16.0f };

	constexpr int null = 0;
	constexpr int sand_1 = 1;
	constexpr int sand_rock = 2;
	constexpr int sand_cactus = 3;
	constexpr int fire = 4;

	constexpr int player_head = 5;

	SubTexture* get(int index);

}