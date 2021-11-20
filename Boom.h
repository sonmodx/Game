#pragma once
#include "Bullet.h"

enum BoomTypes { BOOM = 0 , BLOOD};

class Boom
{
private:
	sf::Sprite sprite;
	sf::Clock cl;
	sf::Vector2f sizeSprite;
	int animationFrame_x;
	int animationFrame_y;
	int type;

	void initVariable();
public:
	//Constructor and Destructor
	Boom(sf::Texture *texture, float pos_x, float pos_y, int type);
	~Boom();
	//Accessors
	const int getAnimationFrame_x() const;
	const int getAnimationFrame_y() const;
	const int getType() const;

	//Function
	void update();
	void render(sf::RenderTarget *target);
};

