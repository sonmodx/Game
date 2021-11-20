#include "Boom.h"

void Boom::initVariable()
{
	this->animationFrame_x = 0;
	this->animationFrame_y = 0;
}

Boom::Boom(sf::Texture* texture, float pos_x, float pos_y, int type)
{
	this->initVariable();
	this->type = type;
	switch (this->type)
	{
	case BOOM:
		this->sprite.setTexture(*texture);
		this->sizeSprite = sf::Vector2f(texture->getSize().x / 8, texture->getSize().y / 8);
		this->sprite.setTextureRect(sf::IntRect(0, 0, this->sizeSprite.x, this->sizeSprite.y));
		this->sprite.setPosition(pos_x, pos_y);
		this->sprite.setScale(2.f, 2.f);
		break;

	case BLOOD:
		this->sprite.setTexture(*texture);
		this->sizeSprite = sf::Vector2f(texture->getSize().x / 4, texture->getSize().y / 4);
		this->sprite.setTextureRect(sf::IntRect(0, 0, this->sizeSprite.x, this->sizeSprite.y));
		this->sprite.setPosition(pos_x, pos_y);
		this->sprite.setScale(0.4f, 0.4f);
		break;
	}
	
}

Boom::~Boom()
{
}

const int Boom::getAnimationFrame_x() const
{
	return this->animationFrame_x;
}

const int Boom::getAnimationFrame_y() const
{
	return this->animationFrame_y;
}

const int Boom::getType() const
{
	return this->type;
}

void Boom::update()
{
	float time = cl.getElapsedTime().asMilliseconds();
	switch (this->type)
	{
	case BOOM:
		if (time > 10)
		{
			this->sprite.setTextureRect(sf::IntRect(this->sizeSprite.x * animationFrame_x, this->sizeSprite.y * animationFrame_y, this->sizeSprite.x, this->sizeSprite.y));
			this->animationFrame_x++;
			if (this->animationFrame_x > 7)
			{
				this->animationFrame_y++;
				this->animationFrame_x = 0;
				if (this->animationFrame_y > 7)
				{
					this->animationFrame_y = 0;
				}
			}
			cl.restart();
		}
		break;
	case BLOOD:
		if (time > 40)
		{
			this->sprite.setTextureRect(sf::IntRect(this->sizeSprite.x * animationFrame_x, this->sizeSprite.y * animationFrame_y, this->sizeSprite.x, this->sizeSprite.y));
			this->animationFrame_x++;
			if (this->animationFrame_x > 3)
			{
				this->animationFrame_y++;
				this->animationFrame_x = 0;
				if (this->animationFrame_y > 3)
				{
					this->animationFrame_y = 0;

				}
			}
			cl.restart();
		}
		break;
	}
	
	
}

void Boom::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}