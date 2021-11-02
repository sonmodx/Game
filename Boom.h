#pragma once
#include "Bullet.h"
class Boom
{
private:
	sf::Sprite sprite;
	sf::Clock cl;
	sf::Vector2f sizeSprite;
	int animationFrame_x;
	int animationFrame_y;
	
	void initVariable();
public:
	//Constructor and Destructor
	Boom(sf::Texture *texture, float pos_x, float pos_y);
	~Boom();
	//Accessors
	const int getAnimationFrame_x() const;
	const int getAnimationFrame_y() const;

	//Function
	void update();
	void render(sf::RenderTarget *target);
};

