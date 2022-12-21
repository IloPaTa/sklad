#include "PinButton.h"
#include <iostream>

PinButton::PinButton(sf::Vector2f size, sf::Vector2f position,
    std::string string_name, std::string string_date, std::string string_cost, sf::Font font, unsigned int font_size):
    _font(font), _font_size(font_size)
{
    _rect_pin.setSize(sf::Vector2f(30, 30));
    _rect_pin.setPosition(sf::Vector2f(position.x + 10, position.y + 10));
    _rect_pin.setFillColor(sf::Color(255, 52, 59));
    _rect_pin.setOutlineColor(sf::Color::Black);
    _rect_pin.setOutlineThickness(1);
    
    _text_name = sf::Text(string_name, _font, _font_size);
    _text_name.setPosition(sf::Vector2f(position.x + 50 + 350 / 2 - _text_name.getGlobalBounds().width / 2,
        position.y + size.y / 2 - _text_name.getGlobalBounds().height / 2 - 13));
    _text_name.setFillColor(sf::Color::Black);
    _rect_name.setSize(sf::Vector2f(350, 50));
    _rect_name.setPosition(position.x + 50, position.y);
    _rect_name.setFillColor(sf::Color(204, 255, 255));

    _text_date = sf::Text(string_date, _font, _font_size);
    _text_date.setPosition(position.x + 50 + 350 + 200 / 2 - _text_date.getGlobalBounds().width / 2,
        position.y + size.y / 2 - _text_date.getGlobalBounds().height / 2 - 13);
    _text_date.setFillColor(sf::Color::Black);

    _text_cost = sf::Text(string_cost, _font, _font_size);
    _text_cost.setPosition(position.x + 50 + 350 + 200 + 200 / 2 - _text_cost.getGlobalBounds().width / 2,
        position.y + size.y / 2 - _text_cost.getGlobalBounds().height / 2 - 13);
    _text_cost.setFillColor(sf::Color::Black);

    _status = 0;
}

void PinButton::draw(sf::RenderWindow& window)
{
    window.draw(_rect_pin);
    window.draw(_rect_name);
    window.draw(_text_name);
    window.draw(_text_date);
    window.draw(_text_cost);
}

void PinButton::setStatus()
{
    if (_status == 0) {
        _rect_pin.setFillColor(sf::Color(0, 255, 55));
        _status = 1;
    }
    else
    {
        _rect_pin.setFillColor(sf::Color(255, 52, 59));
        _status = 0;
    }
    
}

bool PinButton::isInPointArea(sf::Vector2i position)
{
    return _rect_pin.getGlobalBounds().contains(sf::Vector2f(position));
}