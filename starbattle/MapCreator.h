#pragma once
#include "Background.h"
#include "Asteroid.h"
//#include "Ship.h"

static class MapCreator //�������� ����� ��������� �� �����
{
public:
	MapCreator(){
		background = new Background("data/background_2.png", 1000, 1000);
	};
	~MapCreator(){};
	
	//����������� ����������� ����� � ��������� ��������� ��� ������������� ����� �������
protected:
	std::vector<Asteroid*> asteroids;
	std::vector<Ship*> ships;
	Background* background;
	

};
