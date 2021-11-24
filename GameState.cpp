#define _CRT_SECURE_NO_WARNINGS
#include "GameState.h"

void GameState::initKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
	this->keybinds["MOVE_LEFT"] = this->supportedKeys->at("A");
	this->keybinds["MOVE_RIGHT"] = this->supportedKeys->at("D");
	this->keybinds["MOVE_UP"] = this->supportedKeys->at("W");
	this->keybinds["MOVE_DOWN"] = this->supportedKeys->at("S");
}

void GameState::initVariables()
{
	this->currentLevel = 1;
	this->incrementTime = 1.f;
	this->endGame = false;
	this->bossIsDead = true;
	this->spawnTimerMax = 10.f;
	this->spawnTimer = this->spawnTimerMax;
	this->points = 0;
}

void GameState::initWindow()
{
	this->window->setFramerateLimit(60);
}

void GameState::initSound()
{
	//Soundtrack
	this->music.openFromFile("sound/avenger.wav");
	this->music.play();
	this->music.setVolume(30);
	this->music.setLoop(true);

	this->buffers["S_OBS"].loadFromFile("sound/obs_attack.wav");
	this->buffers["S_HEAL"].loadFromFile("sound/potion.wav");
	this->buffers["S_BLUEBALL"].loadFromFile("sound/blueBall.wav");
	this->buffers["GAMEOVER"].loadFromFile("sound/gameOver.wav");
	this->buffers["FIRE"].loadFromFile("sound/shoot_fire.wav");
	if (!this->buffers["ENEMYDEAD"].loadFromFile("sound/fire.wav"))
		std::cout << "FAiled" << std::endl;

	this->s_blueBall.setBuffer(this->buffers["S_BLUEBALL"]);
	this->s_blueBall.setVolume(20.f);
	this->s_blueBall.setPitch(0.9);
	this->endGameSounds.setBuffer(this->buffers["GAMEOVER"]);
	this->enemyDeadSound.setBuffer(this->buffers["ENEMYDEAD"]);
	this->fireSound.setBuffer(this->buffers["FIRE"]);
	this->fireSound.setVolume(20.f);
	this->s_heal.setBuffer(this->buffers["S_HEAL"]);
	this->s_heal.setVolume(80.f);
	this->s_obs.setBuffer(this->buffers["S_OBS"]);
	this->s_obs.setVolume(50.f);

}

void GameState::initGameOverMenu()
{
	this->omenu = new GameOverMenu(this->window, this->font);

	this->omenu->addButton("ENTER", 700.0f, "Enter");
}

void GameState::initTexture()
{
	//Obstacle
	this->textures["OBSTACLE"] = new sf::Texture();
	this->textures["OBSTACLE"]->loadFromFile("img/obstacle.png");

	//Bullet
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("img/fire.png");
	this->textures["BLUEBALL"] = new sf::Texture();
	if (!this->textures["BLUEBALL"]->loadFromFile("img/blueBall.png"))
		std::cout << "can't load this bullet";

	this->textures["BLUEBALL_PIC"] = new sf::Texture();
	this->textures["BLUEBALL_PIC"]->loadFromFile("img/blueBall.png");
	
	
	this->textures["TORNADO"] = new sf::Texture();
	this->textures["TORNADO"]->loadFromFile("img/Tornado.png");
	this->textures["SUPER"] = new sf::Texture();
	this->textures["SUPER"]->loadFromFile("img/superSkill.png");

	//Boom
	this->textures["BOOM"] = new sf::Texture();
	this->textures["BOOM"]->loadFromFile("img/boom3.png");

	//Blood
	this->textures["BLOOD"] = new sf::Texture();
	this->textures["BLOOD"]->loadFromFile("img/blood.png");

	//Ship
	this->textures["SHIP"] = new sf::Texture();
	this->textures["SHIP"]->loadFromFile("img/spaceShip.png");

	//Picture blue ball
	this->g_frame[0].setTexture(this->textures["BLUEBALL_PIC"]);
	this->g_frame[0].setSize(sf::Vector2f(100, 100));
	this->g_frame[0].setTextureRect(sf::IntRect(
		0, 0,
		this->textures["BLUEBALL_PIC"]->getSize().x / 4.f,
		this->textures["BLUEBALL_PIC"]->getSize().y)
	);
	this->g_frame[0].setPosition(this->window->getSize().x / 2.f - 45.f,
		this->window->getSize().y - this->g_frame[0].getGlobalBounds().height - 45.f);

	this->g_frame[1].setTexture(this->textures["SUPER"]);
	this->g_frame[1].setSize(sf::Vector2f(200, 200));
	this->g_frame[1].setTextureRect(sf::IntRect(
		4 *this->textures["SUPER"]->getSize().x / 6.f, 0,
		this->textures["SUPER"]->getSize().x / 6.f ,
		this->textures["SUPER"]->getSize().y / 3.f)
	);
	this->g_frame[1].setPosition(300.f,
		this->window->getSize().y - this->g_frame[1].getGlobalBounds().height);

	this->g_frame[2].setTexture(this->textures["TORNADO"]);
	this->g_frame[2].setSize(sf::Vector2f(150, 150));
	this->g_frame[2].setTextureRect(sf::IntRect(
		0, 2*this->textures["TORNADO"]->getSize().y / 4.f,
		this->textures["TORNADO"]->getSize().x / 5.f ,
		this->textures["TORNADO"]->getSize().y / 4.f)
	);
	this->g_frame[2].setPosition(this->window->getSize().x - 300.f - this->g_frame[2].getGlobalBounds().width,
		this->window->getSize().y - this->g_frame[2].getGlobalBounds().height - 15.f);
	//Item
	this->textures["HEAL"] = new sf::Texture();
	this->textures["HEAL"]->loadFromFile("img/potion.png");

	//gui Back
	this->textures["GUI_BACK"] = new sf::Texture();
	this->textures["GUI_BACK"]->loadFromFile("img/guiBack.jpg");
}

