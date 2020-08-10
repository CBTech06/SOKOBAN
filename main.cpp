/* 
 *
 *  				SOKOBAN - WRITTEN IN C++ / SFML
 *			BY BOURGEOIS CHRISTOPHE  - STARTED 16/01/2019
*/

#include "main.hpp"
#include <sstream>

Game::Game():GAMESPEED(0.15)
{
	window.create(sf::VideoMode(1024,600),"Dev", sf::Style::Resize);	
	window.setFramerateLimit(5);
	titleTexture.loadFromFile("Resources/Title.png");
	title.setTexture(titleTexture);
	title.setPosition(700,20);
	sClearTexture.loadFromFile("Resources/ui.png");
	sClear.setTexture(sClearTexture);
	sClear.setTextureRect(sf::IntRect(0,0,343,273));
	sClear.setPosition(300,100);

}

std::vector<int>& Game::loadBlockInfo(const char* file)
{
		doc.LoadFile(file);	
		tinyxml2::XMLElement* root = doc.FirstChildElement("block_info");
		if(root) {
			for(const tinyxml2::XMLElement* e = root->FirstChildElement("block1_x"); e != NULL ;
				e = e->NextSiblingElement())
					{
					const char* value = e->GetText();
					tmp.push_back(std::stoi(value));
					}
		}
	
	return tmp;
}

void Game::getMapInformation(Map& map)
{
	wallsVector = map.getTile();
}

void Game::getBlockInformation(Blocks& blocks)
{
	blocksVector = blocks.getBlocks();
}

void Game::loop()
{
	Map map;
 	Blocks blocks;
	Player player;
	
	map.load("Map/map1.txt");
	map.setTileTexture();	
	blocks.init();
	while(window.isOpen())
	{
		while(window.pollEvent(event))
		{
			if(event.type == event.KeyPressed)
			{
				if(event.key.code == sf::Keyboard::Escape)
					window.close();
			}
			if(event.type == sf::Event::Closed)
				window.close();
		}
		
		getMapInformation(map);
		getBlockInformation(blocks);	
		window.clear(sf::Color::White);
		map.draw(window);
		player.addBoundingBox(window);
		if(player.getState() == "NOT_WIN") player.event(map,blocks,*this);
		else {
			window.draw(sClear);
			std::cout << "WIIIINNNN" << std::endl; }
		blocks.display(window);
		player.display(window);
		window.draw(title);
		window.display();
	}
}

int main(int argc,char *argv[])
{
	Game game;

	game.loop();
}

