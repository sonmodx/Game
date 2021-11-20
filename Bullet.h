#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>

enum BulletTypes { FIRE = 0, LASER ,TORNADO, SUPER};

class Bullet
{
private:
	sf::Sprite sprite;
	sf::Vector2f direction;
	sf::Clock cl;
	sf::Vector2f sizeSprite;

	float movementSpeed;
	int animationFrame_x;
	int animationFrame_y;
	int type;
	int damage;
	float count;
	unsigned charged;
	//Function
	void initVariable();
public:
	//Constructor and Deconstructor
	Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed, int damage, int type);
	virtual ~Bullet();

	//Accessors
	const sf::FloatRect getBound() const;
	const sf::Vector2f getPositon() const;
	const int& getDamage() const;
	const int getType() const;

	//Modifer
	void loseDamage(const int value);

	//Function
	void Move();
	void update(int type);
	void render(sf::RenderTarget* target);
};

