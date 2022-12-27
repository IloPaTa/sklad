 #include "IButton.h"

IButton::IButton(sf::RenderWindow& window, std::string id, sf::Vector2f size, sf::Vector2f position,
    std::string string, sf::Font font, unsigned int font_size) :
    _window(window), _id(id), _size(size), _position(position), _start_position(position), _font(font), _font_size(font_size)
{
    _rect.setSize(size);
    _rect.setPosition(position);
    _rect.setOutlineColor(sf::Color::Black);
    _rect.setOutlineThickness(1);

    _text = sf::Text(string, _font, _font_size);
    _text.setPosition({ position.x + size.x / 2 - _text.getGlobalBounds().width / 2,
        position.y + size.y / 2 - _text.getGlobalBounds().height / 2 - 13});
    _text.setFillColor(sf::Color::Black);
}

IButton::IButton(sf::RenderWindow& window, std::string id, sf::Vector2f size, sf::Vector2f position,
    std::string string, sf::Font font, unsigned int font_size, sf::Image image) :
    _window(window), _id(id), _size(size), _position(position), _font(font), _font_size(font_size), _image(image)
{
    _texture.loadFromImage(_image);
    _sprite.setTexture(_texture);

    _text = sf::Text(string, _font, _font_size);
    _text.setPosition({ position.x + (int)size.x / 2 - _text.getGlobalBounds().width / 2,
        position.y + (int)size.y / 2 - _text.getGlobalBounds().height / 2 });
    _text.setFillColor(sf::Color::Black);
}

void IButton::draw()
{
    _window.draw(_rect);
    _window.draw(_sprite);
    _window.draw(_text);
}

std::string IButton::getId()
{
    return _id;
}

bool IButton::isInPointArea(sf::Vector2i position)
{
    return _rect.getGlobalBounds().contains(sf::Vector2f(position));
}

void IButton::setRectColor(int status)
{
    if (status == 0) _rect.setFillColor(sf::Color::White);
    else if (status == 1) _rect.setFillColor(sf::Color(204, 255, 255));
    else _rect.setFillColor(sf::Color(89, 107, 255));
}

void IButton::setPosition(sf::Vector2f position)
{
    _position = position;
    _rect.setPosition(position);

    _text.setPosition({ position.x + _rect.getGlobalBounds().width / 2 - _text.getGlobalBounds().width / 2,
        position.y + _rect.getGlobalBounds().height / 2 - _text.getGlobalBounds().height / 2 - 13 });
}