void GameState::initSpace()
{
	if (!this->spaceBackgroundTexture[0].loadFromFile("img/spaceBackground.png"))
		std::cout << "This background load failed" << std::endl;
	if (!this->spaceBackgroundTexture[1].loadFromFile("img/spaceScore.jpg"))
		std::cout << "This background load failed" << std::endl;
	this->spaceBackground.setTexture(this->spaceBackgroundTexture[0]);
	this->spaceBackground.setScale(1.5f,1.5f);
}

void GameState::initObstacle()
{
	this->speedObs = 10.f;
	this->obs_up = 1.f;
	this->spawnObstacleTime = 0.f;
	this->spawnObstacleTimeMax = 100.f;
	this->spawnObstacleMaximum = 1;
}

void GameState::initShip()
{
	this->numberShip = 0.f;
	this->numberShipMax = 4.f;
	this->positionShip_x = 20.f;
	this->positionShip_y = 100.f;
}

void GameState::initPlayer()
{
	this->player = new Player(150.f,40.f);
}

void GameState::initFonts()
{
	if (!this->guiFont.loadFromFile("Fonts/PixellettersFull.ttf"))
	{
		std::cout << " ! ERROR::GAME::INITFONTS::COULD NOT LOAD PixellettersFull.ttf" << "\n";
	}

	if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf"))
	{
		std::cout << " ! ERROR::GAME::INITFONTS::COULD NOT LOAD PixellettersFull.ttf" << "\n";
	}
}

