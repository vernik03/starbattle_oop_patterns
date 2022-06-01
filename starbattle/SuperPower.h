#pragma once
#include "HeadSprite.h"

class SuperPower : public HeadSprite
{
public:
	SuperPower() {


		
	};
	
	~SuperPower(){};

private:

};

class Shield : public SuperPower
{
public:
	Shield(){
		width = 63;
		height = 63;
	};
	~Shield(){};

private:

};

class Rocket : public SuperPower
{
public:
	Rocket(){};
	~Rocket(){};

private:

};