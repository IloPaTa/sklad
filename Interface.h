#pragma once
#include <SFML/Graphics.hpp>
#include "IButton.h"
#include "InputField.h"
#include "Manager.h"
#include "Trucks.h"
#include "Warehouse.h"
#include <vector>
#include <string>
#include "Manager.h"

class Interface
{
public:
    Interface();
    ~Interface();
    void launch();
private:
    Warehouse* _whouse;
    Manager _manager;
    sf::RenderWindow _window;
    sf::Font _font;
    unsigned int _font_size;

    //std::vector<sf::RectangleShape*> _start_lines;
    std::vector<sf::Text*> _start_texts;
    std::vector<InputField*> _start_input_fields;

    std::vector<sf::RectangleShape*> _lines;
    std::vector<sf::Text*> _texts;
    std::vector<IButton*> _buttons;
    
    std::vector<sf::Text*> _warehouse_texts;
    
    std::vector<sf::RectangleShape*> _nextday_lines;
    std::vector<sf::Text*> _nextday_texts;
    
    std::vector<sf::Text*> _orders_text;

    sf::Text* _text_current_date;
    int _current_date;
    int _delta_y;
    std::string _event;
    IButton* _current_pressed_button;
    InputField* _current_entered_button;

    std::map<std::wstring, std::pair<int, int>> map;
    std::map<std::wstring, std::pair<int, int>>::iterator it;

    void input();
    void update(); //здесь апдейт окна происходит
    void draw();
    void setObject(sf::Vector2f size, sf::Vector2f position);
    void setObject(sf::Vector2f size, sf::Vector2f position, std::string string);
    void startSetObject(sf::Vector2f size, sf::Vector2f position, std::string string);
    //void startSetObject(sf::Vector2f size, sf::Vector2f position);
    void warehouseSetObject(sf::Vector2f size, sf::Vector2f position, std::string string);
    void nextdaySetObject(sf::Vector2f size, sf::Vector2f position);
    void nextdaySetObject(sf::Vector2f size, sf::Vector2f position, std::string string);
    void orderSetObject(sf::Vector2f size, sf::Vector2f position, std::string string);
    void incorrectTextInput();
    void createMainButtons();
    void createNextdayButtons();
    bool checkName(char c, InputField* value, bool b = 0);
    bool checkDate(char c, InputField* value, bool b = 0);
    bool checkCost(char c, InputField* value, bool b = 0);
    bool checkCnt(char c, InputField* value, bool b = 0);
    bool checkInputField(InputField* value);
};