void GameState::initText()
{
	//Gui text init
	this->guiText.setFont(this->guiFont);
	this->guiText.setFillColor(sf::Color::White);
	this->guiText.setCharacterSize(32);

	//End game text
	this->endGameText.setFont(this->guiFont);
	this->endGameText.setFillColor(sf::Color::Red);
	this->endGameText.setCharacterSize(60);
	this->endGameText.setOutlineThickness(10);
	this->endGameText.setOutlineColor(sf::Color::Black);
	this->endGameText.setString("YOU ARE DEAD, EXIT THE GAME!");
	
	//Init Player GUI
	this->playerHpBarTexture.loadFromFile("img/HpBar.png");
	this->playerHpBar.setTexture(&this->playerHpBarTexture);
	this->playerHpBar.setSize(sf::Vector2f(300.f, 40.f));
	this->playerHpBar.setPosition(sf::Vector2f(10.f, 10.f));
	
	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));

	//Init Enemy GUI
	this->enemyHpBar.setSize({ 50.f,8.f });
	this->enemyHpBar.setFillColor(sf::Color::White);

	this->enemyHpBarBack = this->enemyHpBar;
	this->enemyHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));

	//Skill Time 
	//Blue ball
	this->skillTimeText.setFont(this->guiFont);
	this->skillTimeText.setCharacterSize(40);
	this->skillTimeText.setFillColor(sf::Color::Yellow);

	//Tornado
	this->playerSkillTornadoBar.setSize(sf::Vector2f(100.f, 10.f));
	this->playerSkillTornadoBar.setFillColor(sf::Color(0, 255, 255));
	this->playerSkillTornadoBar.setPosition(sf::Vector2f(this->g_frame[2].getPosition().x + this->g_frame[2].getGlobalBounds().width,
		this->g_frame[2].getPosition().y +this->g_frame[2].getGlobalBounds().height / 2.f)
	);

	this->playerSkillTornadoBarBack = this->playerSkillTornadoBar;
	this->playerSkillTornadoBarBack.setFillColor(sf::Color(25, 25, 25, 200));

	//Super
	this->playerSkillSuper.setSize(sf::Vector2f(100.f, 10.f));
	this->playerSkillSuper.setFillColor(sf::Color::Magenta);
	this->playerSkillSuper.setPosition(sf::Vector2f(this->g_frame[1].getPosition().x + this->g_frame[1].getGlobalBounds().width,
		this->g_frame[1].getPosition().y + this->g_frame[1].getGlobalBounds().height / 2.f)
	);

	this->playerSkillSuperBack = this->playerSkillSuper;
	this->playerSkillSuperBack.setFillColor(sf::Color(25, 25, 25, 200));


	//Level
	this->level.setFont(this->guiFont);
	this->level.setCharacterSize(20);
	this->level.setFillColor(sf::Color::White);

	//Text endgame
	e_name.setFont(this->font);
	e_name.setPosition({ 850 , 450});
	e_name.setCharacterSize(60);
	e_name.setString("|---Name---|");
}

void GameState::initItem()
{
	this->spawnItemTime = 0.f;
	this->spawnItemTimeMax = 500.f;
}

void GameState::initEnemy()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
	this->maxEnemy = 5.f;
}

void GameState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);

	this->pmenu->addButton("QUIT", 800.f, "Quit");
}

//Constructors and Destructors
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initKeybinds();
	this->initVariables(); 
	this->initWindow();
	this->initSpace();
	this->initSound();
	this->initTexture();
	this->initShip();
	this->initObstacle();
	this->initPlayer();
	this->initItem();
	this->initEnemy();
	this->initFonts();
	this->initText();
	this->initGameOverMenu();
	this->initPauseMenu();

	//guiBack
	this->guiBack.setTexture(this->textures["GUI_BACK"]);
	this->guiBack.setSize(sf::Vector2f(this->window->getSize().x, 200.f));
	this->guiBack.setFillColor(sf::Color(100, 130, 200, 255));
	this->guiBack.setPosition(sf::Vector2f(0.f,this->window->getSize().y -200.f));

	//Enter a name
	textbox1 = new Textbox(50, sf::Color::White, true);
	textbox1->setFont(font);
	textbox1->setPosition(
		{ this->window->getSize().x / 2.f - 60.f,
		this->window->getSize().y / 2.f }
	);

	t_highscore.setFont(font);
	this->fp = fopen("config/Score.txt", "r");
	for (int i = 0; i < 5; i++)
	{
		(void)fscanf(fp, "%s", &temp);
		name[i] = temp;
		(void)fscanf(fp, "%d", &score[i]);
		this->userScore.push_back(make_pair(this->score[i], this->name[i]));
	}
	t_highscore.setString("HIGHT SCORE " + std::to_string(score[0]));
	t_highscore.setPosition({ this->window->getSize().x /2.f, 10 });
}

GameState::~GameState()
{
	delete this->player;
	delete this->pmenu;
	delete this->omenu;

	//delete texture
	for (auto& i : this->textures)
	{
		delete i.second;
	}

	//delete bullet
	for (auto *i : this->bullets)
	{
		delete i;
	}

	//delete enemies
	for (auto* i : this->enemies)
	{
		delete i;
	}
}

const bool& GameState::getEndGame() const
{
	return this->endGame;
}

const int GameState::getPoints() const
{
	return this->points;
}

//Functions
const bool GameState::running() const
{
	return this->window->isOpen() /*&& this->endGame == false*/;
}

