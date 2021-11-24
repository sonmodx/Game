#include "MainMenuState.h"

void MainMenuState::initVariable()
{
	this->isNameInput = true;
	this->isPlay = 0;
}

void MainMenuState::initSound()
{
	
}

void MainMenuState::initBackground()
{
	this->background.setSize(sf::Vector2f(
		static_cast<float>(this->window->getSize().x), 
		static_cast<float>(this->window->getSize().y)
	));
	this->backgroundTexture.loadFromFile("img/menuBackground.png");
	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts()
{
	this->font.loadFromFile("fonts/PixellettersFull.ttf");

	this->PlayerName.setString("");
	this->PlayerName.setFont(this->font);
	this->PlayerName.setFillColor(sf::Color::White);
	this->PlayerName.setCharacterSize(1000);
	this->PlayerName.setScale(0.14f, 0.14f);
	this->PlayerName.setPosition(InputName.getPosition().x, InputName.getPosition().y + 70.0f);
}

void MainMenuState::initKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
}

void MainMenuState::initButton()
{
	this->buttons["GAME_STATE"] = new Button(880.f, 450.f, 250.f, 50.f,
		&this->font, "New Game",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["HIGH_SCORE"] = new Button(880.f, 650.f, 250.f, 50.f,
		&this->font, "High score",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["EXIT_STATE"] = new Button(880.f, 850.f, 250.f, 50.f,
		&this->font, "Quit",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	
}

void MainMenuState::initPlayButton()
{
	//Input Name
	//this->InputNameTex.loadFromFile("img/fire.png");
}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	:State(window, supportedKeys, states)
{
	
	if (!this->CursorText.loadFromFile("img/mouse.png"))
	{
		std::cout<<"Can't load this mouse texture"<< "\n";
	}
	this->mouseCursor.setTexture(this->CursorText);
	this->mouseCursor.setScale(0.1f, 0.1f);
	//this->mouseCursor.setOrigin(sf::Vector2f(this->CursorText.getSize().x /2.f , this->CursorText.getSize().y /2.f));

	this->initVariable();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButton();
	this->initPlayButton();
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void MainMenuState::updateInput(const float& dt)
{

}

void MainMenuState::updateButtons()
{
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	//New game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
		this->checkInGame = true;
	}
	
	//High Score
	if (this->buttons["HIGH_SCORE"]->isPressed())
	{
		this->states->push(new HighScoreState(this->window, this->supportedKeys, this->states));
	}

	//Quit the game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
			this->endState();
	}
}

void MainMenuState::updateEvent(sf::Event input)
{
}

void MainMenuState::update(const float& dt)
{
	this->window->setMouseCursorVisible(false);
	this->mouseCursor.setPosition(mousePosView);

	this->updateMousePosition();
	this->updateInput(dt);
	
		this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(target);

	target->draw(this->mouseCursor);
	/*
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);*/
	
}
