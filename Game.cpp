#include "Game.h"

void Game::initVariables()
{
	this->endGame = false;
	this->spawnTimerMax = 10.f;
	this->spawnTimer = this->spawnTimerMax;
	this->maxSwagBalls = 10;
	this->points = 0;
}

void Game::initWindow()
{
	this->videoMode = sf::VideoMode(800, 600);
	this->window = new sf::RenderWindow(this->videoMode, "Game", sf::Style::Default);
	this->window->setFramerateLimit(60);
}

void Game::initTexture()
{
	//Bullet
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("img/fire.png");

	//Boom
	this->textures["BOOM"] = new sf::Texture();
	this->textures["BOOM"]->loadFromFile("img/boom3.png");
}

void Game::initSpace()
{
	if (!this->spaceBackgroundTexture.loadFromFile("img/spaceBackground.png"))
		std::cout << "This background load failed" << std::endl;
	this->spaceBackground.setTexture(this->spaceBackgroundTexture);
	this->spaceBackground.setScale(1.5f,1.5f);
}

void Game::initPlayer()
{
	this->player = new Player();

}

void Game::initFonts()
{
	if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf"))
	{
		std::cout << " ! ERROR::GAME::INITFONTS::COULD NOT LOAD PixellettersFull.ttf" << "\n";
	}
}

void Game::initText()
{
	//Gui text init
	this->guiText.setFont(this->font);
	this->guiText.setFillColor(sf::Color::White);
	this->guiText.setCharacterSize(32);

	//End game text
	this->endGameText.setFont(this->font);
	this->endGameText.setFillColor(sf::Color::Red);
	this->endGameText.setCharacterSize(60);
	this->endGameText.setString("YOU ARE DEAD, EXIT THE GAME!");
	this->endGameText.setPosition(sf::Vector2f(
		this->window->getSize().x /2.f - this->endGameText.getGlobalBounds().width / 2.f,
		this->window->getSize().y /2.f - this->endGameText.getGlobalBounds().height / 2.f
	));
	

	//Init Player GUI
	this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(sf::Vector2f(20.f, 60.f));

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
}

void Game::initEnemy()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
	this->maxEnemy = 10.f;
}

//Constructors and Destructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initSpace();
	this->initTexture();
	this->initPlayer();
	this->initEnemy();
	this->initFonts();
	this->initText();
}

Game::~Game()
{
	delete this->window;
	delete this->player;

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

const bool& Game::getEndGame() const
{
	return this->endGame;
}

//Functions
const bool Game::running() const
{
	return this->window->isOpen() /*&& this->endGame == false*/;
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->sfmlEvent))
	{
		switch (this->sfmlEvent.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->sfmlEvent.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		case sf::Event::Resized:
			sf::FloatRect visibleArea(0,0,this->sfmlEvent.size.width,this->sfmlEvent.size.height);
			window->setView(sf::View(visibleArea));
		}
	}
}

void Game::spawnEnemy()
{
	//Spawning
	if (this->spawnTimer < this->spawnTimerMax)
	{
		this->spawnTimer++;
	}
	else
	{
		if (this->enemies.size() < this->maxEnemy)
		{
			this->enemies.push_back(new Enemy(this->window->getSize().x, static_cast<float>(rand() % this->window->getSize().y), this->randomEnemyType()));
			this->spawnTimer = 0.f;
			std::cout << "size of enemies: " << this->enemies.size() << std::endl;
		}
	}

}

const int Game::randomEnemyType() const
{
	int type = EnemyTypes::DEFAULT;
	int random = rand() % 100 + 1;
	if (random > 90 && random <= 100)
		type = EnemyTypes::HARD;
	else if (random >= 60 && random <= 80)
		type = EnemyTypes::MEDIUM;

	return type;
}

/*void Game::spawnSwagBalls()
{
	//Timer
	if (this->spawnTimerSwag < this->spawnTimerMaxSwag)
		this->spawnTimerSwag += 1.f;
	else
	{
		if (this->swagBalls.size() < this->maxSwagBalls)
		{
			this->swagBalls.push_back(SwagBall(*this->window, this->randBallType()));
			this->spawnTimer = 0.f;
		}
	}
}*/

/*const int Game::randBallType() const
{
	int type = SwagBallTypes::DEFAULT;

	int randValue = rand() % 100 + 1;
	if (randValue > 60 && randValue <= 80)
		type = SwagBallTypes::DAMAGING;
	else if (randValue > 80 && randValue <= 100)
		type = SwagBallTypes::HEALING;

	return type;
}*/