void GameState::spawnObstacle()
{
	this->spawnObstacleTime+= this->obs_up;
	if (this->spawnObstacleTime >= this->spawnObstacleTimeMax)
	{
		if (this->obstacles.size() < this->spawnObstacleMaximum)
		{

			float randomSpawn = static_cast<float>(rand() % this->window->getSize().y) - 300.f;
			if (randomSpawn < this->window->getSize().y - 300.f && randomSpawn > 0.f)
			{
				this->obstacles.push_back(new Obstacle(this->textures["OBSTACLE"],
					this->window->getSize().x,
					static_cast<float>(rand() % this->window->getSize().y) - 300.f,
					this->speedObs, 20.f));
			}
			if (this->currentLevel >= 5)
			{
				this->speedObs = 20.f;
				this->obs_up = 1.5f;
			}
			else if (this->currentLevel >= 10)
			{
				this->speedObs = 30.f;
				this->obs_up = 10.f;
				this->spawnObstacleMaximum = 2;
			}
		}
	}
}

void GameState::spawnEnemy()
{
	//Spawning
	if (this->spawnTimer < this->spawnTimerMax)
	{
		this->spawnTimer += this->incrementTime;
	}
	else
	{
		float time = cl.getElapsedTime().asMilliseconds();
		float timeBoss = clBoss.getElapsedTime().asMilliseconds();
			if (this->enemies.size() < this->maxEnemy )
			{
			
				float randomSpawn = static_cast<float>(rand() % this->window->getSize().y) - 250.f;	
				if (randomSpawn < this->window->getSize().y - 300.f &&randomSpawn > 0.f && this->bossIsDead)
				{
					this->enemies.push_back(new Enemy(this->window->getSize().x, randomSpawn, this->randomEnemyType()));
					this->spawnTimer = 0.f;
	
					if (time >= 10000)
					{
						this->currentLevel++;
						this->maxEnemy += 2.f;
						this->incrementTime += 0.5f;
						this->spaceBackground.setTexture(this->spaceBackgroundTexture[0]);
						cl.restart();
					}
				}
				else if (timeBoss >= 20000 && this->bossIsDead)
				{
					this->bossIsDead = false;
					this->enemies.push_back(new Enemy(this->window->getSize().x, this->window->getSize().y/2.f -100.f, EnemyTypes::BOSS));
					this->spaceBackground.setTexture(this->spaceBackgroundTexture[1]);
				}
			}
	}
}

void GameState::spawnShip()
{
	if (this->numberShip < this->numberShipMax)
	{
		this->numberShip += 1.f;
		this->ships.push_back(new Ship(this->textures["SHIP"], this->positionShip_x, this->positionShip_y));
		this->positionShip_y += 200.f;
	}
}

void GameState::spawnItem()
{
	this->spawnItemTime++;
	if (this->spawnItemTime >= this->spawnItemTimeMax)
	{
		this->items.push_back(new Item(this->textures["HEAL"],
			 this->window->getSize().x,
			static_cast<float>(rand() % (this->window->getSize().y - 250 ))
		));
		this->spawnItemTime = 0.f;
	}

}

const int GameState::randomEnemyType() const
{
	int type = EnemyTypes::DEFAULT;
	int random = rand() % 100 + 1;
	if (random > 90 && random <= 100)
		type = EnemyTypes::HARD;
	else if (random >= 60 && random <= 80)
		type = EnemyTypes::MEDIUM;

	return type;
}

const int GameState::BulletType() const
{
	int type = BulletTypes::FIRE;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		type = BulletTypes::LASER;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		type = BulletTypes::TORNADO;
	}
	return type;
}

