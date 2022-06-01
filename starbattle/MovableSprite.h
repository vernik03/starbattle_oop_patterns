#pragma once
#include "HeadSprite.h"

class MovableSprite : public HeadSprite {
public:
	MovableSprite() {};
	MovableSprite(const char* sprite_path, double sprite_width, double sprite_height) {
		sprite = createSprite(sprite_path);
		width = sprite_width;
		height = sprite_height;
	};

	virtual ~MovableSprite() {};

	virtual void SetSpeed(double new_x_speed, double new_y_speed) {
		x_speed = new_x_speed;
		y_speed = new_y_speed;
	}

	virtual void Move() {
		global_y += y_speed;
		global_x += x_speed;
		Border();
	}

	virtual std::pair<double, double> GetSpeed() {
		return std::make_pair(y_speed, x_speed);
	}

	virtual double GetMass() {
		return mass;
	}

	void Border() {

		if (global_x + width / 2 >= MAP_WIDTH)
		{
			global_x = -1 * (width / 2);
		}
		else if (global_x < (width / 2) * -1)
		{
			global_x = MAP_WIDTH - width / 2;
		}

		if (global_y + height / 2 >= MAP_HEIGHT)
		{
			global_y = -1 * (height / 2);
		}
		else if (global_y < (height / 2) * -1)
		{
			global_y = MAP_HEIGHT - height / 2;
		}

	}

protected:
	double y_speed;
	double x_speed;

	int mass;
};