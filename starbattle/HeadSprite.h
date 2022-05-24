#pragma once
#include <iostream>
#include <vector>
#include "Framework.h"
#include "GlobalVariables.h"

class HeadSprite {
public:	
	HeadSprite() {};
	HeadSprite(const char* sprite_path, double sprite_width, double sprite_height) : width(sprite_width), height(sprite_height) {
		sprite = createSprite(sprite_path);
		type = "HeadSprite";
	};
	
	virtual ~HeadSprite(){};

	virtual void SetCoords(double new_x, double new_y) {
		global_x = new_x;
		global_y = new_y;
	}

	virtual void Draw() {
		drawSprite(sprite, x(), y());
	}

	virtual std::pair<double, double> GetCoords() {
		return std::make_pair(x(), y());
	}

	virtual std::pair<double, double> GetCoordsGlobal() {
		return std::make_pair(global_x, global_y);
	}

	virtual std::pair<double, double> GetSize() {
		return std::make_pair(width, height);
	}

	virtual double GetRadius() {
		return (height + width) / 4.0;
	}

	virtual std::pair<double, double> GetCenter() {
		return std::make_pair(x() + width / 2, y() + height / 2);
	}

	virtual std::pair<double, double> GetCenterGlobal() {
		return std::make_pair(global_x + width / 2, global_y + height / 2);
	}

	double x() {
		return global_x - WINDOW_X;
	}

	double y() {
		return global_y - WINDOW_Y;
	}

	std::string GetType() {
		return type;
	}

protected:
	Sprite* sprite;
	double width;
	double height;
	double global_x;
	double global_y;
	std::string type;
};
