#pragma once
#include<SFML/Graphics.hpp>
#include <string>
class IButton
{
public:
    IButton(sf::RenderWindow& window, sf::Vector2f size, sf::Vector2f position,
        std::string string, sf::Font font, unsigned int font_size);
    IButton(sf::RenderWindow& window, sf::Vector2f size, sf::Vector2f position,
        std::string string, sf::Font font, unsigned int font_size, sf::Image image);
    void draw();
    void setStatus();
    void inPointArea();
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