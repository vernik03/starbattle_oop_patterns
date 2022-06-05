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
				asteroids.push_back(new BigAsteroid(rand() % MAP_WIDTH, rand() % MAP_HEIGHT, rand() % 10 - 5, rand() % 10 - 5));
			}
			else
			{
				asteroids.push_back(new SmallAsteroid(rand() % MAP_WIDTH, rand() % MAP_HEIGHT, rand() % 10 - 5, rand() % 10 - 5));
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
		
		while (AllAsteroidsCheckCollision(&main_hero) || AllShipsCheckCollision(&main_hero))
		{
			main_hero.SetCoords(rand() % MAP_WIDTH, rand() % MAP_HEIGHT);
		}

	};
	~MapCreator(){};

	bool AllAsteroidsCheckCollision(MovableSprite* object) {
		
		for (auto astroid_check : asteroids)
		{
			if (dynamic_cast<Ship*>(object))
			{
				if (object->Distance(astroid_check) < 50)
				{
					return true;
				}
			}
			else if (dynamic_cast<Asteroid*>(object))
			{
				if (astroid_check->CheckCollision(object))
				{
					return true;
				}
			}
		}
		return false;
	}

	bool AllShipsCheckCollision(HeadSprite* object) {
		if (dynamic_cast<MainHeroShip*>(object))
		{
			for (auto enemy : ships)
			{
				if (dynamic_cast<MainHeroShip*>(object))
				{
					if (enemy->Distance(object) < 300)
					{
						return true;
					}
				}
				else
				{
					if (enemy->CheckCollision(object))
					{
						return true;
					}
				}
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
		asteroids.push_back(new BigAsteroid(rand() % MAP_WIDTH, rand() % MAP_HEIGHT, rand() % 10 - 5, rand() % 10 - 5));
	}

	void DrawAll() {
		background->Draw();
		for (auto astroid : asteroids)
		{
			astroid->Draw();
		}
		for (auto ship : ships)
		{
			ship->Draw();
		}
		main_hero.Draw();
		inter.Draw();
	}

	void MoveAll() {
		for (auto astroid : asteroids)
		{
			astroid->Move();
		}
		for (auto ship : ships)
		{
			//ship->Move();
		}
		main_hero.Move();
	}

	void CheckCollisionsAll() {
		for (auto astroid : asteroids)
		{
			AllAsteroidsCheckCollision(astroid);
		}
		for (auto ship : ships)
		{
			if (main_hero.CheckCollision(ship))
			{

			}
			
		}
	}
	
	//динамически увеличивать карту и добавлять астероиды при присоединении новых игроков
protected:
	std::vector<Asteroid*> asteroids;
	MainHeroShip main_hero;
	std::vector<Ship*> ships;
	Background* background;
	Interface inter;
	
};
