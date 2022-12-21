#pragma once
#include <SFML/Graphics.hpp>

class PinButton
{
public:
    PinButton(sf::Vector2f size, sf::Vector2f position,
        std::string string, std::string string_date, std::string string_cost, sf::Font font, unsigned int font_size);
    void draw(sf::RenderWindow& window);
    void setStatus();
    bool isInPointArea(sf::Vector2i position);
private:
    sf::Font _font;
    unsigned int _font_size;
    int _status;
    sf::RectangleShape _rect_pin;
    sf::RectangleShape _rect_name;
    sf::RectangleShape _rect_date;
    sf::RectangleShape _rect_cost;
    sf::Text _text_name;
    sf::Text _text_date;
    sf::Text _text_cost;
};

