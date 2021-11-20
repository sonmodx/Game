#pragma once
#include "Button.h"

class PauseMenu
{
private:
	sf::Font& font;
	sf::Text menuText;

	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, Button*> buttons;
	
	//Function

public:
	PauseMenu(sf::RenderWindow &window, sf::Font& font);
	virtual ~PauseMenu();

	//Accessors
	std::map<std::string, Button*>& getButtons();

	//Function
	const bool isButtonPressed(const std::string key);
	void addButton(const std::string key, float y, const std::string text);
	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget *target);
};

