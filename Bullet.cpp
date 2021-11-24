#include "Bullet.h"

void Bullet::initVariable()
{
	this->animationFrame_x = 0;
	this->animationFrame_y = 0;
	this->charged = 0;
	this->count = 0.f;
}

Bullet::Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed, int damage,int type)
{
	this->type = type;
	this->initVariable();
	switch (this->type)
	{
	case FIRE:
		this->sprite.setTexture(*texture);
		this->sprite.setPosition(pos_x, pos_y);
		this->sprite.setScale(0.1f, 0.1f);
		this->direction.x = dir_x;
		this->direction.y = dir_y;
		this->movementSpeed = movement_speed;
		this->damage = damage;
		break;
	case LASER:
		this->sprite.setTexture(*texture);
		this->sprite.setPosition(pos_x, pos_y);
		this->sizeSprite = sf::Vector2f(texture->getSize().x / 4, texture->getSize().y);
		this->sprite.setTextureRect(sf::IntRect(0, 0, this->sizeSprite.x, this->sizeSprite.y));
		this->sprite.setScale(1.f, 1.f);
		this->direction.x = dir_x;
		this->direction.y = dir_y;
		this->movementSpeed = movement_speed;
		this->damage = damage;
		break;
	case TORNADO:
		this->sprite.setTexture(*texture);
		this->sprite.setPosition(pos_x, pos_y);
		this->sizeSprite = sf::Vector2f(texture->getSize().x / 5, texture->getSize().y / 4);
		this->sprite.setTextureRect(sf::IntRect(0, 0, this->sizeSprite.x, this->sizeSprite.y));
		this->direction.x = dir_x;
		this->direction.y = dir_y;
		this->movementSpeed = movement_speed;
		this->damage = damage;
		break;
	case SUPER:
		this->sprite.setTexture(*texture);
		this->sprite.setPosition(pos_x, pos_y);
		this->sprite.setScale(5.f, 5.f);
		this->sizeSprite = sf::Vector2f(texture->getSize().x / 6, texture->getSize().y / 3);
		this->sprite.setTextureRect(sf::IntRect(0, 0, this->sizeSprite.x, this->sizeSprite.y));
		this->direction.x = dir_x;
		this->direction.y = dir_y;
		this->movementSpeed = movement_speed;
		this->damage = damage;
		break;
	}
	
}

Bullet::~Bullet()
{
}

const sf::FloatRect Bullet::getBound() const
{
	return this->sprite.getGlobalBounds();
}

const sf::Vector2f Bullet::getPositon() const
{
	return this->sprite.getPosition();
}

const int& Bullet::getDamage() const
{
	return this->damage;
}

const int Bullet::getType() const
{
	return this->type;
}

const int Bullet::getAniFrame_y() const
{
	return this->animationFrame_y;
}

void Bullet::loseDamage(const int value)
{
	this->damage -= value;
	if (this->damage <= 0)
		this->damage = 0;
}


void Bullet::Move()
{
	float time = cl.getElapsedTime().asMilliseconds();
	switch (this->type)
	{
	case FIRE:
		this->sprite.move(this->movementSpeed * this->direction);
		break;
	case LASER:
		this->sprite.move(this->movementSpeed * this->direction);
		if (time > 10)
		{
			this->sprite.setTextureRect(sf::IntRect(this->sizeSprite.x * animationFrame_x, this->sizeSprite.y * animationFrame_y, this->sizeSprite.x, this->sizeSprite.y));
			this->animationFrame_x++;
			if (this->animationFrame_x > 3)
			{

				this->animationFrame_x = 0;
			}
			cl.restart();
		}
		break;
	case TORNADO:
		this->sprite.move(this->movementSpeed * this->direction);
		if (time > 30)
		{
			this->sprite.setTextureRect(sf::IntRect(this->sizeSprite.x * animationFrame_x, this->sizeSprite.y * animationFrame_y, this->sizeSprite.x, this->sizeSprite.y));
			this->animationFrame_x++;
			if (this->animationFrame_x > 4)
			{
				this->animationFrame_y++;
				this->animationFrame_x = 0;
				if (this->animationFrame_y > 3)
					this->animationFrame_y = 0;
			}
			cl.restart();
		}
		break;
	case SUPER:
		if (time > 20)
		{
			this->sprite.move(0.f * this->direction);
			this->sprite.setTextureRect(sf::IntRect(this->sizeSprite.x * animationFrame_x, this->sizeSprite.y * animationFrame_y, this->sizeSprite.x, this->sizeSprite.y));
			if (this->animationFrame_x > 5 && this->animationFrame_y < 2 )
			{
				
				this->animationFrame_y++;
				this->animationFrame_x = 0;
			}
			else if (this->animationFrame_y >= 2 )
			{
				
				this->animationFrame_y = 2;
				this->animationFrame_x++;
				this->sprite.move(this->movementSpeed * this->direction);
				if (this->animationFrame_x > 5)
					this->animationFrame_x = 2;
			}
			if (this->animationFrame_x == 4 && this->animationFrame_y == 0 && this->count < 50)
			{
				this->count++;
				if (this->count > 10 &&this->charged < 4)
				{
					
					this->sprite.setTextureRect(sf::IntRect(this->sizeSprite.x * animationFrame_x, this->sizeSprite.y * animationFrame_y, this->sizeSprite.x, this->sizeSprite.y));
					this->animationFrame_x--;
					this->sprite.setTextureRect(sf::IntRect(this->sizeSprite.x * animationFrame_x, this->sizeSprite.y * animationFrame_y, this->sizeSprite.x, this->sizeSprite.y));
						this->animationFrame_x++;
						this->count = 0;
						this->charged += 1;
				}
			}
			else 
				this->animationFrame_x++;
			cl.restart();
		}
		break;
	}
}

void Bullet::update(int type)
{
	this->Move();
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
