#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>

class Map
{
	private:
		sf::Texture tileset;
		std::vector<sf::Sprite> tile;
		std::vector<int> map;
		const int TILESIZE;
		const int NB_TILE_WIDTH;
		const int NB_TILE_HEIGHT;
		int nTile;
		int tileX;
		int tileY;
		int tmp;
		int idx;
	public:
		Map();
		void load(const char*);
		void setTileTexture();
		const std::vector<sf::Sprite>& getTile();
		const int& getTileValue(const int&);
		const int getTileNumber();
		void  draw(sf::RenderWindow&);
};

#endif
