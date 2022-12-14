 #include "IButton.h"

IButton::IButton(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size, std::string string) :
    _window(window), _position(position), _size(size)
{
    _font.loadFromFile("arial.ttf");
    _font_size = 40;
    _text.setString(string);

    _rect.setSize(size);
    _rect.setPosition(position);
    _rect.setOutlineColor(sf::Color::Black);
    _rect.setOutlineThickness(1);

    _text = sf::Text(string, _font, _font_size);
    _text.setPosition({ position.x + size.x / 2 - _text.getGlobalBounds().width / 2,
        position.y + size.y / 2 - _text.getGlobalBounds().height / 2 });
    _text.setFillColor(sf::Color::Black);
}

IButton::IButton(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size, std::string string, sf::Image image):
    _window(window), _position(position), _size(size), _image(image)
{
    _font.loadFromFile("arial.ttf");
    _font_size = 40;
    _text.setString(string);
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