#include "Player.h"

void Player::initVariables()
{
	this->movementSpeed = 30.f;
	this->hpMax = 100.f;
	this->hp = this->hpMax;
	this->attackTimeMax = 20.f;
	this->attackTime = this->attackTimeMax;
	this->skillTimeMax = 100.f;
	this->skillTime = this->skillTimeMax;
	this->skillTornadoTimeMax = 100.f;
	this->skillTornadoTime = this->skillTornadoTimeMax;
	this->skillSuperMax = 100.f;
	this->skillSuper = this->skillSuperMax;
	this->directionTor = -1;
	this->animationFrame = 0;
	this->receive_damage = 0;
	this->c = 0.f;
}

void Player::initShape()
{
	this->texture.loadFromFile("img/boy.png");
	this->sprite.setTexture(this->texture);
	this->sizeSprite = sf::Vector2i(this->texture.getSize().x / 3, this->texture.getSize().y / 4);
	this->sprite.setTextureRect(sf::IntRect(0, 0, this->sizeSprite.x, this->sizeSprite.y));
	this->sprite.setScale(0.7f,0.7f);
}

Player::Player(float x, float y)
{
	this->sprite.setPosition(x, y);

	this->initVariables();
	this->initShape();
}

Player::~Player()
{

}

//Accessors
const sf::Sprite& Player::getShape() const
{
	return this->sprite;
}

const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::getHpMax() const
{
	return this->hpMax;
}

const int& Player::getSkill() const
{
	return this->skillTime;
}

const int& Player::getSkillMax() const
{
	return this->skillTimeMax;
}

const int& Player::getSkillTornado() const
{
	return this->skillTornadoTime;
}

const int& Player::getSkillTornadoMax() const
{
	return this->skillTornadoTimeMax;
}

const int& Player::getSkillSuper() const
{
	return this->skillSuper;
}

const int& Player::getSkillSuperMax() const
{
	return this->skillSuperMax;
}

const sf::Vector2f& Player::getPosition() const
{
	return this->sprite.getPosition();
}


const bool Player::canAttack() 
{
	if (this->attackTime >= this->attackTimeMax)
	{
		this->attackTime = 0.f;
		return true;
	}
		return false;
	
}

const bool Player::canSkill()
{
	if (this->skillTime >= this->skillTimeMax)
	{
		this->skillTime = 0.f;
		return true;
	}
	return false;
}

const bool Player::canSkillTornado()
{
	if (this->skillTornadoTime >= this->skillTornadoTimeMax)
	{
		this->skillTornadoTime = 0.f;
		return true;
	}
	return false;
}

const bool Player::canSkillSuper()
{
	if (this->skillSuper >= this->skillSuperMax)
	{
		this->skillSuper = 0.f;
		return true;
	}
	return false;
}

const int Player::getDirTor()
{
	return this->directionTor;
}



const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Player::setHp(const int hp)
{
	this->hp = hp;
}

void Player::loseHp(const int value)
{
	c = 0.f;
	this->receive_damage = value;
	if (this->hp < 0.f)
		this->hp = 0;
	
}

void Player::setPosition(const sf::Vector2f position)
{
	this->sprite.setPosition(position);
}

//Functions
void Player::takeDamage(const int damage)
{
	if (this->hp > 0)
		this->hp -= damage;

	if (this->hp < 0)
		this->hp = 0;
}

void Player::gainHealth(const int health)
{
	if (this->hp < this->hpMax)
		this->hp += health;

	if (this->hp > this->hpMax)
		this->hp = this->hpMax;
}

void Player::updateSkill()
{
	if (this->skillTime < this->skillTimeMax)
		this->skillTime += 0.2f;

	if (this->skillTornadoTime < this->skillTornadoTimeMax)
		this->skillTornadoTime += 0.5f;

	if (this->skillSuper < this->skillSuperMax)
		this->skillSuper += 0.1f;
}

void Player::updateAttack()
{
	if (this->attackTime < this->attackTimeMax)
		this->attackTime++;
}

void Player::updateLoseHp()
{
	if (c <  this->receive_damage)
	{
		this->hp -= 1.f;
		c += 1.f;
	}
}

void Player::updateInput()
{
	//Keyboard input
	float time = cl.getElapsedTime().asMilliseconds();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && time > 70)
	{
		this->sprite.move(-this->movementSpeed, 0.f);
		this->sprite.setTextureRect(sf::IntRect(this->sizeSprite.x *this->animationFrame,this->sizeSprite.y *1,this->sizeSprite.x,this->sizeSprite.y));
		cl.restart();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && time > 70)
	{
		this->sprite.move(this->movementSpeed, 0.f);
		this->sprite.setTextureRect(sf::IntRect(this->sizeSprite.x * this->animationFrame, this->sizeSprite.y * 2, this->sizeSprite.x, this->sizeSprite.y));
		cl.restart();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && time > 70)
	{
		this->directionTor = -1;
		this->sprite.move(0.f, -this->movementSpeed);
		this->sprite.setTextureRect(sf::IntRect(this->sizeSprite.x * this->animationFrame, this->sizeSprite.y * 2, this->sizeSprite.x, this->sizeSprite.y));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			this->sprite.setTextureRect(sf::IntRect(this->sizeSprite.x * this->animationFrame, this->sizeSprite.y * 1, this->sizeSprite.x, this->sizeSprite.y));
		}
		cl.restart();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && time > 70)
	{
		this->directionTor = 1;
		this->sprite.move(0.f, this->movementSpeed);
		this->sprite.setTextureRect(sf::IntRect(this->sizeSprite.x * this->animationFrame, this->sizeSprite.y * 2, this->sizeSprite.x, this->sizeSprite.y));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			this->sprite.setTextureRect(sf::IntRect(this->sizeSprite.x * this->animationFrame, this->sizeSprite.y * 1, this->sizeSprite.x, this->sizeSprite.y));
		}
		cl.restart();
	}
	this->animationFrame++;
	if (this->animationFrame > 2)
	{
		this->animationFrame = 0;
	}
}

void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
	//Left
	if (this->sprite.getGlobalBounds().left <= 0.f)
		this->sprite.setPosition(0.f, this->sprite.getGlobalBounds().top);
	//Right
	if (this->sprite.getGlobalBounds().left + this->sprite.getGlobalBounds().width >= target->getSize().x)
		this->sprite.setPosition(target->getSize().x - this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().top);
	//Top
	if (this->sprite.getGlobalBounds().top <= 0.f)
		this->sprite.setPosition(this->sprite.getGlobalBounds().left, 0.f);
	//Bottom
	if (this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height >= target->getSize().y)
		this->sprite.setPosition(this->sprite.getGlobalBounds().left, target->getSize().y - this->sprite.getGlobalBounds().height);
}

void Player::update(const sf::RenderTarget* target)
{
	this->updateAttack();
	this->updateLoseHp();
	this->updateSkill();
	this->updateInput();
	
	//Window bounds collision
	this->updateWindowBoundsCollision(target);
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
