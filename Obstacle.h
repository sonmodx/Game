#pragma once
#include "Bullet.h"
class Obstacle
{
private:
	sf::Sprite shape;
	sf::Vector2f direction;
	float speed;
	float damage;
	sf::Vector2f sizeSprite;
	sf::Clock cl;
	int animationFrame_x;
	int animationFrame_y;

public:
	Obstacle(sf::Texture *texture, float pos_x, float pos_y, float speed, float damage);
	~Obstacle();

	//Accessors
	const sf::FloatRect getBounds() const;
	const sf::Vector2f getPositon() const;
	const int& getDamage() const;

	//Modifier
	

	//Function
	void Move();
	void update();
	void render(sf::RenderTarget *target);
};