void GameState::updatePlayer()
{
	this->player->update(this->window);
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack() && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->bullets.push_back(new Bullet(this->textures["BULLET"],
			this->player->getPosition().x + this->player->getBounds().width / 2.f,
			this->player->getPosition().y + this->player->getBounds().height / 2.f,
			1.f, 0.f, 5.f, 10, 0));
		this->fireSound.play();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && this->player->canSkill() )
	{
		this->bullets.push_back(new Bullet(this->textures["BLUEBALL"],
			this->player->getPosition().x + this->player->getBounds().width / 2.f,
			this->player->getPosition().y,
			aimDirNorm.x, aimDirNorm.y, 50.f, 50, 1));
		this->s_blueBall.play();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && this->player->canSkillTornado())
	{
		if (this->player->getDirTor() == 1)
		{
			this->bullets.push_back(new Bullet(this->textures["TORNADO"],
				this->player->getPosition().x + this->player->getBounds().width / 2.f,
				this->player->getPosition().y,
				1.f, 1.f, 10.f, 100, 2));
		}
		else if (this->player->getDirTor() == -1)
		{
			this->bullets.push_back(new Bullet(this->textures["TORNADO"],
				this->player->getPosition().x + this->player->getBounds().width / 2.f,
				this->player->getPosition().y,
				1.f, -1.f, 10.f, 100, 2));
		}
			this->bullets.push_back(new Bullet(this->textures["TORNADO"],
				this->player->getPosition().x + this->player->getBounds().width / 2.f,
				this->player->getPosition().y,
				1.f, 0.f, 10.f, 100, 2));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && this->player->canSkillSuper())
	{
		this->bullets.push_back(new Bullet(this->textures["SUPER"],
			this->player->getPosition().x + this->player->getBounds().width / 2.f,
			this->player->getPosition().y,
			1.f, 0.f, 30.f, 300, 3));
	}
	if (this->player->getBounds().intersects(this->guiBack.getGlobalBounds()))
		this->player->setPosition(sf::Vector2f(this->player->getPosition().x,this->window->getSize().y - 200.f - this->player->getBounds().height));
	this->BulletType();
	 for (int h =0 ;h< this->ships.size();h++)
	 {
		 if (this->player->getBounds().intersects(this->ships[h]->getBounds()))
		 {
			 sf::Vector2f position = sf::Vector2f(this->ships[h]->getBounds().width, this->player->getPosition().y);
			 this->player->setPosition(position);
		 }
			 
	 }
	 //Skill dalay
	 this->skillTimeText.setString(std::to_string(this->player->getSkill()));
	 //Check Hp player
	 if (this->player->getHp() <= 0)
	 {
		 this->endGameSounds.play();
		 this->endGame = true;
	 }
	
}

void GameState::updateBulltes(sf::RenderWindow &window)
{
	playerCenter = sf::Vector2f(this->player->getPosition().x, this->player->getPosition().y);
	aimDir = mousePosView - playerCenter; 
	aimDirNorm.x = aimDir.x / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
	aimDirNorm.y = aimDir.y / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update(this->BulletType());

		if (bullet->getBound().width + bullet->getBound().left > window.getSize().x)
		{
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}
		++counter;
	}

}

void GameState::updateObstacle()
{
	unsigned counter = 0;
	for (auto* obstacle : this->obstacles)
	{
		//Edit again
		obstacle->update();
		if (obstacle->getBounds().intersects(this->player->getBounds()))
		{
			this->obstacles.erase(this->obstacles.begin() + counter);
			this->player->loseHp(obstacle->getDamage());
			this->s_obs.play();
		}
		else if (obstacle->getBounds().left + obstacle->getBounds().width <= 0.f)
		{
			this->obstacles.erase(this->obstacles.begin() + counter);
		}
		++counter;
	}
}

void GameState::updateItem()
{
	unsigned counter = 0;
	for (auto* item : this->items)
	{
		//Edit again
		item->update(-1.f, 0.f);
		if (item->getBounds().intersects(this->player->getBounds()))
		{
			this->items.erase(this->items.begin() + counter);
			this->player->gainHealth(20.f);
			this->s_heal.play();
		}
		else if (item->getBounds().left + item->getBounds().width <= 0.f)
		{
			this->items.erase(this->items.begin() + counter);
		}
		++counter;
	}
}

void GameState::updateEnemy()
{
	//Update
	unsigned counter = 0;
	for (auto* enemy : this->enemies)
	{
		enemy->update(this->randomEnemyType());
		if (enemy->getBounds().left +enemy->getBounds().width <= 0.f)
		{
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}
		else if (enemy->getBounds().intersects(this->player->getBounds()))
		{
			this->booms.push_back(new Boom(this->textures["BOOM"],
				enemy->getPosition().x - enemy->getBounds().width / 2.f,
				enemy->getPosition().y - enemy->getBounds().height,
				0
			));
			this->booms.push_back(new Boom(this->textures["BLOOD"],
				this->player->getPosition().x + this->player->getBounds().width / 2.f,
				this->player->getPosition().y ,
				1
			));
			this->enemyDeadSound.play();
			this->player->loseHp(this->enemies.at(counter)->getDamage());
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}
		++counter;
	}
}

