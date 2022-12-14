#include "Interface.h"
#include <time.h>

//оепеохяюрэ мю псвмни ббнд хг нймю
int count_of_products = 9;
int count_of_retail_outlets = 3;


Interface::Interface()
{
    sf::Vector2f resolution;
    resolution.x = sf::VideoMode::getDesktopMode().width / 10 * 9;
    resolution.y = sf::VideoMode::getDesktopMode().height / 10 * 9;

    _window.create(sf::VideoMode(resolution.x, resolution.y), "Wholesale warehouse management system", sf::Style::Default);
    _font.loadFromFile("arial.ttf");
    _font_size = 40;
    int coeff_x = resolution.x / 36, coeff_y = resolution.y / 27;
    _buttons.resize(10);
    for (int i = 1; i <= count_of_retail_outlets; i++)
    {
        _buttons[i] = (new IButton(_window, i,
            sf::Vector2f(coeff_x * 3, coeff_y * 3),
            sf::Vector2f(16 * coeff_x + (i - 1) % 3 * coeff_x * 4, 4 * coeff_y + (i - 1) / 3 * coeff_y * 4),
            "ID " + std::to_string(i), _font, _font_size));
    }
    current_date = 0;
    current_time = 0;

    setObject(sf::Vector2f(1, 27 * coeff_y), sf::Vector2f(15 * coeff_x, 0));
    setObject(sf::Vector2f(21 * coeff_x, 1), sf::Vector2f(15 * coeff_x, 16 * coeff_y));
    setObject(sf::Vector2f(1, 16 * coeff_y), sf::Vector2f(28 * coeff_x, 0));
    setObject(sf::Vector2f(8 *coeff_x, 1), sf::Vector2f(28 * coeff_x, 4 * coeff_y));

    setObject(sf::Vector2f(13 * coeff_x, 3 * coeff_y), sf::Vector2f(15 *coeff_x, 0), "SHOPS");
    setObject(sf::Vector2f(8 * coeff_x, 2 * coeff_y), sf::Vector2f(28 * coeff_x, 0), "00.00.0000");
    text_current_date = _texts[_texts.size() - 1];
    setObject(sf::Vector2f(8 * coeff_x, 2 * coeff_y), sf::Vector2f(28 * coeff_x, 2 * coeff_y), "00:00:00");
    text_current_time = _texts[_texts.size() - 1];

    setObject(sf::Vector2f(6 * coeff_x, 6 * coeff_y), sf::Vector2f(29 * coeff_x, 5 * coeff_y));

    setObject(sf::Vector2f(8 * coeff_x, 2 * coeff_y), sf::Vector2f(28 * coeff_x, 11 * coeff_y), "Manager");
    setObject(sf::Vector2f(8 * coeff_x, 2 * coeff_y), sf::Vector2f(28 * coeff_x, 13 * coeff_y), "Natalia Petrovna");

    _buttons[0] = (new IButton(_window, 0,
        sf::Vector2f(coeff_x * 7, coeff_y * 5),
        sf::Vector2f(16 * coeff_x, 17 * coeff_y),
        "WAREHOUSE", _font, _font_size));

    setObject(sf::Vector2f(4 * coeff_x, 5 * coeff_y), sf::Vector2f(24 * coeff_x, 17 * coeff_y));
    setObject(sf::Vector2f(4 * coeff_x, 2 * coeff_y), sf::Vector2f(24 * coeff_x, 17 * coeff_y), "Count of");
    setObject(sf::Vector2f(4 * coeff_x, 2 * coeff_y), sf::Vector2f(24 * coeff_x, 18 * coeff_y), "free cars");
    setObject(sf::Vector2f(4 * coeff_x, 1 * coeff_y), sf::Vector2f(24 * coeff_x, 20 * coeff_y), "10");

    setObject(sf::Vector2f(6 * coeff_x, 3 * coeff_y), sf::Vector2f(29 * coeff_x, 23 * coeff_y));
    setObject(sf::Vector2f(6 * coeff_x, 3 * coeff_y), sf::Vector2f(29 * coeff_x, 23 * coeff_y), "next day");

    setObject(sf::Vector2f(8 * coeff_x, 3 * coeff_y), sf::Vector2f(28 * coeff_x, 18 * coeff_y));
}

Interface::~Interface() {
    for (auto i : _buttons) {
        delete i;
    }
    for (auto i : _lines) {
        delete i;
    }
    for (auto i : _texts) {
        delete i;
    }
}

void Interface::launch()
{
    sf::Clock clock;

    while (_window.isOpen())
    {
        sf::Time dt = clock.restart();
        float dt_as_seconds = dt.asSeconds();
        
        input();
        update(dt_as_seconds);
        draw();
    }
}

void Interface::input()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        _window.close();
    }
    sf::Event event;
    while (_window.pollEvent(event))
    {
        sf::Vector2i position = sf::Mouse::getPosition(_window);
        if (event.type == sf::Event::Closed) _window.close();

        for (auto i : _buttons)
        {
            if (i == nullptr) continue;
            if (i->isInPointArea(position)) {
                i->setStatus(1);
                if (event.type == sf::Event::MouseButtonReleased &&
                    event.mouseButton.button == sf::Mouse::Left)
                {
                    i->setStatus(2);
                    _last_button = i;
                }
                i->getId();
            }
            else
            {
                i->setStatus(0);
            }
        }
        if (_last_button) _last_button->setStatus(2);
    }
}

void Interface::update(float time) 
{
    current_time += 1;
    text_current_time->setString(((current_time / 3600 % 24 < 10)?"0":"") +
        std::to_string(current_time / 3600 % 24) + ":" +
        ((current_time / 60 % 60 < 10) ? "0" : "")
        + std::to_string(current_time / 60 % 60) + ":" +
        ((current_time % 60 < 10) ? "0" : "") +
        std::to_string(current_time % 60));

}

void Interface::draw()
{
    _window.clear(sf::Color::White);
    for (auto i : _buttons) {
        if (i == nullptr) continue;
        i->draw();
    }
    for (auto i : _lines)
    {
        if (i == nullptr) continue;
        _window.draw(*i);
    }
    for (auto i : _texts)
    {
        if (i == nullptr) continue;
        _window.draw(*i);
    }
    _window.display();
}

void Interface::setObject(sf::Vector2f size, sf::Vector2f position)
{
    _lines.push_back(new sf::RectangleShape(size));
    _lines[_lines.size() - 1]->setPosition(position);
    _lines[_lines.size() - 1]->setOutlineColor(sf::Color::Black);
    _lines[_lines.size() - 1]->setOutlineThickness(1);
}

void Interface::setObject(sf::Vector2f size, sf::Vector2f position, std::string string)
{
    _texts.push_back(new sf::Text(string, _font, _font_size));
    _texts[_texts.size() - 1]->setPosition({ position.x + size.x / 2 - _texts[_texts.size() - 1]->getGlobalBounds().width / 2,
        position.y + size.y / 2 - _texts[_texts.size() - 1]->getGlobalBounds().height / 2});
    _texts[_texts.size() - 1]->setFillColor(sf::Color::Black);
}