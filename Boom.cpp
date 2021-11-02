#include "Boom.h"

void Boom::initVariable()
{
	this->animationFrame_x = 0;
	this->animationFrame_y = 0;
}

Boom::Boom(sf::Texture* texture, float pos_x, float pos_y)
{
	this->initVariable();
	this->sprite.setTexture(*texture);
	this->sizeSprite = sf::Vector2f(texture->getSize().x / 8,texture->getSize().y / 8);
	this->sprite.setTextureRect(sf::IntRect(0, 0, this->sizeSprite.x,this->sizeSprite.y));
	this->sprite.setPosition(pos_x, pos_y);
	this->sprite.setScale(2.f,2.f);
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

void Boom::update()
{
	float time = cl.getElapsedTime().asMilliseconds();
	if (time > 10)
	{
		this->sprite.setTextureRect(sf::IntRect(this->sizeSprite.x * animationFrame_x, this->sizeSprite.y * animationFrame_y, this->sizeSprite.x, this->sizeSprite.y));
		this->animationFrame_x++;
		if (this->animationFrame_x > 7)
		{
			this->animationFrame_y++;
			if (this->animationFrame_y > 7)
			{
				this->animationFrame_y = 0;
				this->animationFrame_x = 0;
			}
		}
		cl.restart();
	}
	

}

void Boom::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
