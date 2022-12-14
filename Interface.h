#pragma once
#include <SFML/Graphics.hpp>
#include "IButton.h"
#include <vector>
#include <string>

class Interface
{
public:
    Interface();
    ~Interface();
    void launch();
private:
    sf::RenderWindow _window;
    sf::Font _font;
    unsigned int _font_size;
    std::vector<IButton*> _buttons;
    std::vector<sf::RectangleShape*> _lines;
    std::vector<sf::Text*> _texts;
    sf::Text* text_current_date;
    sf::Text* text_current_time;
    int current_date;
    int current_time;
    void input();
    void update(float time); //здесь апдейт окна происходит
    void draw();
    void setObject(sf::Vector2f size, sf::Vector2f position);
    void setObject(sf::Vector2f size, sf::Vector2f position, std::string string);
};