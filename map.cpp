#include "map.hpp"

Map::Map():TILESIZE(32),NB_TILE_WIDTH(31),NB_TILE_HEIGHT(18)
{
	tileset.loadFromFile("Resources/levelgridless.png");
	nTile = 0;
	tileX = 0;
	tileY = 0;
	tmp = 0;
	idx = 0;
}

void Map::load(const char *filename)
{
	int tmp(0);

	std::ifstream level(filename);
	if(level.is_open())
	{
		while(level >> tmp) map.push_back(tmp);
	}

}

void Map::setTileTexture()
{
 	idx = 0;	
	for(int y = 0; y <= NB_TILE_HEIGHT; y++)
	{
		for(int x = 0; x <= NB_TILE_WIDTH; x++)
		{
		tile.push_back(sf::Sprite(tileset));
		nTile = map[idx++];
		tileX = nTile % (tileset.getSize().x / TILESIZE);
		//Top left coordinate
		tileY =	nTile / (tileset.getSize().y / TILESIZE);	
			
		tile.back().setTextureRect(sf::IntRect(tileX * TILESIZE,tileY * TILESIZE,TILESIZE,TILESIZE));
		tile.back().setPosition(x * TILESIZE, y * TILESIZE); 
		}
	}
}

const std::vector<sf::Sprite>& Map::getTile()
{
	return tile;
}

const int& Map::getTileValue(const int& idx)
{//  RETURN THE VALUE OF THE TILE ASKED BY IDX
	return map[idx];
}

const int Map::getTileNumber()
{ // GET THE TILE NUMBER OF THE MAP
	return map.size();
}

void Map::draw(sf::RenderWindow& win)
{
	for(int t = 0; t < tile.size(); ++t)
	{
		win.draw(tile[t]);
	}
}
