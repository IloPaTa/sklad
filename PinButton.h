#pragma once
#include <SFML/Graphics.hpp>

class PinButton
{
public:
    PinButton(sf::Vector2f size, sf::Vector2f position,
        std::string string, std::string string_date, std::string string_cost, sf::Font font, unsigned int font_size);
    void draw(sf::RenderWindow& window);
    void changePin();
    std::string isInPointArea(sf::Vector2i position);
    std::string& getStringNameRef();
    void updateTextName();
    std::string& getStringDateRef();
    void updateTextDate();
    std::string& getStringCostRef();
    void updateTextCost();
    std::string getStringName() {
        return _string_name;
    }
    std::string getStringDate() {
        return _string_date;
    }
    std::string getStringCost() {
        return _string_cost;
    }
    int getStatus() { return _status; }

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
    std::string _string_name;
    std::string _string_date;
    std::string _string_cost;
};