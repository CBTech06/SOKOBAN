#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "main.hpp"
#include "string.h"

class Game;

class Blocks
{
	private:
		//! This vector contains all blocks
		std::vector<sf::Sprite> block;
		std::vector<int> dest;
		//! contains each block coords 
		std::vector<sf::Vector2f> coords;
		sf::FloatRect blockOverlap;
		sf::Vector2f bPosition;
		sf::Sprite sprite;
		sf::Texture texture;
		sf::FloatRect boundingBox;
		const int BLOCK_NB;
		const int NONE;	
		int x;
		int y;
		int point;
		bool check;
	public:
		Blocks();	
		//! This function define texture and set position for each block 
		void init();
		void addBoundingBox(const int&);
		void showMapInfo(const int& var,const std::vector<sf::Sprite> wallsVector);   /* TO REMOVE */
		void showInfo(const int&,Map&);
		const std::string nextPositionIsABlock(const int&,const std::string&);
		const std::string checkNextPosition(const std::vector<sf::Sprite>,Map&,const std::string&,const int&);
		const std::vector<sf::Sprite>& getBlocks();
		bool strCompare(const char*,const char*);
		void showInformation(const sf::FloatRect&,std::vector<sf::Sprite>&);
		void move(Map&,const int& ,const std::string& );
		bool checkDestVector(const int&);
		bool checkFinalPosition(Map&,const int&);
		void display(sf::RenderWindow&);
};
#endif
