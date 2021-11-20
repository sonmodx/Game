#include "Ship.h"

void Ship::initVariable()
{
	this->hpMax = 100;
	this->hp = this->hpMax;
}

void Ship::initShape()
{

}

Ship::Ship(sf::Texture* texture, float pos_x, float pos_y)
{
	this->initVariable();
	this->sprite.setTexture(*texture);
	this->sprite.setPosition(pos_x, pos_y);
	this->sprite.setScale(0.20f, 0.20f);
}

Ship::~Ship()
{
}

const sf::FloatRect Ship::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Ship::update()
{
}

void Ship::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
