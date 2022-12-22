#include "Interface.h"
#include <time.h>

//ÏÅÐÅÏÈÑÀÒÜ ÍÀ ÐÓ×ÍÎÉ ÂÂÎÄ ÈÇ ÎÊÍÀ
int count_of_products = 9;
int count_of_retail_outlets = 9;


Interface::Interface()
{
    sf::Vector2f resolution;
    resolution.x = 1600;
    resolution.y = 900;

    _window.create(sf::VideoMode(resolution.x, resolution.y), "Wholesale warehouse management system", sf::Style::Default);
    _font.loadFromFile("Anonymous_Pro.ttf");
    _font_size = 40;
    status = "start";

    startSetObject(sf::Vector2f(800, 50), sf::Vector2f(0, 0), "Select the products you need to sell");
    startSetObject(sf::Vector2f(800, 50), sf::Vector2f(800, 0), "Enter store names");
    int j = 130, k = 50;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Milk", "2 days", "200 RUB", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Burger", "5 weeks", "20 RUB", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Bread", "1 week", "100 RUB", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Salt", "2 months", "10 RUB", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Paper", "24:12:2022", "2000 RUB", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Apple", "25:12:2022", "5200 RUB", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Pineapple", "25:12:2022", "7200 RUB", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Cucumber", "26:12:2022", "5200 RUB", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Tomato", "26:12:2022", "1200 RUB", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Potato", "26:12:2022", "2200 RUB", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Cheese", "28:12:2022", "10 RUB", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Strawberry", "29:12:2022", "2800 RUB", _font, _font_size));

    _buttons.push_back(new IButton(_window, "start",
        sf::Vector2f(400, 50),
        sf::Vector2f(1000, 800),
        "Start simulation", _font, _font_size));
    _buttons[_buttons.size() - 1]->changeLifeStatus();


    
    for (int i = 0; i < count_of_retail_outlets; i++)
    {
        _buttons.push_back(new IButton(_window, std::to_string(i + 1),
            sf::Vector2f(100, 100),
            sf::Vector2f(25 + 800 + i % 3 * 125, 50 + 150 + i / 3 * 125),
            "ID " + std::to_string(i + 1), _font, _font_size));
        //_buttons[i]->changeLifeStatus();
    }
    current_date = 0;
    current_time = 0;

    setObject(sf::Vector2f(1, 900), sf::Vector2f(800, 0));
    setObject(sf::Vector2f(800, 1), sf::Vector2f(800, 600));
    setObject(sf::Vector2f(1, 600), sf::Vector2f(1200, 0));
    setObject(sf::Vector2f(400, 1), sf::Vector2f(1200, 150));

    setObject(sf::Vector2f(400, 150), sf::Vector2f(800, 0), "SHOPS");
    setObject(sf::Vector2f(400, 75), sf::Vector2f(1200, 0), "00.00.0000");
    text_current_date = _texts[_texts.size() - 1];
    setObject(sf::Vector2f(400, 75), sf::Vector2f(1200, 75), "00:00:00");
    text_current_time = _texts[_texts.size() - 1];

    setObject(sf::Vector2f(250, 250), sf::Vector2f(1275, 200));

    setObject(sf::Vector2f(400, 75), sf::Vector2f(1200, 450), "Manager");
    setObject(sf::Vector2f(400, 75), sf::Vector2f(1200, 500), "Natalia Petrovna");

    _buttons.push_back(new IButton(_window, "warehouse",
        sf::Vector2f(225, 150),
        sf::Vector2f(825, 675),
        "WAREHOUSE", _font, _font_size));
    //_buttons[_buttons.size() - 1]->changeLifeStatus();
    
    setObject(sf::Vector2f(200, 150), sf::Vector2f(1075, 675));
    setObject(sf::Vector2f(200, 140), sf::Vector2f(1075, 625), "Count of");
    setObject(sf::Vector2f(200, 130), sf::Vector2f(1075, 675), "free cars");
    setObject(sf::Vector2f(200, 170), sf::Vector2f(1075, 700), "10");

    _buttons.push_back(new IButton(_window, "next day",
        sf::Vector2f(225, 150),
        sf::Vector2f(1200 + 150, 675),
        "next day", _font, _font_size));
    //_buttons[_buttons.size() - 1]->changeLifeStatus();

    
    //setObject(sf::Vector2f(8 * 30, 3 * 30), sf::Vector2f(28 * 30, 18 * 30));
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
        for (auto i : _pin_buttons)
        {
            if (status == "start" && i->isInPointArea(position)) {
                if (event.type == sf::Event::MouseButtonReleased &&
                    event.mouseButton.button == sf::Mouse::Left)
                {
                    i->setStatus();
                }
            }
        }
        for (auto i : _buttons)
        {
            if (!i->getLifeStatus()) continue;
            if (i->isInPointArea(position)) {
                i->setStatus(1);
                if (event.type == sf::Event::MouseButtonReleased &&
                    event.mouseButton.button == sf::Mouse::Left)
                {
                    i->setStatus(2);
                    _current_pressed_button = i;
                    if (i->getId() == "start") {
                        status = "main";
                        for (auto i : _buttons) i->changeLifeStatus();
                    }
                    else if (i->getId() == "warehouse") {
                        status = "warehouse";
                    }
                }
            }
            else
            {
                i->setStatus(0);
            }
        }
        if (_current_pressed_button) _current_pressed_button->setStatus(2);
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
    _window.clear(sf::Color(255, 235, 228));
    for (auto i : _buttons)
    {
        if (!i->getLifeStatus()) continue;
        i->draw();
    }
    if (status == "start") for (auto i : _pin_buttons)
    {
        i->draw(_window);
    }
    if (status != "start") for (auto i : _lines)
    {
        _window.draw(*i);
    }
    if (status != "start") for (auto i : _texts)
    {
        _window.draw(*i);
    }
    if (status == "start") for (auto i : _start_texts)
    {
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

void Interface::startSetObject(sf::Vector2f size, sf::Vector2f position, std::string string)
{
    _start_texts.push_back(new sf::Text(string, _font, _font_size));
    _start_texts[_start_texts.size() - 1]->setPosition({ position.x + size.x / 2 - _start_texts[_start_texts.size() - 1]->getGlobalBounds().width / 2,
        position.y + size.y / 2 - _start_texts[_start_texts.size() - 1]->getGlobalBounds().height / 2 });
    _start_texts[_start_texts.size() - 1]->setFillColor(sf::Color::Black);
}