#pragma once

#include "Bullet.h"

class Player
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2i sizeSprite;
	sf::Clock cl;
	float c;
	float movementSpeed;
	float hp;
	float hpMax;
	unsigned receive_damage;
	float attackTime;
	float attackTimeMax;
	float skillTime;
	float skillTimeMax;
	float skillTornadoTime;
	float skillTornadoTimeMax;
	float skillSuper;
	float skillSuperMax;

	int animationFrame;
	int directionTor;
	void initVariables();
	void initShape();

public:
	Player(float x = 0.f, float y = 0.f);
	virtual ~Player();

	//Accessors
	const sf::Sprite& getShape() const;
	const int& getHp() const;
	const int& getHpMax() const;
	const int& getSkill() const;
	const int& getSkillMax() const;
	const int& getSkillTornado() const;
	const int& getSkillTornadoMax() const;
	const int& getSkillSuper() const;
	const int& getSkillSuperMax() const;
	const sf::Vector2f& getPosition() const;
	const bool canAttack();
	const bool canSkill();
	const bool canSkillTornado();
	const bool canSkillSuper();
	const int getDirTor();
	const sf::FloatRect getBounds() const;

	//Modifier
	void setHp(const int hp);
	void loseHp(const int value);
	void setPosition(const sf::Vector2f position);
	void takeDamage(const int damage);
	void gainHealth(const int health);

	//Functions
	void updateSkill();
	void updateAttack();
	void updateLoseHp();
	void updateInput();
	void updateWindowBoundsCollision(const sf::RenderTarget* target);
	void update(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);
};

