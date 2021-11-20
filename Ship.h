#pragma once
#include "Bullet.h"
class Ship
{
private:
	sf::Sprite sprite;

	int hp;
	int hpMax;

	void initVariable();
	void initShape();
public:
	//Constructor and Deconstructor
	Ship(sf::Texture *texture, float pos_x, float pos_y);
	~Ship();

	//Accessors
	const sf::FloatRect getBounds() const;
	
	//Modifier

	//Functions
	void update();
	void render(sf::RenderTarget *target);

};

