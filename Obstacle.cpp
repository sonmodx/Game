#include "Obstacle.h"

Obstacle::Obstacle(sf::Texture* texture,float pos_x, float pos_y, float speed, float damage)
{
	this->animationFrame_x = 0.f;
	this->animationFrame_y = 0.f;
	this->speed = speed;
	this->damage = damage;
	this->direction = sf::Vector2f(-1.f, 0.f);
	this->shape.setTexture(*texture);
	this->sizeSprite = sf::Vector2f(texture->getSize().x / 2.f, texture->getSize().y / 2.f);
	this->shape.setTextureRect(sf::IntRect(0.f, 0.f, this->sizeSprite.x, this->sizeSprite.y));
	this->shape.setPosition(pos_x, pos_y);
	this->shape.setScale(0.6f, 0.6f);
}

Obstacle::~Obstacle()
{
}

const sf::FloatRect Obstacle::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const sf::Vector2f Obstacle::getPositon() const
{
	return this->shape.getPosition();
}

const int& Obstacle::getDamage() const
{
	return this->damage;
}

void Obstacle::Move()
{
	this->shape.move(this->speed * this->direction.x, this->speed * this->direction.y);
}

void Obstacle::update()
{
	this->Move();
	float time = cl.getElapsedTime().asMilliseconds();
	if (time > 100)
	{
		this->shape.setTextureRect(sf::IntRect(this->sizeSprite.x * animationFrame_x, this->sizeSprite.y * animationFrame_y, this->sizeSprite.x, this->sizeSprite.y));
		this->animationFrame_x++;
		if (this->animationFrame_x == 1 && this->animationFrame_y == 1)
		{
			this->animationFrame_y = 0;
			this->animationFrame_x = 0;
		}
		if (this->animationFrame_x > 1)
		{
			this->animationFrame_x = 0;
			this->animationFrame_y++;

			if (this->animationFrame_y > 1)
			{
				this->animationFrame_y = 0;
			}
		}
		cl.restart();
	}
}

void Obstacle::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
