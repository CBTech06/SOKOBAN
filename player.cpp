#include "player.hpp"

Player::Player():SPEED(32),PLAYER_WIDTH(30),PLAYER_HEIGHT(30),MAX_PLAYER_PER_ROW(90),PLAYER_OFFSET(0.5),TILESIZE(32),LEFT(32),RIGHT(96),UP(64),DOWN(0)
{
	playerTexture.loadFromFile("Resources/character.png");
	player.setTexture(playerTexture);
	player.setTextureRect(sf::IntRect(0,0,PLAYER_WIDTH,PLAYER_HEIGHT));
	position.x = 351;
	// [LV1] position.y = 127 [LV2]191
	position.y = 191;
	player.setPosition(position.x,position.y);
	boundingBox.width = 34;
	boundingBox.height = 34;
	anim.x = 0;
	anim.y = 0;
	idx = 0;
	dir="NONE";
	selectedBox = 0;
	gameState = "NOT_WIN";
}

void Player::animate(const char* animation)
{
	if(animation == "LEFT")	anim.y = LEFT;
	else if(animation == "RIGHT") anim.y = RIGHT;
	else if(animation == "UP") anim.y = UP;
	else if(animation == "DOWN") anim.y = DOWN;

	anim.x++;
	player.setTextureRect(sf::IntRect(anim.x * PLAYER_WIDTH,anim.y,PLAYER_WIDTH,PLAYER_HEIGHT));
	if(anim.x * PLAYER_WIDTH > MAX_PLAYER_PER_ROW) anim.x = 0;
}

void Player::addBoundingBox(sf::RenderWindow& win)
{       // ADD BOUNDINGBOX TO PLAYER TO CHECK COLLISION
	boundingBox.left = player.getPosition().x;
	boundingBox.top = player.getPosition().y ;
}

bool Player::checkCollision(Map& map,std::vector<sf::Sprite>& wallsVector,const char* direction)
{
	for(int i=0; i <= wallsVector.size();i++) {
		if(map.getTileValue(i) == 1) {
			if(boundingBox.intersects(wallsVector[i].getGlobalBounds(),overlap)){
				if(overlap.width > overlap.height) {
					if(overlap.contains(overlap.left,boundingBox.top))
					{
						if(direction == "UP") { return false; }
					}
					else { if(direction == "DOWN") return false; }
				}
				if(overlap.width < overlap.height) {
					if(overlap.contains(boundingBox.left + boundingBox.width - PLAYER_OFFSET,
								overlap.top + PLAYER_OFFSET)) 
					{
						if(direction == "RIGHT") return false;		
					}		
					else { if(direction == "LEFT"){ return false; } }
				}
			}
		}
	}
	return true;
}

std::ostream& operator<<(std::ostream& flux,Player const& p)
{
	p.showPlayerInformation(flux);
	return flux;
}

void Player::showPlayerInformation(std::ostream& flux) const& 
{
	flux << "L:   " << player.getGlobalBounds().left << "\tT:   " << player.getGlobalBounds().top;
}

void showInfo(const sf::Sprite& p,const sf::Sprite& b)
{
	std::cout << "Player X :: " << p.getPosition().x << "\tY :: " << p.getPosition().y <<
		"\tWIDTH :: " << p.getGlobalBounds().width <<"\tHEIGHT :: " << p.getGlobalBounds().height << 
		"\t Block X :: " << b.getPosition().x << "\tY :: " << b.getPosition().y <<
		"\tWIDTH :: " << b.getGlobalBounds().width <<"\tHEIGHT :: " << b.getGlobalBounds().height <<
		std::endl;
}

std::string& Player::getState()
{
	return gameState;
}

bool Player::checkBoxesCollision(const std::vector<sf::Sprite>& blocksVector,const std::string& direction)
{
	for(int i=0; i < blocksVector.size();i++)
	{
		if(boundingBox.intersects(blocksVector[i].getGlobalBounds()))
		{
			//			showInfo(player,blocksVector[i]);
			if(direction == "LEFT") {
				if((player.getPosition().y +1 ) == blocksVector[i].getPosition().y && 
						(player.getPosition().x + 1) == (blocksVector[i].getPosition().x )+
						(blocksVector[i].getGlobalBounds().width )) { selectedBox = i; return true; }
			}
			if(direction =="RIGHT") {
				if((player.getPosition().y +1) == blocksVector[i].getPosition().y && 
						((player.getPosition().x + player.getGlobalBounds().width +3)  ==
						 blocksVector[i].getPosition().x)) { selectedBox = i; return true; }
			}
			if(direction == "UP") {
				if(player.getPosition().y +1 == blocksVector[i].getPosition().y + 
						blocksVector[i].getGlobalBounds().height && 
						player.getPosition().x + 1 == blocksVector[i].getPosition().x) {
					selectedBox = i; return true; }
			}
			if(direction =="DOWN") {
				if((player.getPosition().y + player.getGlobalBounds().height +3)== 
						blocksVector[i].getPosition().y && 
						player.getPosition().x + 1 ==  blocksVector[i].getPosition().x) {
					selectedBox = i; return true; }
			}
		}
	}

	return false;
}

void Player::event(Map& map,Blocks& block,Game& game)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ) { dir = "LEFT"; }
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ) { dir = "RIGHT"; }
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ) { dir = "UP"; }
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ) { dir = "DOWN"; }
	else state = "NONE"; 	

	if(checkBoxesCollision(block.getBlocks(),dir)){ pushBlock(map,block,dir); }

	if(block.checkFinalPosition(map,selectedBox)) { gameState = "WIN"; }
	else { gameState = "NOT_WIN"; } 

	move (map,block,game,dir);

	dir = "NONE";
}

void Player::move(Map& map,Blocks& block,Game& game,const std::string& direction)
{
	if (state == "PUSH")  block.move(map,selectedBox,direction); 

	if(direction == "LEFT") {	
		animate("LEFT");	
		if (state != "BLOCKLEFT" && checkCollision(map,game.returnMapInformation(),"LEFT")) position.x -= SPEED;
	}
	else if(direction == "RIGHT")  {
		animate("RIGHT");
		if(state != "BLOCKRIGHT"&& checkCollision(map,game.returnMapInformation(),"RIGHT")) position.x += SPEED;
	}
	else if(direction == "UP") {
		animate("UP");
		if(state != "BLOCKUP" && checkCollision(map,game.returnMapInformation(),"UP"))position.y -= SPEED;
	}
	else if(direction =="DOWN")  {
		animate("DOWN");
		if(state != "BLOCKDOWN"&& checkCollision(map,game.returnMapInformation(),"DOWN")) position.y += SPEED;
	}
}

void Player::pushBlock(Map& map,Blocks& block,const std::string& direction)
{
	state = block.checkNextPosition(map.getTile(),map,getDir(),selectedBox);
	if(block.nextPositionIsABlock(selectedBox,direction) == "BLOCKUP") state = "BLOCKUP";
	else if(block.nextPositionIsABlock(selectedBox,direction) == "BLOCKLEFT") state = "BLOCKLEFT";
	else if(block.nextPositionIsABlock(selectedBox,direction) == "BLOCKDOWN") state = "BLOCKDOWN";
	else if(block.nextPositionIsABlock(selectedBox,direction) == "BLOCKRIGHT") state = "BLOCKRIGHT";
}

void Player::display(sf::RenderWindow& win)
{
	player.setPosition(position.x,position.y);
	win.draw(player);
}

