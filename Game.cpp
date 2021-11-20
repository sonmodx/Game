#include "Game.h"

void Game::initVariable()
{
	this->window = NULL;
	this->fullscreen = true;
	this->dt = 0.f;
}

void Game::initWindow()
{
	std::ifstream ifs("config/window.ini");
	this->videoModes = sf::VideoMode::getFullscreenModes();
	std::string title = "None";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
	unsigned framerate_limit = 60;
	bool vertical_sync_enable = false;
	unsigned antialiasing_level = 0;

	if (ifs.is_open())
	{
		std::getline(ifs, title);
		//ifs >> window_bounds.width >> window_bounds.height;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enable;
	}
	ifs.close();

	this->fullscreen = fullscreen;
	this->windowSettings.antialiasingLevel = antialiasing_level;
	if (this->fullscreen)
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, this->windowSettings);
	else
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, this->windowSettings);

	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enable);
}

void Game::initStates()
{
	this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}

void Game::initKeys()
{
	this->supportedKeys.emplace("Escape", sf::Keyboard::Key::Escape);
	this->supportedKeys.emplace("A", sf::Keyboard::Key::A);
	this->supportedKeys.emplace("D", sf::Keyboard::Key::D);
	this->supportedKeys.emplace("W", sf::Keyboard::Key::W);
	this->supportedKeys.emplace("S", sf::Keyboard::Key::S);

	//DEBUG
	for (auto i : this->supportedKeys)
	{
		std::cout << i.first << " " << i.second << "\n";
	}
}

Game::Game()
{
	this->initVariable();
	this->initWindow();
	this->initKeys();
	this->initStates();
}

Game::~Game()
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

void Game::endApplication()
{
	std::cout << "End Application" << "\n";
}

void Game::updateDt()
{
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSfEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
		{
			this->window->close();
		}
		else if (this->sfEvent.type == sf::Event::TextEntered)
		{
			this->states.top()->updateEvent(sfEvent);
		}
	}
}

void Game::update()
{
	this->updateSfEvents();

	if (!this->states.empty())
	{
		this->states.top()->update(this->dt);

		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	//Appication Ending
	else
	{
		this->endApplication();
		this->window->close();
	}
		
}

void Game::render()
{
	this->window->clear();
	//Render Item
	if (!this->states.empty())
		this->states.top()->render();

	this->window->display();
}

void Game::run()
{
	srand(static_cast<unsigned>(time(0)));
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}
