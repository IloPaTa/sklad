#pragma once
#include<SFML/Graphics.hpp>
#include <string>
class IButton
{
public:
    IButton(sf::RenderWindow& window, std::string id, sf::Vector2f size, sf::Vector2f position,
        std::string string, sf::Font font, unsigned int font_size);
    IButton(sf::RenderWindow& window, std::string id, sf::Vector2f size, sf::Vector2f position,
        std::string string, sf::Font font, unsigned int font_size, sf::Image image);
    void draw();
    void setRectColor(std::string status);
    bool isInPointArea(sf::Vector2i position);
    std::string getId();
    void setPosition(sf::Vector2f position);
    void setStartPosition(sf::Vector2f position) {
        _start_position = position;
    }
    sf::Vector2f getPosition() {
        return _position;
    }
    sf::Vector2f getStartPosition() {
        return _start_position;
    }
protected:
    std::string _id;
    sf::Font _font;
    unsigned int _font_size;
    sf::RenderWindow& _window;
    sf::Vector2f _start_position;
    sf::Vector2f _position;
    sf::Vector2f _size;
    sf::Text _text;
    sf::Texture _texture;
    sf::Sprite _sprite;
    sf::Image _image;
    sf::RectangleShape _rect;
};