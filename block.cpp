#include "block.hpp"

Blocks::Blocks():BLOCK_NB(5),NONE(0)
{
	texture.loadFromFile("Resources/Blocks.png");
	coords.push_back(sf::Vector2f(320,160));
	coords.push_back(sf::Vector2f(320,224));
	coords.push_back(sf::Vector2f(384,192));
	coords.push_back(sf::Vector2f(384,224));
	coords.push_back(sf::Vector2f(224,320));
	coords.push_back(sf::Vector2f(320,320));
	bPosition.x = 320;
	bPosition.y = 160;
	check = false;
	x = 0;
	y = 0;
}

void Blocks::init()
{
	// Set texture and position for each block
	for(int i=0; i < BLOCK_NB ;i++)
	{
			block.push_back(sf::Sprite());
			block[i].setTexture(texture);
			block[i].setTextureRect(sf::IntRect(0,64,TILESIZE,TILESIZE));
			block[i].setPosition(coords[i]);
		}
}


void Blocks::addBoundingBox(const int& idx)
{
	boundingBox.left = block[idx].getPosition().x; 
	boundingBox.top = block[idx].getPosition().y;
	boundingBox.width = TILESIZE;
	boundingBox.height = TILESIZE;
}

const std::vector<sf::Sprite>& Blocks::getBlocks()
{
	return block;
}

void Blocks::showMapInfo(const int& id,const std::vector<sf::Sprite> wallsVector)   /* TO REMOVE */
{
	std::cout << "ID ::  " << id << "\tBB.LEFT :: " << boundingBox.left << "\tBBTOP :: " 
		<< boundingBox.top << "\tWLEFT ::  " << wallsVector[id].getPosition().x 
		<< "\tWTOP ::  " << wallsVector[id].getPosition().y 
		<< "\t+ SIZE :: " << wallsVector[id].getPosition().x<< std::endl;
}

void Blocks::showInfo(const int& idx,Map& m)
{
	std::cout << "BLOCK :: "   << idx  << "\tLEFT :: " << block[idx].getPosition().x <<  
		"\tTOP :: " << block[idx].getPosition().y << "\t FTILE_X :: " <<
		m.getTile()[343].getPosition().x << "\t FTILE_Y :: " << m.getTile()[343].getPosition().y <<
		std::endl;
}

bool Blocks::checkDestVector(const int& idx)
{
	for(int i=0; i <= dest.size(); i++)
	{
		if(!dest.empty())
		if(dest[i] == idx) { return true; }
	}

	return false;
}

bool Blocks::checkFinalPosition(Map& map,const int& idx)
{
	for(int fTile=0; fTile <= map.getTileNumber();fTile++)
	{
		if(map.getTileValue(fTile) == 3) {
			if(block[idx].getPosition().x == map.getTile()[fTile].getPosition().x &&
					block[idx].getPosition().y  ==  map.getTile()[fTile].getPosition().y)
			{
				std::cout << "ADD BLOCK::  " << idx  << std::endl;
			std::cout << dest.size() << std::endl;
				if(!checkDestVector(idx)) dest.push_back(idx);
			}
			if(dest.size() == BLOCK_NB) return true;
		}
	}

	return false;
}

const std::string Blocks::nextPositionIsABlock(const int& idx,const std::string& direction)
{
	//showInfo(idx);
	for(int b = 0; b <= block.size(); b++)
	{
		if(block[idx].getPosition().y == block[b].getPosition().y + block[b].getGlobalBounds().height &&
				block[idx].getPosition().x == block[b].getPosition().x && direction == "UP")
			return "BLOCKUP";
		if(block[idx].getPosition().y + block[idx].getGlobalBounds().height == block[b].getPosition().y &&
				block[idx].getPosition().x == block[b].getPosition().x && direction == "DOWN")
			return "BLOCKDOWN";
		if(block[idx].getPosition().x == block[b].getPosition().x + block[b].getGlobalBounds().width &&
				block[idx].getPosition().y == block[b].getPosition().y && direction == "LEFT")
			return "BLOCKLEFT";
		if(block[idx].getPosition().x + block[idx].getGlobalBounds().width == block[b].getPosition().x && 
				block[idx].getPosition().y == block[b].getPosition().y && direction == "RIGHT")
			return "BLOCKRIGHT";
	}

	return "NULL";
}

const std::string Blocks::checkNextPosition(const std::vector<sf::Sprite> wallsVector,Map& map,const std::string& direction,const int& idx)
{
	for(int wallID = 0; wallID <= map.getTileNumber(); wallID++)
	{
		addBoundingBox(idx);
		if(map.getTileValue(wallID) == 1) {
			if(direction == "LEFT") {
				if(boundingBox.left == wallsVector[wallID].getPosition().x +
						wallsVector[wallID].getGlobalBounds().width && 
						boundingBox.top == wallsVector[wallID].getPosition().y) {
					return "BLOCKLEFT";
				}
			}
			if(direction == "RIGHT") { 
				if(boundingBox.left + boundingBox.width == wallsVector[wallID].getPosition().x &&
						boundingBox.top == wallsVector[wallID].getPosition().y) {
					return "BLOCKRIGHT";
				}
			}
			if(direction == "UP" ) {
				if(boundingBox.top == wallsVector[wallID].getPosition().y + 
						wallsVector[wallID].getGlobalBounds().height && 
						boundingBox.left == wallsVector[wallID].getPosition().x){
					return "BLOCKUP";
				}
			}
			if(direction == "DOWN") {
				if(boundingBox.top + boundingBox.height == wallsVector[wallID].getPosition().y && 
						boundingBox.left == wallsVector[wallID].getPosition().x)  {
					return "BLOCKDOWN";
				}
			}

		}
	}
	return "PUSH";
}

void Blocks::move(Map& map,const int& idx,const std::string& direction)
{
	if(direction == "LEFT" ) block[idx].setPosition(sf::Vector2f(block[idx].getPosition().x - TILESIZE, 
				block[idx].getPosition().y));
	if(direction == "RIGHT") block[idx].setPosition(sf::Vector2f(block[idx].getPosition().x + TILESIZE,
				block[idx].getPosition().y));
	if(direction == "UP") 	block[idx].setPosition(sf::Vector2f(block[idx].getPosition().x,
				block[idx].getPosition().y - TILESIZE));
	if(direction == "DOWN") block[idx].setPosition(sf::Vector2f(block[idx].getPosition().x,
				block[idx].getPosition().y + TILESIZE));

}

void Blocks::display(sf::RenderWindow& window)
{
	for(int i= 0; i < block.size();i++)
	{
		window.draw(block[i]);
	}
}

