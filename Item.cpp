#include "Item.h"

void Item::initVariable()
{
	this->degree = 0.f;
	this->movementSpeed = 10.f;
}

Item::Item(sf::Texture* texture, float pos_x, float pos_y) //type
{
	this->initVariable();
	this->sprite.setTexture(*texture);
	this->sprite.setPosition(pos_x,pos_y);
	this->sprite.setScale(0.5f, 0.5f);
}

Item::~Item()
{
}


const sf::FloatRect Item::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const sf::Vector2f& Item::getPosition() const
{
	return this->sprite.getPosition();
}

void Item::setPosition(sf::Vector2f position)
{
	this->sprite.setPosition(position);
}

void Item::Move(float dir_x, float dir_y)
{
	this->sprite.move(this->movementSpeed* dir_x, this->movementSpeed * dir_y);
}

void Item::update(float dir_x, float dir_y)
{
	this->Move(dir_x,dir_y);
	float time = cl.getElapsedTime().asMilliseconds();
	if (time > 10)
	{
		this->sprite.setRotation(this->degree);
		this->degree += 1.f;
	}
	cl.restart();

}

void Item::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
