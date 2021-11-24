#pragma once
#include "State.h"

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

class Button
{
private:
	short unsigned buttonState;
	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;
	
	sf::Texture texture;
	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

	sf::Sound buttonSound;
	std::map<std::string, sf::SoundBuffer> soundBuf;
	sf::Clock cl;

	void initSound();
public:
	Button(float x, float y, float width, float height,
		sf::Font* font, std::string text,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	~Button();

	//Accessors
	const bool isPressed() const;

	//Function
	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget* target);
};

