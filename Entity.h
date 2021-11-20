#pragma once
#include "State.h"
class Entity
{
private:

protected:
	sf::RectangleShape shape;
	float movementSpeed;
public:
	Entity();
	virtual ~Entity();

	//Function
	virtual void move(const float& dt, const float dir_x, const float dir_y);
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
};

