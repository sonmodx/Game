#pragma once
#include "State.h"
#include "Button.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "Textbox.h"
#include "ScoreBoard.h"

class HighScoreState : public State
{
private:
	RectangleShape wallPaper;
	ConvexShape background2;
	RectangleShape background1;
	Font font;
	Texture texture;
	Textbox* textbox1;
	Text text1;
	ScoreBoard scoreboard;
	Text textscore[6];
	Text textname[6];
	Text textcount[6];

	FILE* fp;
	char temp[255];
	unsigned int score[6];
	string name[6];
	vector<pair<int, string>> userScore;

	std::map<std::string, Button*> buttons;

	// functions
	void initFonts();
	void initButtons();
	void initKeybinds();

public:
	HighScoreState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~HighScoreState();

	void updateEvent(Event input);
	void updateKeybinds(const float& dt);
	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButton(RenderTarget* target = NULL);
	void render(RenderTarget* target = NULL);
};

