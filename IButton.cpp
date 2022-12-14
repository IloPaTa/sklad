 #include "IButton.h"

IButton::IButton(sf::RenderWindow& window, int id, sf::Vector2f size, sf::Vector2f position,
    std::string string, sf::Font font, unsigned int font_size) :
    _window(window), _id(id), _size(size), _position(position), _font(font), _font_size(font_size)
{
    _rect.setSize(size);
    _rect.setPosition(position);
    _rect.setOutlineColor(sf::Color::Black);
    _rect.setOutlineThickness(1);

    _text = sf::Text(string, _font, _font_size);
    _text.setPosition({ position.x + size.x / 2 - _text.getGlobalBounds().width / 2,
        position.y + size.y / 2 - _text.getGlobalBounds().height / 2 });
    _text.setFillColor(sf::Color::Black);
    _isAlive = false;
}

IButton::IButton(sf::RenderWindow& window, int id, sf::Vector2f size, sf::Vector2f position,
    std::string string, sf::Font font, unsigned int font_size, sf::Image image) :
    _window(window), _id(id), _size(size), _position(position), _font(font), _font_size(font_size), _image(image)
{
    _texture.loadFromImage(_image);
    _sprite.setTexture(_texture);

    _text = sf::Text(string, _font, _font_size);
    _text.setPosition({ position.x + size.x / 2 - _text.getGlobalBounds().width / 2,
        position.y + size.y / 2 - _text.getGlobalBounds().height / 2 });
    _text.setFillColor(sf::Color::Black);
    _isAlive = false;
}

void IButton::draw()
{
    _window.draw(_rect);
    _window.draw(_sprite);
    _window.draw(_text);
}

int IButton::getId()
{
    return _id;
}

bool IButton::isInPointArea(sf::Vector2i position)
{
    return _rect.getGlobalBounds().contains(sf::Vector2f(position));
}

void IButton::setStatus(int status)
{
    if (status == 0) _rect.setFillColor(sf::Color::White);
    else if (status == 1) _rect.setFillColor(sf::Color::Yellow);
    else _rect.setFillColor(sf::Color::Red);
}

void IButton::changeLifeStatus()
{
    _isAlive = !_isAlive;
}

bool IButton::getLifeStatus()
{
    return _isAlive;
}