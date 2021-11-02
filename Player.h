#pragma once

#include "Bullet.h"

class Player
{
private:
	//sf::RectangleShape shape;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2i sizeSprite;
	sf::Clock cl;
	
	float movementSpeed;
	int hp;
	int hpMax;
	float attackTime;
	float attackTimeMax;

	int animationFrame;
	void initVariables();
	void initShape();

public:
	Player(float x = 0.f, float y = 0.f);
	virtual ~Player();

	//Accessors
	const sf::Sprite& getShape() const;
	const int& getHp() const;
	const int& getHpMax() const;
	const sf::Vector2f& getPosition() const;
	const bool canAttack();
	const sf::FloatRect getBounds() const;

	//Modifier
	void setHp(const int hp);
	void loseHp(const int value);


	//Functions
	void takeDamage(const int damage);
	void gainHealth(const int health);

	void updateAttack();
	void updateInput();
	void updateWindowBoundsCollision(const sf::RenderTarget* target);
	void update(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);
};

