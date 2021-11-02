#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
class Bullet
{
private:
	sf::Sprite sprite;
	sf::Vector2f direction;
	float movementSpeed;
	//Function

public:
	//Constructor and Deconstructor
	Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
	virtual ~Bullet();


	//Accessors
	const sf::FloatRect getBound() const;
	const sf::Vector2f getPositon() const;

	//Function
	void update();
	void render(sf::RenderTarget* target);
};

