#include "Button.h"

void Button::initSound()
{
	if (!this->soundBuf["BUTTON_SOUND"].loadFromFile("sound/buttonSound.wav"))
	{
		std::cout << "CANT LOAD BUTTON SOUND"<< "\n";
	}
	
	this->buttonSound.setBuffer(this->soundBuf["BUTTON_SOUND"]);
}

Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	this->initSound();

	this->buttonState = BTN_IDLE;
	this->texture.loadFromFile("img/obsidience.png");
	this->shape.setSize(sf::Vector2f(width, height));
	
	this->shape.setTexture(&this->texture);
	this->shape.setOrigin(this->shape.getLocalBounds().width / 2.f, this->shape.getLocalBounds().height / 2.f);
	this->shape.setPosition(sf::Vector2f(x, y));

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(40);
	this->text.setOrigin(this->text.getLocalBounds().width / 2.f, this->text.getLocalBounds().height / 2.f);
	this->text.setPosition(
		this->shape.getPosition().x ,
		this->shape.getPosition().y  - 20.f
	);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->shape.setFillColor(this->idleColor);
}

Button::~Button()
{
}

const bool Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
	{
		return true;
	}
		

	return false;
}

void Button::update(const sf::Vector2f& mousePos)
{
	/*Update the boolean for hover and pressed*/

	//Idle
	this->buttonState = BTN_IDLE;
	float time = cl.getElapsedTime().asMilliseconds();
	//Hover
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;
		this->shape.setScale(1.1f, 1.1f);

		//Hover sound
		this->buttonSound.play();
		if (time > 30)
		{
			this->buttonSound.stop();
		}

		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}
	else {
		this->shape.setScale(1.0f, 1.0f);
		cl.restart();
	}
	
	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		break;

	default:
		this->shape.setFillColor(sf::Color::Red);
		break;
	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}
