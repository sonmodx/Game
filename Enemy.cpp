#include "Enemy.h"

void Enemy::initVaraible()
{
	switch (this->type)
	{
	case DEFAULT:
		this->hp = 10;
		this->hpMax = 10;
		this->damage = 10;
		this->point = 10;
		this->speed = 15.f;
		this->animationFrame = 0;
		break;
	case MEDIUM:
		this->hp = 20;
		this->hpMax = 20;
		this->damage = 20;
		this->point = 20;
		this->speed = 30.f;
		this->animationFrame = 0;
		break;
	case HARD:
		this->hp = 50;
		this->hpMax = 50;
		this->damage = 50;
		this->point = 100;
		this->speed = 7.f;
		this->animationFrameHARD = 9;
		break;
	}
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

const int& Enemy::getHp() const
{
	return this->hp;
}

const int& Enemy::getHpMax() const
{
	return this->hpMax;
}

void Enemy::loseHp(const int value)
{
	this->hp -= value;
	if (this->hp <= 0.f)
		this->hp = 0;
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