void GameState::updateBoom()
{
	for (int j = 0; j < this->booms.size(); ++j)
	{
		booms[j]->update();
		if (booms[j]->getType() == 0)
		{
			if (booms[j]->getAnimationFrame_x() >= 7 && booms[j]->getAnimationFrame_y() >= 7)
			{
				delete this->booms[j];
				this->booms.erase(this->booms.begin() + j);
			}
		}
		else if (booms[j]->getType() == 1)
		{
			 if (booms[j]->getAnimationFrame_x() >= 3 && booms[j]->getAnimationFrame_y() >= 3)
			{
				delete this->booms[j];
				this->booms.erase(this->booms.begin() + j);
			}
		}
	}
}

void GameState::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_delete = false;
		for (int k = 0; k < this->bullets.size() && enemy_delete == false; k++)
		{
			if (this->bullets[k]->getBound().intersects(this->enemies[i]->getBounds()))
			{
				
				//Check HP enemy
				this->enemies[i]->loseHp(this->bullets[k]->getDamage());
				this->bullets[k]->loseDamage(this->enemies[i]->getHpMax());
				 if (this->bullets[k]->getDamage() <= 0.f)
				{
					this->bullets.erase(this->bullets.begin() + k);
				}
				
				if (this->enemies[i]->getHp() <= 0.f)
				{
					this->booms.push_back(new Boom(this->textures["BOOM"],
						this->enemies[i]->getPosition().x - this->enemies[i]->getBounds().width / 2.f,
						this->enemies[i]->getPosition().y - this->enemies[i]->getBounds().height,
						0
					));
					if (enemies[i]->getType() == EnemyTypes::BOSS)
					{
						this->bossIsDead = true;
						this->points += 5000;
						clBoss.restart();
					}
					switch (this->enemies[i]->getType())
					{
					case EnemyTypes::DEFAULT:
						this->points += 10;
						break;
					case EnemyTypes::MEDIUM:
						this->points += 20;
						break;
					case EnemyTypes::HARD:
						this->points += 50;
						break;
					}
					
					this->enemies.erase(this->enemies.begin() + i);
					this->enemyDeadSound.play();
					enemy_delete = true;
				}
			}	
		}
		for (int s = 0; s < this->ships.size() && enemy_delete == false; s++)
		{

			if (this->ships[s]->getBounds().intersects(this->enemies[i]->getBounds()))
			{
				this->ships.erase(this->ships.begin() + s);
				this->enemies.erase(this->enemies.begin() + i);
				this->numberShip--;
				this->endGameSounds.play();
				this->endGame = true;
				enemy_delete = true;
			}
		}
	}
}

void GameState::updatePausedMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
	{
		this->endState();
	}
}

void GameState::updatePauseInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
		if (!this->paused)
		{
			this->pauseState();
		}
		else
		{
			this->unpauseState();
		}
	}
}

void GameState::updateInput(const float& dt)
{
	//Update player input
	
}

void GameState::updateGameOverButton()
{
	if (this->omenu->isButtonPressed("ENTER"))
	{
		scoreboard.WriteFile(textbox1->getText(), this->points);
		this->endState();
	}
}

void GameState::updateEvent(Event input)
{
	if (this->endGame)
	{
		textbox1->typedOn(input);
	}
}

