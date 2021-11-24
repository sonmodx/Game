#pragma once
#include "GameState.h"
#include "Button.h"
#include "HighScoreState.h"
#include "Textbox.h"

class MainMenuState :
    public State
{
private:    
    sf::Sprite mouseCursor;
    sf::Texture CursorText;

    Textbox *nameMenu;
    bool checkInGame;

    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Event event;
    sf::Font font;
    std::map<std::string, Button*> buttons;
    bool isNameInput;
    sf::RectangleShape play_button;
    sf::Texture play_buttontex;

    sf::RectangleShape InputName;
    sf::Texture InputNameTex;
    sf::Text InputName_text;
    sf::Text OnlyEight;
    sf::RectangleShape CloseInputNameButton;
    sf::Texture CloseInputNameButtonTex;
    int isPlay;

    //Function
    void initVariable();
    void initSound();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButton();
    void initPlayButton();

public:
    MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~MainMenuState();

    inline std::string getName() { return Name; }

    //Function
    void updateInput(const float& dt);
    void updateButtons();
    void updateEvent(sf::Event input);
    void update(const float& dt);
    void renderButtons(sf::RenderTarget* target = NULL);
    void render(sf::RenderTarget* target = NULL);
};

