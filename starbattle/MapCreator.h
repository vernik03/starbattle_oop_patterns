#pragma once
#include "Background.h"
#include "Asteroid.h"
#include "Ship.h"
#include "Events.h"
#include "Interface.h"

enum Rotation
{
	Top,
	Left,
	Bottom,
	Right
};

static class MapCreator //заведует всеми объектами на карте
{
public:
	std::unique_ptr<MouseClick> mouse_click_event;
	std::unique_ptr<KeyPress> key_press_event;
	std::unique_ptr<MouseMove> mouse_move_event;
	

public:
	MapCreator(){
		background = new Background("data/background_2.png", 1000, 1000);
		//mouse_click_event->Subscribe();
		
		key_press_event->Subscribe(&main_hero);
		
		mouse_move_event->Subscribe(&main_hero);
		mouse_move_event->Subscribe(&(inter.GetReticle()));
		
		for (int i = 0; i < NUM_ASTEROIDS; i++)
		{
			if (i < NUM_ASTEROIDS / 2)
			{
				asteroids.push_back(new BigAsteroid(rand() % MAP_WIDTH, rand() % MAP_HEIGHT));
			}
			else
			{
				asteroids.push_back(new SmallAsteroid(rand() % MAP_WIDTH, rand() % MAP_HEIGHT));
			}
		}
		
	};
	~MapCreator(){};

	void AddShip(int x, int y, Rotation rot) {
		
	}

	void MapResize() {
		
	}
	
	void AddAsteroid(int x, int y, Rotation rot) {
		asteroids.push_back(new BigAsteroid(rand() % MAP_WIDTH, rand() % MAP_HEIGHT));
	}

	
	//динамически увеличивать карту и добавлять астероиды при присоединении новых игроков
protected:
	std::vector<Asteroid*> asteroids;
	Ship main_hero;
	std::vector<Ship*> ships;
	Background* background;
	Interface inter;
	
};
