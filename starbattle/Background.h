#pragma once
#include "MovableSprite.h"

static class Background : public HeadSprite
{
public:
	Background() {};
	Background(const char* sprite_path, double sprite_width, double sprite_height) {
		sprite = createSprite(sprite_path);
		width = sprite_width;
		height = sprite_height;
	};
	~Background();

	void Draw() override {
		for (int i = 1; i <= MAP_WIDTH / width + 1; i++)
		{
			for (int i = 1; i <= MAP_HEIGHT / height + 1; i++)
			{
				drawSprite(sprite, (global_x - WINDOW_X) * i, (global_y - WINDOW_Y) * i);
			}
		}		
	}
};