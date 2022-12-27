#include "InputButton.h"
#include <iostream>

InputButton::InputButton(sf::Vector2f size, sf::Vector2f position,
    std::string string, sf::Font font, unsigned int font_size, std::string name) :
    _font(font), _font_size(font_size), _string(string), _position(position), _size(size), _string_name(name)
{

    _text = sf::Text(string, _font, _font_size);
    _text.setPosition(sf::Vector2f(position.x + size.x / 2 - _text.getGlobalBounds().width / 2,
        position.y + size.y / 2 - _text.getGlobalBounds().height / 2 - 13));
    _text.setFillColor(sf::Color::Black);
    _rect.setSize(size);
    _rect.setPosition(position);
    _rect.setFillColor(sf::Color::Transparent);
    
    _text_name = sf::Text(name, _font, _font_size);
    _text_name.setPosition(sf::Vector2f(position.x + size.x / 2 - _text_name.getGlobalBounds().width / 2,
        position.y + size.y / 2 - _text_name.getGlobalBounds().height / 2 - 13 - 50));
    _text_name.setFillColor(sf::Color::Black);
}

void InputButton::draw(sf::RenderWindow& window)
{
    window.draw(_rect);
    window.draw(_text);
    window.draw(_text_name);
}

std::string InputButton::isInPointArea(sf::Vector2i position)
{
    if (_rect.getGlobalBounds().contains(sf::Vector2f(position))) {
        _rect.setFillColor(sf::Color(204, 255, 255));
        return "1";
    }
    else {
        _rect.setFillColor(sf::Color::Transparent);
        return "none";
    }
}

void InputButton::setPosition(sf::Vector2f position)
{
    _position = position;
    _text.setPosition(sf::Vector2f(position.x + 50 + 250 / 2 - _text.getGlobalBounds().width / 2,
        position.y - _text.getGlobalBounds().height / 2 + 13));
    _rect.setPosition(position.x + 50, position.y);
}