#include "Enemy.h"

void Enemy::initVaraible()
{
	this->hp		=  0;
	this->hpMax		=  10;
	this->pointCount = rand() % 20+ 3;
	this->damage	=  this->pointCount;
	this->point		=  this->pointCount;
	this->speed		=  10.f;
	this->animationFrame = 0;
	this->animationFrameHARD = 9;
}

void Enemy::initShape()
{
	switch (this->type)
	{
	case DEFAULT:
		this->texture.loadFromFile("img/alien.png");
		this->sprite.setTexture(this->texture);
		this->sizeSprite = sf::Vector2f(this->texture.getSize().x / 4, this->texture.getSize().y / 4);
		this->sprite.setTextureRect(sf::IntRect(0, 0, this->sizeSprite.x, this->sizeSprite.y));
		this->sprite.setScale(2.f, 2.f);
		break;
	case MEDIUM:
		//set Texture
		this->texture.loadFromFile("img/AllEnemy.png");
		this->sprite.setTexture(this->texture);
		this->sizeSprite = sf::Vector2f(this->texture.getSize().x / 12, this->texture.getSize().y / 8);
		this->sprite.setTextureRect(sf::IntRect(0, 0, this->sizeSprite.x, this->sizeSprite.y));
		this->sprite.setScale(2.f, 2.f);
		break;
	case HARD:
		//set Texture 
		this->texture.loadFromFile("img/AllEnemy.png");
		this->sprite.setTexture(this->texture);
		this->sizeSprite = sf::Vector2f(this->texture.getSize().x / 12, this->texture.getSize().y / 8);
		this->sprite.setTextureRect(sf::IntRect(0, 0, this->sizeSprite.x, this->sizeSprite.y));
		this->sprite.setScale(2.f, 2.f);
		break;
	}
		

	
}

Enemy::Enemy(float pos_x, float pos_y, int type)
{
	this->type = type;
	this->initVaraible();
	this->initShape();
	
	this->sprite.setPosition(pos_x, pos_y);
}

Enemy::~Enemy()
{
}

//Accessors
const sf::FloatRect Enemy::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const sf::Vector2f Enemy::getPosition() const
{
	return this->sprite.getPosition();
}

const int& Enemy::getType() const
{
	return this->type;
}

const int& Enemy::getPoints() const
{
	return this->point;
}

const int& Enemy::getDamage() const
{
	return this->damage;
}

//Function
void Enemy::Move()
{
	float time = cl.getElapsedTime().asMilliseconds();
	switch (this->type)
	{
	case DEFAULT:
		if (time > 100)
		{
			this->sprite.move(-this->speed, 0.f);
			this->sprite.setTextureRect(sf::IntRect(this->sizeSprite.x * animationFrame, this->sizeSprite.y * 1, this->sizeSprite.x, this->sizeSprite.y));
			this->animationFrame++;
			if (this->animationFrame > 3)
			{
				this->animationFrame = 0;
			}
			cl.restart();
		}
		break;
	case MEDIUM:
		if (time > 100)
		{
			this->sprite.move(-this->speed, 0.f);
			this->sprite.setTextureRect(sf::IntRect(this->sizeSprite.x * animationFrame, this->sizeSprite.y * 1, this->sizeSprite.x, this->sizeSprite.y));
			this->animationFrame++;
			if (this->animationFrame > 2)
			{
				this->animationFrame = 0;
			}
			cl.restart();
		}
		break;
	case HARD:
		if (time > 100)
		{
			this->sprite.move(-this->speed, 0.f);
			this->sprite.setTextureRect(sf::IntRect(this->sizeSprite.x * animationFrameHARD, this->sizeSprite.y * 1, this->sizeSprite.x, this->sizeSprite.y));
			this->animationFrameHARD++;
			if (this->animationFrameHARD > 11)
			{
				this->animationFrameHARD = 9;
			}
			cl.restart();
		}
		break;
	}
	

	
		
}

void Enemy::update(int type)
{
	this->Move();
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
