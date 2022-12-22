#pragma once
#include <SFML/Graphics.hpp>
#include "IButton.h"
#include "PinButton.h"
#include "Manager.h"
#include "Trucks.h"
#include "Warehouse.h"
#include <vector>
#include <string>

class Interface
{
public:
    Interface();
    ~Interface();
    void launch();
    int getCurrentTime() {
        return current_time;
    }
private:
    Warehouse* _whouse;
    std::vector<Trucks*> trucks;
    Manager manager;
    sf::RenderWindow _window;
    sf::Font _font;
    unsigned int _font_size;
    std::vector<IButton*> _buttons;
    std::vector<PinButton*> _pin_buttons;
    std::vector<sf::RectangleShape*> _lines;
    std::vector<sf::RectangleShape*> _start_lines;
    std::vector<sf::Text*> _texts;
    std::vector<sf::Text*> _start_texts;
    sf::Text* text_current_date;
    sf::Text* text_current_time;
    int current_date;
    int current_time;
    std::string _status;
    IButton* _current_pressed_button;
    PinButton* _current_entered_button;
    void input();
    void update(float time); //здесь апдейт окна происходит
    void draw();
    void setObject(sf::Vector2f size, sf::Vector2f position);
    void setObject(sf::Vector2f size, sf::Vector2f position, std::string string);
    void startSetObject(sf::Vector2f size, sf::Vector2f position, std::string string);
    void startSetObject(sf::Vector2f size, sf::Vector2f position);
    void incorrectTextInput();
};