#include "InputField.h"
#include <iostream>

InputField::InputField(sf::Vector2f size, sf::Vector2f position,
    std::string string_name, std::string string_date, std::string string_cost, std::string string_quantity, sf::Font font, unsigned int font_size):
    _font(font), _font_size(font_size), _string_name(string_name), _string_date(string_date), _string_cost(string_cost), _string_quantity(string_quantity), _position(position), _start_position(position)
{
   
    _text_name = sf::Text(string_name, _font, _font_size);
    _text_name.setPosition(sf::Vector2f(position.x + 50 + 250 / 2 - _text_name.getGlobalBounds().width / 2,
        position.y + size.y / 2 - _text_name.getGlobalBounds().height / 2 - 13));
    _text_name.setFillColor(sf::Color::Black);
    _rect_name.setSize(sf::Vector2f(250, 50));
    _rect_name.setPosition(position.x + 50, position.y);
    _rect_name.setFillColor(sf::Color::Transparent);

    _text_date = sf::Text(string_date, _font, _font_size);
    _text_date.setPosition(position.x + 50 + 250 + 300 / 2 - _text_date.getGlobalBounds().width / 2,
        position.y + size.y / 2 - _text_date.getGlobalBounds().height / 2 - 13);
    _text_date.setFillColor(sf::Color::Black);
    _rect_date.setSize(sf::Vector2f(300, 50));
    _rect_date.setPosition(position.x + 50 + 250, position.y);
    _rect_date.setFillColor(sf::Color::Transparent);

    _text_cost = sf::Text(string_cost, _font, _font_size);
    _text_cost.setPosition(position.x + 50 + 250 + 300 + 200 / 2 - _text_cost.getGlobalBounds().width / 2,
        position.y + size.y / 2 - _text_cost.getGlobalBounds().height / 2 - 13);
    _text_cost.setFillColor(sf::Color::Black);
    _rect_cost.setSize(sf::Vector2f(200, 50));
    _rect_cost.setPosition(position.x + 50 + 250 + 300, position.y);
    _rect_cost.setFillColor(sf::Color::Transparent);

    _text_quantity = sf::Text(string_quantity, _font, _font_size);
    _text_quantity.setPosition(position.x + 50 + 250 + 300 + 200 + 100 / 2 - _text_quantity.getGlobalBounds().width / 2,
        position.y + size.y / 2 - _text_cost.getGlobalBounds().height / 2 - 13);
    _text_quantity.setFillColor(sf::Color::Black);
    _rect_quantity.setSize(sf::Vector2f(100, 50));
    _rect_quantity.setPosition(position.x + 50 + 250 + 300 + 200, position.y);
    _rect_quantity.setFillColor(sf::Color::Transparent);
}

void InputField::draw(sf::RenderWindow& window)
{
    window.draw(_rect_name);
    window.draw(_rect_date);
    window.draw(_rect_cost);
    window.draw(_rect_quantity);
    window.draw(_text_name);
    window.draw(_text_date);
    window.draw(_text_cost);
    window.draw(_text_quantity);
}

std::string InputField::isInPointArea(sf::Vector2i position)
{
    if (_rect_name.getGlobalBounds().contains(sf::Vector2f(position))) {
        _rect_name.setFillColor(sf::Color(204, 255, 255));
        _rect_date.setFillColor(sf::Color::Transparent);
        _rect_cost.setFillColor(sf::Color::Transparent);
        _rect_quantity.setFillColor(sf::Color::Transparent);
        return "name";
    }
    else if (_rect_date.getGlobalBounds().contains(sf::Vector2f(position))) {
        _rect_name.setFillColor(sf::Color::Transparent);
        _rect_date.setFillColor(sf::Color(204, 255, 255));
        _rect_cost.setFillColor(sf::Color::Transparent);
        return "date";
    }
    else if (_rect_cost.getGlobalBounds().contains(sf::Vector2f(position))) {
        _rect_name.setFillColor(sf::Color::Transparent);
        _rect_date.setFillColor(sf::Color::Transparent);
        _rect_cost.setFillColor(sf::Color(204, 255, 255));
        _rect_quantity.setFillColor(sf::Color::Transparent);
        return "cost";
    }
    else if (_rect_quantity.getGlobalBounds().contains(sf::Vector2f(position))) {
        _rect_name.setFillColor(sf::Color::Transparent);
        _rect_date.setFillColor(sf::Color::Transparent);
        _rect_cost.setFillColor(sf::Color::Transparent);
        _rect_quantity.setFillColor(sf::Color(204, 255, 255));
        return "quantity";
    }
    else {
        _rect_name.setFillColor(sf::Color::Transparent);
        _rect_date.setFillColor(sf::Color::Transparent);
        _rect_cost.setFillColor(sf::Color::Transparent);
        _rect_quantity.setFillColor(sf::Color::Transparent);
        return "none";
    }
}

std::string& InputField::getStringNameRef()
{
    return _string_name;
}

std::string& InputField::getStringDateRef()
{
    return _string_date;
}

std::string& InputField::getStringCostRef()
{
    return _string_cost;
}

std::string& InputField::getStringQuantityRef()
{
    return _string_quantity;
}

void InputField::updateTextName()
{
    _text_name.setString(_string_name);
    _text_name.setPosition(sf::Vector2f(50 + 250 / 2 - _text_name.getGlobalBounds().width / 2, _text_name.getPosition().y));
}

void InputField::updateTextDate()
{
    _text_date.setString(_string_date);
    _text_date.setPosition(sf::Vector2f(50 + 250 + 300 / 2 - _text_date.getGlobalBounds().width / 2, _text_date.getPosition().y));
}

void InputField::updateTextCost()
{
    _text_cost.setString(_string_cost);
    _text_cost.setPosition(sf::Vector2f(50 + 250 + 300 + 200 / 2 - _text_cost.getGlobalBounds().width / 2, _text_cost.getPosition().y));
}

void InputField::updateTextQuantity()
{
    _text_quantity.setString(_string_quantity);
    _text_quantity.setPosition(sf::Vector2f(50 + 250 + 300 + 200 + 100 / 2 - _text_quantity.getGlobalBounds().width / 2, _text_quantity.getPosition().y));
}

void InputField::setPosition(sf::Vector2f position)
{
    _position = position;
    _text_name.setPosition(sf::Vector2f(position.x + 50 + 250 / 2 - _text_name.getGlobalBounds().width / 2,
        position.y - _text_name.getGlobalBounds().height / 2 + 13));
    _rect_name.setPosition(position.x + 50, position.y);
    _text_date.setPosition(position.x + 50 + 250 + 300 / 2 - _text_date.getGlobalBounds().width / 2,
        position.y + _rect_date.getGlobalBounds().height / 2 - _text_date.getGlobalBounds().height / 2 - 13);
    _rect_date.setPosition(position.x + 50 + 250, position.y);
    _text_cost.setPosition(position.x + 50 + 250 + 300 + 200 / 2 - _text_cost.getGlobalBounds().width / 2,
        position.y + _rect_cost.getGlobalBounds().height / 2 - _text_cost.getGlobalBounds().height / 2 - 13);
    _rect_cost.setPosition(position.x + 50 + 250 + 300, position.y);
    _text_quantity.setPosition(position.x + 50 + 250 + 300 + 200 + 100 / 2 - _text_quantity.getGlobalBounds().width / 2,
        position.y + _rect_quantity.getGlobalBounds().height / 2 - _text_cost.getGlobalBounds().height / 2 - 13);
    _rect_quantity.setPosition(position.x + 50 + 250 + 300 + 200, position.y);
}