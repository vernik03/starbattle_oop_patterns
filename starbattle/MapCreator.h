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
		background = new Background();

		ObserverSubscribes();
		
		for (int i = 0; i < NUM_ASTEROIDS(); i++)
		{
			if (i < NUM_ASTEROIDS() / 2)
			{
				asteroids.push_back(new BigAsteroid(rand() % MAP_WIDTH, rand() % MAP_HEIGHT, rand() % 10 - 5));
			}
			else
			{
				asteroids.push_back(new SmallAsteroid(rand() % MAP_WIDTH, rand() % MAP_HEIGHT, rand() % 10 - 5));
			}
		}

		for(auto astroid : asteroids)
		{
			while (AllAsteroidsCheckCollision(astroid))
			{
				astroid->SetCoords(rand() % MAP_WIDTH, rand() % MAP_HEIGHT);
			}
			
		}

		main_hero.SetCoords(rand() % MAP_WIDTH, rand() % MAP_HEIGHT);

		

		
		
	};
	~MapCreator(){};

	bool AllAsteroidsCheckCollision(MovableSprite* object) {
		for (auto astroid_check : asteroids)
		{
			if (astroid_check->CheckCollision(object))
			{
				return true;
			}
		}
		return false;
	}

	bool AllShipsCheckCollision(HeadSprite* object) {

		///////////!!!!
		{
			for (auto astroid_check : asteroids)
			{
				while (main_hero.Distance(astroid_check) < 50 && main_hero.Distance(enemy) < 300)
				{
					main_hero.SetCoords(rand() % MAP_WIDTH, rand() % MAP_HEIGHT);
				}
			}
		}
		for (auto enemy : ships)
		{
			if (enemy->CheckCollision(object))
			{
				return true;
			}
		}
		return false;
	}


	void ObserverSubscribes() {
		//mouse_click_event->Subscribe();
		key_press_event->Subscribe(&main_hero);
		mouse_move_event->Subscribe(&main_hero);
		mouse_move_event->Subscribe(&(inter.GetReticle()));
	}

	void AddShip(int x, int y, Rotation rot) {
		
	}

	void MapResize() {
		
	}
	
	void AddAsteroid(int x, int y, Rotation rot) {
		asteroids.push_back(new BigAsteroid(rand() % MAP_WIDTH, rand() % MAP_HEIGHT, rand() % 10 - 5));
	}

	
	//динамически увеличивать карту и добавлять астероиды при присоединении новых игроков
protected:
	std::vector<Asteroid*> asteroids;
	Ship main_hero;
	std::vector<Ship*> ships;
	Background* background;
	Interface inter;
	
};
