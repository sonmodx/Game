#include "Bullet.h"

Bullet::Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed)
{
	this->sprite.setTexture(*texture);
	this->sprite.setPosition(pos_x,pos_y);
	this->sprite.setScale(0.1f,0.1f);
	this->direction.x = dir_x;
	this->direction.y = dir_y;
	this->movementSpeed = movement_speed;
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

void Bullet::update()
{
	this->sprite.move(this->movementSpeed * this->direction);
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
