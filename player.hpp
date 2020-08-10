#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "map.hpp"
#include "block.hpp" 

class Blocks;
class Game;

class Player
{
	private:
		sf::Texture playerTexture;
		sf::Sprite player;
		sf::Vector2f position;
		sf::Vector2i anim;
		sf::FloatRect overlap;
		sf::FloatRect boundingBox;
		const int LEFT;
		const int RIGHT;
		const int UP;
		const int DOWN;
		int SPEED;
		const int PLAYER_WIDTH;
		const int PLAYER_HEIGHT;
		const int MAX_PLAYER_PER_ROW;
		const int TILESIZE;
		const float PLAYER_OFFSET;
		std::string dir;	
		std::string state;
		std::string gameState;
		int idx;
		int selectedBox;
		bool keyRepeat;
	public:
		Player();
		void showPlayerInformation(std::ostream&) const& ;
		void animate(const char* );
		void getMapInformation(Map&,Blocks&);
		void addBoundingBox(sf::RenderWindow&);
		bool checkCollision(Map&,std::vector<sf::Sprite>&,const char*);
		bool checkBoxesCollision(const std::vector<sf::Sprite>&,const std::string&);
		inline void setDir(const std::string& direction) { dir = direction;  }
		inline std::string& getDir() { return dir;}
		std::string& getState();
		void event(Map&,Blocks&,Game&);
		void move(Map&,Blocks&,Game&,const std::string&);
		void pushBlock(Map& ,Blocks&,const std::string&);
		void display(sf::RenderWindow&);
};

#endif
