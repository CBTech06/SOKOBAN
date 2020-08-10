#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <tinyxml2.h>
#include "map.hpp"
#include "player.hpp"
#include "block.hpp"

class Blocks;
const int TILESIZE(32);

class Game
{
	private:
		const float GAMESPEED;
		std::vector<sf::Sprite> wallsVector;
		std::vector<sf::Sprite> blocksVector;
		std::vector<int> tmp;
		sf::RenderWindow window;
		sf::Event event;
		sf::Texture titleTexture;
		sf::Sprite title;
		sf::Sprite sClear;
		sf::Texture sClearTexture;
		std::vector<int> mapArray;
		sf::Clock clock;
		tinyxml2::XMLDocument doc;
		
	public:
		Game();
		std::vector<int>& loadBlockInfo(const char*);
		std::vector<int>& loadMapInfo(const char*);
		void getMapInformation(Map&);
		void getBlockInformation(Blocks&);
		inline std::vector<sf::Sprite>& returnMapInformation() { return wallsVector; }
		inline std::vector<sf::Sprite>& returnBlockInformation() { return blocksVector; }
		void loop();
};

#endif