void GameState::updateGui()
{
	std::stringstream ss;

	ss << " - Points: " << this->points << "\n";

	this->guiText.setString(ss.str());
	this->guiText.setPosition(this->window->getSize().x-this->guiText.getGlobalBounds().width,0.f);

	//Update player hp
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent,this->playerHpBar.getSize().y));
	
	//Update skill cool down
	float skillTornadoPercent = static_cast<float>(this->player->getSkillTornado()) / this->player->getSkillTornadoMax();
	this->playerSkillTornadoBar.setSize(sf::Vector2f(100.f * skillTornadoPercent, this->playerSkillTornadoBar.getSize().y));

	float skillSuperPercent = static_cast<float>(this->player->getSkillSuper()) / this->player->getSkillSuperMax();
	this->playerSkillSuper.setSize(sf::Vector2f(100.f * skillSuperPercent, this->playerSkillSuper.getSize().y));

	this->skillTimeText.setPosition(sf::Vector2f(this->window->getSize().x/ 2.f + 20.f, this->window->getSize().y - 50.f));
	this->skillTimeText.setFillColor(sf::Color::Yellow);
	if (this->skillTimeText.getString() == "100")
	{
		this->skillTimeText.setFillColor(sf::Color::Green);
		this->skillTimeText.setString("READY");
	}

	//Update End game
	this->endGameText.setPosition(sf::Vector2f(
		this->window->getSize().x / 2.f - this->endGameText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->endGameText.getGlobalBounds().height / 2.f
	));

	//Level
	std::stringstream lv;
	lv << "Level " << this->currentLevel << "\n";
	this->level.setString(lv.str());
	this->level.setPosition(this->window->getSize().x - this->level.getGlobalBounds().width, 40.f);

}

void GameState::update(const float& dt)
{
	this->window->setMouseCursorVisible(true);
	this->updateMousePosition();
	this->updateKeytime(dt);
	this->updatePauseInput(dt);
	
	if (this->endGame == false && !this->paused)
	{
	
		this->spawnShip();
		this->spawnEnemy();
		this->spawnObstacle();
		this->spawnItem();
		this->updateBulltes(*this->window);
		this->updatePlayer();
		this->updateItem();
		this->updateObstacle();
		this->updateEnemy();
		this->updateCombat();
		this->updateBoom();
		this->updateGui();
	}
	if (this->paused)
	{
		this->pmenu->update(this->mousePosView);
		this->updatePausedMenuButtons();
	}
	if (this->endGame)
	{
		this->omenu->update(this->mousePosView);
		this->updateGameOverButton();
		std::cout << "Gameover! " << "\n";
	}
}

void GameState::renderSpace()
{
	this->window->draw(this->spaceBackground);
}

void GameState::renderGui(sf::RenderTarget* target)
{
	target->draw(this->guiBack);
	target->draw(this->guiText);
	target->draw(this->level);
	target->draw(this->playerHpBarBack);
	target->draw(this->playerHpBar);
	target->draw(this->playerSkillTornadoBar);
	target->draw(this->playerSkillTornadoBarBack);
	target->draw(this->playerSkillSuper);
	target->draw(this->playerSkillSuperBack);
	target->draw(this->skillTimeText);
	target->draw(this->t_highscore);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	
		//Render background
		this->renderSpace();

		//Render stuff
		this->player->render(this->window);

		//Render gui
		this->renderGui(this->window);

		//BLUE BALL
		this->window->draw(this->g_frame[0]);

		//SUPER
		this->window->draw(this->g_frame[1]);

		//TORNADO
		this->window->draw(this->g_frame[2]);

		for (auto* bullet : this->bullets)
		{
			bullet->render(this->window);
		}

		for (auto* item : this->items)
		{
			item->render(this->window);
		}

		for (auto* enemy : this->enemies)
		{
			this->enemyHpBar.setPosition(enemy->getPosition().x +this->enemyHpBar.getGlobalBounds().width -20.f,
				enemy->getPosition().y );
			this->enemyHpBarBack.setPosition(enemy->getPosition().x + this->enemyHpBar.getGlobalBounds().width - 20.f,
				enemy->getPosition().y);
			float enemyPer = static_cast<float>(50 *enemy->getHp()) / enemy->getHpMax();
			this->enemyHpBar.setSize(sf::Vector2f(enemyPer,this->enemyHpBar.getSize().y ));
			enemy->render(this->window);
			this->window->draw(this->enemyHpBar);
			this->window->draw(this->enemyHpBarBack);
		}

		for (auto* boom : this->booms)
		{
			boom->render(this->window);
		}

		for (auto* ship : this->ships)
		{
			ship->render(this->window);
		}

		for (auto* obstacle : this->obstacles)
		{
			obstacle->render(this->window);
		}

		//Render end text
		if (this->endGame)
		{
			this->omenu->render(this->window);
			this->textbox1->drawTo(this->window);
			this->window->draw(e_name);
		}

		//Render pauseMenu
		if (this->paused)
		{
			this->pmenu->render(target);
		}
}