void Game::updatePlayer()
{
	this->player->update(this->window);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
	{
		this->bullets.push_back(new Bullet(this->textures["BULLET"],
			this->player->getPosition().x +this->player->getBounds().width / 2.f,
			this->player->getPosition().y + this->player->getBounds().height/ 2.f,
			1.f,0.f,5.f));
	}
	if (this->player->getHp() <= 0)
		this->endGame = true;
}

/*void Game::updateCollision()
{
	//Check the collision
	for (size_t i = 0; i < this->swagBalls.size(); i++)
	{
		if (this->player->getShape().getGlobalBounds().intersects(this->swagBalls[i].getShape().getGlobalBounds()))
		{
			switch (this->swagBalls[i].getType())
			{
			case SwagBallTypes::DEFAULT:
				this->points++;
				break;
			case SwagBallTypes::DAMAGING:
				this->player->takeDamage(1);
				break;
			case SwagBallTypes::HEALING:
				this->player->gainHealth(1);
				break;
			}

			//Remove the ball
			this->swagBalls.erase(this->swagBalls.begin() + i);
		}
	}
}*/

void Game::updateBulltes(sf::RenderWindow &window)
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();

		if (bullet->getBound().width + bullet->getPositon().x > window.getSize().x)
		{
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}
		++counter;
	}

}

void Game::updateEnemy()
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
			this->player->loseHp(this->enemies.at(counter)->getDamage());
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}
		++counter;
	}
}

void Game::updateBoom()
{
	for (int j = 0; j < this->booms.size(); ++j)
	{
		booms[j]->update();
		if (booms[j]->getAnimationFrame_x() >= 7 && booms[j]->getAnimationFrame_y() >= 7)
		{
			delete this->booms[j];
			this->booms.erase(this->booms.begin() + j);
		}
	}
}

void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_delete = false;
		for (int k = 0; k < this->bullets.size() && enemy_delete == false; k++)
		{
				if (this->bullets[k]->getBound().intersects(this->enemies[i]->getBounds()))
				{
					switch (this->enemies[i]->getType())
					{
					case EnemyTypes::DEFAULT:
						this->points += 1;
						break;
					case EnemyTypes::MEDIUM:
						this->points += 10;
						break;
					case EnemyTypes::HARD:
						this->points += 50;
						break;
					}
					this->booms.push_back(new Boom(this->textures["BOOM"],
						this->enemies[i]->getPosition().x - this->enemies[i]->getBounds().width / 2.f,
						this->enemies[i]->getPosition().y - this->enemies[i]->getBounds().height
					));
					//this->points += this->enemies[i]->getPoints();
					
					this->bullets.erase(this->bullets.begin() + k);

					this->enemies.erase(this->enemies.begin() + i);
					enemy_delete = true;
				}	
		}
	}
}

void Game::updateGui()
{
	std::stringstream ss;

	ss << " - Points: " << this->points << "\n";
		//<< " - Health: " << this->player->getHp() << " / " << this->player->getHpMax() << "\n";

	this->guiText.setString(ss.str());

	//Update player GUI
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent,this->playerHpBar.getSize().y));

}

void Game::update()
{
	this->pollEvents();

	if (this->endGame == false)
	{
		this->spawnEnemy();
		//this->spawnSwagBalls();
		this->updateBulltes(*this->window);
		this->updatePlayer();
		this->updateEnemy();
		this->updateCombat();
		this->updateBoom();
		//this->updateCollision();
		this->updateGui();
	}
}

void Game::renderSpace()
{
	this->window->draw(this->spaceBackground);
}

void Game::renderGui(sf::RenderTarget* target)
{
	target->draw(this->guiText);
	target->draw(this->playerHpBarBack);
	target->draw(this->playerHpBar);
	
}

void Game::render()
{
	this->window->clear();

	//Render background
	this->renderSpace();

	//Render stuff
	this->player->render(this->window);

	//for (auto i : this->swagBalls)
	//{
		//i.render(*this->window);
//	}

	//Render gui
	this->renderGui(this->window);

	//Render end text
	if (this->endGame == true)
		this->window->draw(this->endGameText);

	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	for (auto* boom : this->booms)
	{
		boom->render(this->window);
	}

	this->window->display();
}