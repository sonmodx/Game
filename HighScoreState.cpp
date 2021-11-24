#define _CRT_SECURE_NO_WARNINGS
#include "HighScoreState.h"

void HighScoreState::initFonts()
{
	if (!this->font.loadFromFile("fonts/PixellettersFull.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void HighScoreState::initButtons()
{
	this->buttons["BACK_STATE"] = new Button(950, 700, 200, 50,
		&this->font, "BACK",
		Color(100, 100, 100, 200), Color(150, 150, 150, 255), Color(20, 20, 20, 200));
}

void HighScoreState::initKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
}

HighScoreState::HighScoreState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	if (!this->CursorText.loadFromFile("img/mouse.png"))
	{
		std::cout << "Can't load this mouse texture" << "\n";
	}
	this->mouseCursor.setTexture(this->CursorText);
	this->mouseCursor.setScale(0.1f, 0.1f);

	this->initFonts();
	this->initButtons();

	this->texture.loadFromFile("img/spaceScore.jpg");

	this->wallPaper.setSize(Vector2f(window->getSize()));
	this->wallPaper.setTexture(&this->texture);
	this->wallPaper.setFillColor(sf::Color(0,255,255,250));
	
	this->background1.setPosition({0,70});
	this->background1.setSize({ 1920, 500 });
	this->background1.setOutlineThickness(3);
	this->background1.setOutlineColor(Color(10,255,170,200));
	this->background1.setFillColor(Color(20, 20, 20, 250));

	text1.setFont(font);
	text1.setString("HIGH SCORE");
	text1.setPosition(sf::Vector2f( window->getSize().x/2.f - this->text1.getGlobalBounds().width , 80));
	text1.setCharacterSize(60);

	this->fp = fopen("config/Score.txt", "r");
	float num = 120.0f;
	for (int i = 0; i < 5; i++)
	{
		(void)fscanf(fp, "%s", &temp);
		name[i] = temp;
		(void)fscanf(fp, "%d", &score[i]);
		this->userScore.push_back(make_pair(this->score[i], this->name[i]));
		textscore[i].setString(std::to_string(this->score[i]));
		textname[i].setString(this->name[i]);
		textcount[i].setString(std::to_string(i + 1));

		num += 75.0f;
		textscore[i].setPosition({ 1100.0f,  num });
		textname[i].setPosition({ 800.0f, num });
		textcount[i].setPosition({ 750.0f, num });

		textscore[i].setFont(font);
		textname[i].setFont(font);
		textcount[i].setFont(font);
		textscore[i].setCharacterSize(42);
		textname[i].setCharacterSize(42);
		textcount[i].setCharacterSize(42);
	}
}

HighScoreState::~HighScoreState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void HighScoreState::updateButtons()
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	if (this->buttons["BACK_STATE"]->isPressed())
	{
		this->endState();
	}
}


void HighScoreState::updateEvent(Event input)
{

}

void HighScoreState::updateKeybinds(const float& dt)
{
}

void HighScoreState::updateInput(const float& dt)
{
}

void HighScoreState::update(const float& dt)
{
	this->window->setMouseCursorVisible(false);
	this->mouseCursor.setPosition(mousePosView);
	this->updateMousePosition();
	this->updateKeytime(dt);
	this->updateButtons();
}

void HighScoreState::renderButton(RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void HighScoreState::render(RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	
	target->draw(this->wallPaper);
	target->draw(this->background2);
	target->draw(this->background1);
	target->draw(text1);
	for (int i = 0; i < 5; i++)
	{
		target->draw(textname[i]);
		target->draw(textscore[i]);
		target->draw(textcount[i]);
	}

	this->renderButton(target);
	target->draw(this->mouseCursor);
}