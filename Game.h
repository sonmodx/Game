#pragma once
#include "MainMenuState.h"

class Game
{
private:
	sf::RenderWindow *window;
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;
	sf::Event sfEvent;
	bool fullscreen;
	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	//Initialization
	void initVariable();
	void initWindow();
	void initStates();
	void initKeys();
public:
	Game();
	virtual ~Game();

	//Function

	//Regular
	void endApplication();

	//Update
	void updateDt();
	void updateSfEvents();
	void update();

	//Render
	void render();

	//Core
	void run();
};

