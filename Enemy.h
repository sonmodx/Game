#pragma once
#include "Bullet.h"

enum EnemyTypes {DEFAULT = 0, MEDIUM, HARD};

class Enemy
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f sizeSprite;
	sf::Clock cl;
	int hp;
	int hpMax;
	int damage;
	int type;
	int point;
	int pointCount;
	int animationFrame;
	int animationFrameHARD;
	float speed;
	void initVaraible();
	void initShape();
public:
	//Constructor and Deconstructor
	Enemy(float pos_x, float pos_y, int type);
	~Enemy();

	//Accessors
	const sf::FloatRect getBounds() const;
	const sf::Vector2f getPosition() const;
	const int& getType() const;
	const int& getPoints() const;
	const int& getDamage() const;

	//Function
	void Move();
	void update(int type);
	void render(sf:: RenderTarget *target);
};

