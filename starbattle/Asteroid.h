#pragma once
#include "MovableSprite.h"


class Asteroid : public MovableSprite //фабрика!!
{
public:
	Asteroid(){};
	Asteroid(const char* sprite_path, double sprite_width, double sprite_height, int sprite_mass) {
		sprite = createSprite(sprite_path);
		width = sprite_width;
		height = sprite_height;
		mass = sprite_mass;
	};

	virtual ~Asteroid(){};

	virtual bool CheckCollision(MovableSprite* element) {

		if (element == this)
		{
			return 0;
		}
		else if (GetRadius() + element->GetRadius()
			>= sqrt(pow(GetCenter().first - element->GetCenter().first, 2)
			+ pow(GetCenter().second - element->GetCenter().second, 2)))
		{
			//if (element->GetType() == "Asteroid")//костыль
			if (dynamic_cast<Asteroid*>(element))
			{
				std::pair<double, double> result = CountCollision(element);
				element->SetSpeed(result.first, result.second);
				return 1;
			}
			else 
			{
				return 1;
			}
		}
		else
		{
			return 0;
		}
	}
	
private:
	virtual std::pair<double, double> CountCollision(MovableSprite* element) {
		double d = sqrt(pow(GetCenter().first - element->GetCenter().first, 2)
			+ pow(GetCenter().second - element->GetCenter().second, 2));
		if (d == 0)
		{
			return;
		}
		double ny = (element->GetCenter().second - GetCenter().second) / d;
		double nx = (element->GetCenter().first - GetCenter().first) / d;
		/*double p = 2 * (y_speed * ny + x_speed * nx - element->GetSpeed().second * ny - element->GetSpeed().first * nx) /
			(mass + element->GetMass());
		y_speed = y_speed - p * mass * ny;
		x_speed = x_speed - p * mass * nx;
		double vy2 = element->GetSpeed().second + p * element->GetMass() * ny;
		double vx2 = element->GetSpeed().first + p * element->GetMass() * nx;
		return std::make_pair(vx2, vy2);*/

		double v1_x = (x_speed * (mass - element->GetMass()) + 2* element->GetMass() * element->GetSpeed().first) / (mass + element->GetMass());
		double v2_x = (element->GetSpeed().first * (element->GetMass() - mass) + 2 * mass * x_speed) / (mass + element->GetMass());
		double v1_y = (y_speed * (mass - element->GetMass()) + 2 * element->GetMass() * element->GetSpeed().second) / (mass + element->GetMass());
		double v2_y = (element->GetSpeed().second * (element->GetMass() - mass) + 2 * mass * y_speed) / (mass + element->GetMass());
		
		SetSpeed(v1_x, v1_y);
		element->SetSpeed(v2_x, v2_y);
		return std::make_pair(v2_x, v2_y);
	}	
};

class BigAsteroid : public Asteroid
{
public:
	BigAsteroid(int x, int y, double speed_x, double speed_y) {
		sprite = createSprite("data/big_asteroid.png"); // легковес!!
		width = 68;
		height = 60;
		mass = 10;
		SetCoordsByCenter(x, y);
		SetSpeed(speed_x, speed_y);
	};
	
	std::pair<SmallAsteroid, SmallAsteroid> Split() {
		SmallAsteroid asteroid1(global_x + 12, global_y - 10, 0, -1.5);
		SmallAsteroid asteroid2(global_x + 12, global_y + 35, 0, 1.5);
		return std::make_pair(asteroid1, asteroid2);		
	}
	

private:

};

class SmallAsteroid : public Asteroid
{
public:
	SmallAsteroid(int x, int y, double speed_x, double speed_y) {
		sprite = createSprite("data/small_asteroid.png");// легковес!!
		width = 44;
		height = 36;
		mass = 6;
		SetCoordsByCenter(x, y);
		SetSpeed(speed_x, speed_y);
	};

private:

};

