#pragma once
#include "Bullet.h"

class Item
{
private:
	sf::Sprite sprite;
	sf::Clock cl;
	float degree;
	float movementSpeed;
	void initVariable();
public:
	//Constructor and Deconstructor
	Item(sf::Texture* texture, float pos_x, float pos_y);//type next
	~Item();

	//Accessors
	const sf::FloatRect getBounds() const;
	const sf::Vector2f& getPosition() const;

	//Modifier
	void setPosition(sf::Vector2f position);

	//Function
	void Move(float dir_x, float dir_y);
	void update(float dir_x, float dir_y);
	void render(sf::RenderTarget *target);

};