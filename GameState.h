#pragma once

#include<iostream>
#include<ctime>
#include<vector>
#include<math.h>
#include<sstream>
#include<map>

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Boom.h"
#include "Item.h"
#include "Ship.h"
#include "State.h"
#include "PauseMenu.h"
#include "ScoreBoard.h"
#include "GameOverMenu.h"
#include "Textbox.h"
#include "Obstacle.h"

class GameState
	: public State
{
private:
	bool s_check;

	FILE* fp;
	char temp[255];
	unsigned int score[6];
	string name[6];
	vector<pair<int, string>> userScore;

	sf::Font font;
	PauseMenu *pmenu;
	ScoreBoard scoreboard;
	Textbox* textbox1;
	sf::Text t_highscore;
	sf::Text e_name;
	
	//Gameover
	GameOverMenu* omenu;
	bool endGame;

	//Resoures
	std::map<std::string, sf::Texture*> textures;

	//Bullets
	std::vector<Bullet*> bullets;
	sf::Vector2f aimDir;
	sf::Vector2f aimDirNorm;
	sf::Vector2f playerCenter;

	//Obstacle
	std::vector<Obstacle*> obstacles;
	float spawnObstacleTime;
	float spawnObstacleTimeMax;
	unsigned spawnObstacleMaximum;
	float speedObs;
	float obs_up;

	//System
	int points;
	int currentLevel;
	float incrementTime;
	sf::Clock cl;
	sf::Clock clBoss;
	sf::Clock cl_s;

	//Sound audio
	std::map<std::string, sf::SoundBuffer> buffers;
	sf::Sound endGameSounds;
	sf::Sound enemyDeadSound;
	sf::Sound fireSound;
	sf::Sound s_blueBall;
	sf::Sound s_heal;
	sf::Sound s_obs;

	//Soundtrack
	sf::Music music;
		
	//Ship
	float numberShipMax;
	float numberShip;
	float positionShip_x;
	float positionShip_y;
	std::vector<Ship*> ships;

	//Player
	Player *player;
	std::string playerName;

	//Player GUI
	sf::Texture playerHpBarTexture;
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;
	sf::Texture playerSkillTorBarTexture;
	sf::RectangleShape playerSkillTornadoBar;
	sf::RectangleShape playerSkillTornadoBarBack;
	sf::RectangleShape playerSkillSuper;
	sf::RectangleShape playerSkillSuperBack;

	//Enemies
	bool bossIsDead;
	float spawnTimer;
	float spawnTimerMax;
	float maxEnemy;
	sf::RectangleShape enemyHpBar;
	sf::RectangleShape enemyHpBarBack;
	std::vector<Enemy*> enemies;

	//Item
	std::vector<Item*> items;
	float spawnItemTime;
	float spawnItemTimeMax;

	//boom Effect
	std::vector<Boom*> booms;
	std::vector<sf::Sprite*> bloods;

	//Pictures
	sf::RectangleShape g_frame[3];
	
	//GUI
	sf::Font guiFont;
	sf::Text guiText;
	sf::Text endGameText;
	sf::Text skillTimeText;
	sf::Text level;
	sf::RectangleShape guiBack;

	//Background
	sf::Sprite spaceBackground;
	sf::Texture spaceBackgroundTexture[3];

	void initKeybinds();
	void initVariables();
	void initWindow();
	void initSound();
	void initGameOverMenu();
	void initTexture();
	void initSpace();
	void initObstacle();
	void initShip();
	void initPlayer();
	void initFonts();
	void initText();
	void initItem();
	void initEnemy();
	void initPauseMenu();
	
public:
	//Constructors and Destructors
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	//Accessors
	const bool& getEndGame() const;
	const int getPoints() const;

	//Modifiers
	inline void getPlayerName(std::string playername) { this->playerName = playername; }
	//Functions
	const bool running() const;

	void spawnObstacle();
	void spawnEnemy();
	void spawnShip();
	void spawnItem();
	const int randomEnemyType() const;
	const int BulletType() const;

	void updatePlayer();
	void updateBulltes(sf::RenderWindow &window);

	void updateObstacle();
	void updateItem();
	void updateEnemy();
	void updateBoom();
	void updateCombat();
	
	
	void updatePausedMenuButtons();
	void updatePauseInput(const float& dt);
	void updateInput(const float& dt);

	void updateGameOverButton();
	void updateEvent(sf::Event input);
	void updateGui();
	void update(const float& dt);

	void renderSpace();
	void renderGui(sf::RenderTarget* target);
	void render(sf::RenderTarget* target = nullptr);
};