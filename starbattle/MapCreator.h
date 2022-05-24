#pragma once
#include "Background.h"
#include "Asteroid.h"
//#include "Ship.h"

static class MapCreator //заведует всеми объектами на карте
{
public:
	MapCreator(){
		background = new Background("data/background_2.png", 1000, 1000);
	};
	~MapCreator(){};
	
	//динамически увеличивать карту и добавлять астероиды при присоединении новых игроков
protected:
	std::vector<Asteroid*> asteroids;
	std::vector<Ship*> ships;
	Background* background;
	

};
