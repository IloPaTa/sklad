#pragma once
#include <SFML/Graphics.hpp>

class InputButton
{
public:
    InputButton(sf::Vector2f size, sf::Vector2f position,
        std::string string, sf::Font font, unsigned int font_size, std::string name);
    void draw(sf::RenderWindow& window);
    std::string isInPointArea(sf::Vector2i position);
    std::string getString() {
        return _string;
    }
    std::string& getRefString() {
        return _string;
    }
    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition() {
        return _position;
    }
    void updateText()
    {
        _text.setString(_string);
        _text.setPosition(sf::Vector2f(_position.x + _size.x / 2 - _text.getGlobalBounds().width / 2, _text.getPosition().y));
    }

private:
    sf::Font _font;
    unsigned int _font_size;
    sf::RectangleShape _rect;
    sf::Text _text;
    sf::Text _text_name;
    std::string _string;
    std::string _string_name;
    sf::Vector2f _position;
    sf::Vector2f _size;
};