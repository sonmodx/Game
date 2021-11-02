#pragma once

#include<iostream>
#include<ctime>
#include<vector>
#include<sstream>
#include<map>

#include "Player.h"
//#include "SwagBall.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Boom.h"

class Game
{
private:
	//Window
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	bool endGame;
	sf::Event sfmlEvent;

	//Resoures
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;
	

	//System
	int points;

	//Player
	Player *player;

	//Player GUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	//Enemies
	float spawnTimer;
	float spawnTimerMax;
	float maxEnemy;
	std::vector<Enemy*> enemies;

	//boom Effect
	std::vector<Boom*> booms;

	//GUI
	sf::Font font;
	sf::Text guiText;
	sf::Text endGameText;

	//Background
	sf::Sprite spaceBackground;
	sf::Texture spaceBackgroundTexture;

	//std::vector<SwagBall> swagBalls;
	float spawnTimerMaxSwag;
	float spawnTimerSwag;
	int maxSwagBalls;

	
	void initVariables();
	void initWindow();
	void initTexture();
	void initSpace();
	void initPlayer();
	void initFonts();
	void initText();
	void initEnemy();
	
public:
	//Constructors and Destructors
	Game();
	~Game();

	//Accessors
	const bool& getEndGame() const;

	//Modifiers

	//Functions
	const bool running() const;
	void pollEvents();

	void spawnEnemy();
	const int randomEnemyType() const;

	void spawnSwagBalls();
	const int randBallType() const;
	void updatePlayer();
	void updateCollision();
	void updateBulltes(sf::RenderWindow &window);
	void updateEnemy();
	void updateBoom();
	void updateCombat();
	
	void updateGui();
	void update();

	void renderSpace();
	void renderGui(sf::RenderTarget* target);
	void render();
};