#define CURL_STATICLIB

#include <iostream>
#include <random>
#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <iterator>
#include <regex>
#include <sstream>
#include <thread>

#include "Framework.h"
#include "GlobalVariables.h"
#include "curl.h"
#include "MapCreator.h"

class MyFramework : public Framework {

public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = WINDOW_WIDTH;
		height = WINDOW_HEIGHT;
		if (WINDOW_WIDTH == 0 && WINDOW_HEIGHT == 0)
			fullscreen = true;
		else
			fullscreen = false;
	}

	virtual bool Init() {

		
		return true;
	}

	virtual void Close() {

	}

	virtual bool Tick() {
		showCursor(false);
		for (int i = 0; i < WINDOW_WIDTH; i += 1000)
		{
			for (int j = 0; j < WINDOW_HEIGHT; j += 1000)
			{
				drawSprite(background, i - 100, j - 100);
			}
		}

		std::vector<Asteroid*> asteroids_temp;
		for (auto asteroid : asteroids)
		{
			asteroid->EachOtherCollision(asteroids);
			asteroid->Move();
			asteroid->Draw();
			if (battleship->CheckCollision(asteroid))
			{
				std::cout << "Game over!" << "\n";
				return 1;
			}
			if (reticle->CheckShoot(asteroid, false) && asteroid->GetType() == "big")
			{
				asteroids_temp.push_back(new SmallAsteroid(asteroids, 0, -1.5, false, asteroid->GetCoords().first + 12, asteroid->GetCoords().second - 10));
				asteroids_temp.push_back(new SmallAsteroid(asteroids, 0, 1.5, false, asteroid->GetCoords().first + 12, asteroid->GetCoords().second + 35));
			}
			if (reticle->CheckShoot(asteroid, false) && asteroid->GetType() == "small")
			{
				if (static_cast<double>(rand()) / RAND_MAX >= 1 - ABILITY_PROBABILITY)
				{
					icons.push_back(new Shield(false, asteroid->GetCoords().first, asteroid->GetCoords().second));
				}
			}
		}
		std::erase_if(asteroids, [this](Asteroid* a) -> bool {
			return reticle->CheckShoot(a); });
		for (auto asteroid : asteroids_temp)
		{
			asteroids.push_back(asteroid);
		}
		for (auto icon : icons)
		{
			icon->Draw();
			icon->MoveCheck();
		}
		std::erase_if(icons, [this](Icon* i) -> bool {
			return battleship->CheckCollisionIcon(i); });
		for (auto asteroid : asteroids)
		{
			asteroid->MoveCheck();
		}

		battleship->Draw();
		reticle->Draw();
		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {
		map_manager->mouse_move_event->Notify(x, y);
		reticle->SetPos(x, y);
		battleship->SetRot(x, y);
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {
		map_manager->mouse_click_event->Notify(button, isReleased);
		switch (button)
		{
		case FRMouseButton::LEFT:
			reticle->Shoot(battleship->GetCoords().first + battleship->GetSize().second / 2, battleship->GetCoords().second + battleship->GetSize().first / 2);
			break;
		case FRMouseButton::MIDDLE:
			break;
		case FRMouseButton::RIGHT:
			battleship->AbilityInit();
			break;
		case FRMouseButton::COUNT:
			break;
		default:
			break;
		}
	}

	virtual void onKeyPressed(FRKey k) {
		map_manager->key_press_event->Notify(k);
		for (auto asteroid : asteroids)
		{
			asteroid->MoveManual(k);
		}
		for (auto icon : icons)
		{
			icon->MoveManual(k);
		}
		battleship->MoveManual(k);
	}

	virtual void onKeyReleased(FRKey k) {
	}

	virtual const char* GetTitle() override
	{
		return "asteroids";
	}
private:

	///
	std::unique_ptr<MapCreator> map_manager;
	/// 
	




	//Asteroid* a1;
	Sprite* background;
	Character* battleship;
	std::vector<Asteroid*> asteroids;
	std::vector<Icon*> icons;

	Reticle* reticle;

	void asteroidsSpawn(int count, const char* path) {
		for (int i = 0; i < count; i++)
		{
			drawSprite(createSprite(path), rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT);
		}
	}
};


void Parameters(int argc, char** argv) {
	for (int i = 0; i < argc - 1; i++)
	{
		if (strcmp(argv[i], "-window") == 0)
		{
			std::string str = std::string(argv[i + 1]);
			std::istringstream iss(argv[i]);
			static const std::regex rdelim{ "x" };
			std::vector<std::string> strPairs{
					std::sregex_token_iterator(str.begin(), str.end(), rdelim, -1),
					std::sregex_token_iterator()
			};
			WINDOW_WIDTH = stoi(strPairs[0]);
			WINDOW_HEIGHT = stoi(strPairs[1]);
		}
		else if (strcmp(argv[i], "-map") == 0)
		{
			std::string str = std::string(argv[i + 1]);
			std::istringstream iss(argv[i]);
			static const std::regex rdelim{ "x" };
			std::vector<std::string> strPairs{
					std::sregex_token_iterator(str.begin(), str.end(), rdelim, -1),
					std::sregex_token_iterator()
			};
			MAP_WIDTH = stoi(strPairs[0]);
			MAP_HEIGHT = stoi(strPairs[1]);
		}
		else if (strcmp(argv[i], "-num_asteroids") == 0)
		{
			NUM_ASTEROIDS = atoi(argv[i + 1]);
		}
		else if (strcmp(argv[i], "-num_ammo") == 0)
		{
			NUM_AMMO = atoi(argv[i + 1]);
		}
		else if (strcmp(argv[i], "-ability_probability") == 0)
		{
			ABILITY_PROBABILITY = std::stod(argv[i + 1]);
		}
	}
}

int main(int argc, char** argv)
{
	Parameters(argc, argv);
	
	
	srand(time(NULL));
	
	//поток1
	std::thread t1([]() {
		while (true)
		{
			run(new MyFramework);
		}
	});
	//поток2
	std::thread t2([]() {
		/*CURL* curl_handle;
		CURLcode res;

		struct MemoryStruct chunk;
		chunk.memory = (char*)(std::malloc(1));
		chunk.size = 0;

		curl_handle = curl_easy_init();
		if (curl_handle) {
			curl_easy_setopt(curl_handle, CURLOPT_URL, "https://vernik03.ml/");
			curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);
			curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
			curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void*)&chunk);
			curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

			res = curl_easy_perform(curl_handle);

			if (res != CURLE_OK) {
				fprintf(stderr, "error: %s\n", curl_easy_strerror(res));
			}
			else {
				printf("Size: %lu\n", (unsigned long)chunk.size);
				printf("Data: %s\n", chunk.memory);
			}
			curl_easy_cleanup(curl_handle);
			free(chunk.memory);*/
	});
	
	t1.join();
	t2.join();
	
	return 0;
}
