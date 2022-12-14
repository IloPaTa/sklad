#include "IButton.h"

IButton::IButton(sf::RenderWindow& window, sf::Vector2f size, sf::Vector2f position,
    std::string string, sf::Font font, unsigned int font_size) :
    _window(window), _size(size), _position(position), _font(font), _font_size(font_size)
{
    _rect.setSize(size);
    _rect.setPosition(position);
    _rect.setOutlineColor(sf::Color::Black);
    _rect.setOutlineThickness(1);

    _text = sf::Text(string, _font, _font_size);
    _text.setPosition({ position.x + size.x / 2 - _text.getGlobalBounds().width / 2,
        position.y + size.y / 2 - _text.getGlobalBounds().height / 2 });
    _text.setFillColor(sf::Color::Black);
}

IButton::IButton(sf::RenderWindow& window, sf::Vector2f size, sf::Vector2f position,
    std::string string, sf::Font font, unsigned int font_size, sf::Image image) :
    _window(window), _size(size), _position(position), _font(font), _font_size(font_size), _image(image)
{
    _texture.loadFromImage(_image);
    _sprite.setTexture(_texture);

    _text = sf::Text(string, _font, _font_size);
    _text.setPosition({ position.x + size.x / 2 - _text.getGlobalBounds().width / 2,
        position.y + size.y / 2 - _text.getGlobalBounds().height / 2 });
    _text.setFillColor(sf::Color::Black);
}

void IButton::draw()
{
    _window.draw(_rect);
    _window.draw(_sprite);
    _window.draw(_text);
}

void IButton::inPointArea()
{
    if (_position.x <= sf::Mouse::getPosition().x <= _position.x + _size.x &&
        _position.y <= sf::Mouse::getPosition().y <= _position.y + _size.y)
        return;

}

void IButton::setStatus()
{

}