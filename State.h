#pragma once
#include "Bullet.h"
#include "Entity.h"
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <stack>
#include <map>

class State
{
private:

protected:
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;
	bool paused;

	float keytime;
	float keytimeMax;
	sf::String Name;
	sf::Text PlayerName;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	//Resources

	//Function
	virtual void initKeybinds() = 0;
public:
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~State();

	//Accessors
	const bool& getQuit() const;
	const bool getKeytime();

	//Function
	void endState();
	void pauseState();
	void unpauseState();

	virtual void updateMousePosition();
	virtual void updateKeytime(const float &dt);
	virtual void updateEvent(sf::Event input) = 0;
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = NULL) = 0;
};

