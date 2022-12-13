#pragma once
#include<SFML/Graphics.hpp>
#include <string>
class IButton
{
public:
    IButton(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size, std::string string);
    IButton(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size, std::string string, sf::Image image);
    void draw();
private:
    sf::Font _font;
    unsigned int _font_size;
    sf::RenderWindow& _window;
    sf::Vector2f _position;
    sf::Vector2f _size;
    sf::Text _text;
    sf::Texture _texture;
    sf::Sprite _sprite;
    sf::Image _image;
    sf::RectangleShape _rect;
};

