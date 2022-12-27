#pragma once
#include <SFML/Graphics.hpp>

class InputField
{
public:
    InputField(sf::Vector2f size, sf::Vector2f position,
        std::string string, std::string string_date, std::string string_cost, std::string string_quantity, sf::Font font, unsigned int font_size);
    void draw(sf::RenderWindow& window);
    std::string isInPointArea(sf::Vector2i position);
    std::string& getStringNameRef();
    void updateTextName();
    std::string& getStringDateRef();
    void updateTextDate();
    std::string& getStringCostRef();
    void updateTextCost();
    std::string& getStringQuantityRef();
    void updateTextQuantity();
    std::string getStringName() {
        return _string_name;
    }
    std::string getStringDate() {
        return _string_date;
    }
    std::string getStringCost() {
        return _string_cost;
    }
    std::string getStringQuantity() {
        return _string_quantity;
    }
    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition() {
        return _position;
    }
    sf::Vector2f getStartPosition() {
        return _start_position;
    }

private:
    sf::Font _font;
    unsigned int _font_size;
    sf::RectangleShape _rect_name;
    sf::RectangleShape _rect_date;
    sf::RectangleShape _rect_cost;
    sf::RectangleShape _rect_quantity;
    sf::Text _text_name;
    sf::Text _text_date;
    sf::Text _text_cost;
    sf::Text _text_quantity;
    std::string _string_name;
    std::string _string_date;
    std::string _string_cost;
    std::string _string_quantity;
    sf::Vector2f _position;
    sf::Vector2f _start_position;
};