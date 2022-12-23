#include "Interface.h"
#include <time.h>
#include <fstream>

//ÏÅÐÅÏÈÑÀÒÜ ÍÀ ÐÓ×ÍÎÉ ÂÂÎÄ ÈÇ ÎÊÍÀ
int count_of_products = 9;
int count_of_retail_outlets = 9;


Interface::Interface()
{
    sf::Vector2f resolution;
    resolution.x = 1600;
    resolution.y = 900;
    current_date = 0;

    _window.create(sf::VideoMode(resolution.x, resolution.y), "Wholesale warehouse management system", sf::Style::Default);
    _font.loadFromFile("Anonymous_Pro.ttf");
    _font_size = 40;
    _status = "start";

    _manager = Manager();
    _whouse = new Warehouse(5);
    startSetObject(sf::Vector2f(800, 50), sf::Vector2f(0, 0), "Select the products you need to sell");
    startSetObject(sf::Vector2f(250, 50), sf::Vector2f(50, 50), "Name");
    startSetObject(sf::Vector2f(300, 50), sf::Vector2f(280, 55), "Storage date");
    startSetObject(sf::Vector2f(200, 50), sf::Vector2f(550, 60), "Cost");
    startSetObject(sf::Vector2f(200, 50), sf::Vector2f(850, 60), "Quantity\nin whpackaging");
    startSetObject(sf::Vector2f(800, 50), sf::Vector2f(800, 0), "Enter store names");
    int j = 130, k = 50;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Milk", "2 days", "200 RUB", "1", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Burger", "5 weeks", "20 RUB", "1", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Bread", "1 week", "100 RUB", "1", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Salt", "2 months", "10 RUB", "1", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Paper", "24:12:2022", "2000 RUB", "1", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Apple", "25:12:2022", "5200 RUB", "1", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Pineapple", "25:12:2022", "7200 RUB", "1", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Cucumber", "26:12:2022", "5200 RUB", "1", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Tomato", "26:12:2022", "1200 RUB", "1", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Potato", "26:12:2022", "2200 RUB", "1", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Cheese", "28:12:2022", "10 RUB", "1", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Strawberry", "29:12:2022", "2800 RUB", "1", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Strawberry", "29:12:2022", "2800 RUB", "1", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Strawberry", "29:12:2022", "2800 RUB", "1", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Strawberry", "29:12:2022", "2800 RUB", "1", _font, _font_size));

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
        if (_status == "enter name")
        {
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == '\b') {
                    if (_current_entered_button->getStringNameRef().size()) _current_entered_button->getStringNameRef().pop_back();
                }
                else if (event.text.unicode == '\r') {
                    if (_current_entered_button->getStringNameRef().size())
                        _status = "start";
                    else incorrectTextInput();
                }
                else if (_current_entered_button->getStringNameRef().size() < 10)
                    _current_entered_button->getStringNameRef() += event.text.unicode;
                _current_entered_button->updateTextName();
            }
        }
        if (_status == "enter date")
        {
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == '\b') { if (_current_entered_button->getStringDateRef().size()) _current_entered_button->getStringDateRef().pop_back(); }
                else if (event.text.unicode == '\r')
                {
                    int st = 0; bool ok = true;
                    std::string string = _current_entered_button->getStringDateRef();
                    std::string buf = "";
                    for (int i = 0; i < string.length(); i++)
                    {
                        if (st == 0 && string[i] >= '0' && string[i] <= '9') {
                            ;
                        }
                        else if (st == 0 && string[i] == ' ') {
                            st = 1;
                        }
                        else if (st == 1 && (string[i] >= 'a' && string[i] <= 'z') || (string[i] >= 'A' && string[i] <= 'Z')) {
                            buf += string[i];
                        }
                        else
                        {
                            ok = false;
                        }
                    }
                    std::transform(buf.begin(), buf.end(), buf.begin(), tolower);
                    if ((buf == "d" || buf == "m" || buf == "w" ||
                        buf == "day" || buf == "days" || buf == "week" || buf == "weeks" ||
                        buf == "month" || buf == "months")
                        && st && ok && _current_entered_button->getStringDateRef().size()) _status = "start";
                    else incorrectTextInput();
                }
                else { if (_current_entered_button->getStringDateRef().size() < 10) _current_entered_button->getStringDateRef() += event.text.unicode; }
                _current_entered_button->updateTextDate();
            }
        }
        if (_status == "enter cost")
        {
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == '\b') { if (_current_entered_button->getStringCostRef().size() > 4) _current_entered_button->getStringCostRef().erase(_current_entered_button->getStringCostRef().end() - 5); }
                else if (event.text.unicode == '\r') { if (_current_entered_button->getStringCostRef().size() > 4) _status = "start"; else incorrectTextInput(); }
                else { if (_current_entered_button->getStringCostRef().size() < 10) _current_entered_button->getStringCostRef().insert(_current_entered_button->getStringCostRef().end() - 4, event.text.unicode); }
                _current_entered_button->updateTextCost();
            }
        }
        if (_status == "enter quantity") {
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == '\b') {
                    if (_current_entered_button->getStringQuantityRef().size()) _current_entered_button->getStringQuantityRef().pop_back();
                }
                else if (event.text.unicode == '\r') {
                    if (_current_entered_button->getStringQuantityRef().size())
                        _status = "start";
                    else incorrectTextInput();
                }
                else if (_current_entered_button->getStringQuantityRef().size() < 3)
                    _current_entered_button->getStringQuantityRef() += event.text.unicode;
                _current_entered_button->updateTextQuantity();
            }
        }
        if (_status == "start") {
            for (auto i : _pin_buttons)
            {
                if (i->isInPointArea(position) == "none") continue;
                if (event.type == sf::Event::MouseButtonReleased &&
                    event.mouseButton.button == sf::Mouse::Left)
                {
                    if (i->isInPointArea(position) == "pin") {
                        i->changePin();
                    }
                    else if (i->isInPointArea(position) == "name") {
                        _status = "enter name";
                        _current_entered_button = i;
                    }
                    else if (i->isInPointArea(position) == "date") {
                        _status = "enter date";
                        _current_entered_button = i;
                    }
                    else if (i->isInPointArea(position) == "cost") {
                        _status = "enter cost";
                        _current_entered_button = i;
                    }
                    else if (i->isInPointArea(position) == "quantity") {
                        _status = "enter quantity";
                        _current_entered_button = i;
                    }
                }
            }
        }
        if (_status == "warehouse") {
            _warehouse_texts.resize(0);
            std::vector<Shelf*> shelfs = _whouse->getShelfs();
            int m = 0;
            for (int i = 0; i < shelfs.size(); ++i) {
                auto j = shelfs[i];
                warehouseSetObject(sf::Vector2f(150, 20), sf::Vector2f(0, m), "Shell " + std::to_string(i + 1));
                std::vector<Item*> items = j->getItem();
                for (auto k : items) {
                    std::wstring a = k->getName();
                    warehouseSetObject(sf::Vector2f(150, 50), sf::Vector2f(0, 30 + m), std::string(a.begin(), a.end()));
                    warehouseSetObject(sf::Vector2f(150, 50), sf::Vector2f(150, 30 + m), std::to_string(k->getDateOfCreating().d) + ":" + std::to_string(k->getDateOfCreating().m) + ":" + std::to_string(k->getDateOfCreating().y));
                    warehouseSetObject(sf::Vector2f(150, 50), sf::Vector2f(300, 30 + m), std::to_string(k->getShelfLife()));
                    warehouseSetObject(sf::Vector2f(150, 50), sf::Vector2f(450, 30 + m), std::to_string(k->getCost()));
                    m += 80;
                }
                m += 100;
            }
        }
        for (auto i : _buttons)
        {
            if (!i->getLifeStatus()) continue;
            if (i->isInPointArea(position)) {
                i->setRectColor(1);
                if (event.type == sf::Event::MouseButtonReleased &&
                    event.mouseButton.button == sf::Mouse::Left)
                {
                    i->setRectColor(2);
                    _current_pressed_button = i;
                    if (i->getId() == "start") {
                        std::ofstream out;
                        out.open("list_of_products.txt");
                        for (auto i : _pin_buttons)
                        {
                            std::string date = i->getStringDate();
                            int days = 0;
                            for (int i = 0; i < date.size(); i++)
                            {
                                if (date[i] >= '0' && date[i] <= '9') days = days * 10 + date[i] - '0';
                                else {
                                    if (date[i + 1] == 'd' || date[i + 1] == 'D') days *= 1;
                                    if (date[i + 1] == 'm' || date[i + 1] == 'M') days *= 30;
                                    if (date[i + 1] == 'w' || date[i + 1] == 'W') days *= 7;
                                }
                            }
                            for (int j = 0; j < 4; j++) i->getStringCostRef().pop_back();
                            if (i->getStatus()) out << i->getStringName() << ' ' << days << ' ' << i->getStringCost() << ' ' << i->getStringQuantity() << '\n';
                        }
                        out.close();
                        std::ifstream fin;
                        fin.open("list_of_products.txt");
                        std::string name;
                        int data, cost, count;
                        std::vector<std::pair<Item*, int>> items;
                        while (fin >> name >> data >> cost >> count) {
                            Item* i = new Item(data, cost, std::wstring(name.begin(), name.end()));
                            items.push_back({ i, count });
                        }
                        _manager.addProducts(_whouse, items);
                        _status = "main";
                        for (auto i : _buttons) i->changeLifeStatus();
                    }
                    else if (i->getId() == "warehouse") {
                        _status = "warehouse";
                    }
                    else if (i->getId() == "next day") {
                        _whouse->updateItems();
                        std::map<std::wstring, std::pair<int, int>> map = _manager.funcShortage(_whouse);
                        std::map<std::wstring, std::pair<int, int>>::iterator it = map.begin();
                        for (int i = 0; it != map.end(); it++, i++) {
                            std::cout << std::string(it->first.begin(), it->first.end()) << ' ' << it->second.first << it->second.second << '\n';
                        }
                        _status = "shortage";
                    }
                }
            }
            else
            {
                i->setRectColor(0);
            }
        }
        if (_current_pressed_button) _current_pressed_button->setRectColor(2);
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
    if (_status == "start" || _status == "enter name" || _status == "enter date" || _status == "enter cost" || _status == "enter quantity")
    {
        for (auto i : _pin_buttons)
        {
            i->draw(_window);
        }
        for (auto i : _start_texts)
        {
            _window.draw(*i);
        }
        for (auto i : _start_lines)
        {
            _window.draw(*i);
        }
    }
    if (_status == "main" || _status == "warehouse")
    {
        for (auto i : _lines)
        {
            _window.draw(*i);
        }
        for (auto i : _texts)
        {
            _window.draw(*i);
        }
    }
    if (_status == "warehouse")
    {
        for (auto i : _warehouse_texts)
        {
            _window.draw(*i);
        }
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

void Interface::startSetObject(sf::Vector2f size, sf::Vector2f position)
{
    _start_lines.push_back(new sf::RectangleShape(size));
    _start_lines[_start_lines.size() - 1]->setPosition(position);
    _start_lines[_start_lines.size() - 1]->setOutlineColor(sf::Color::Black);
    _start_lines[_start_lines.size() - 1]->setOutlineThickness(1);
}

void Interface::incorrectTextInput()
{
    sf::RenderWindow err_window(sf::VideoMode(600, 100), "", sf::Style::None);
    sf::Text txt = sf::Text("Incorrect text input\npress any key to continue", _font, _font_size);
    txt.setPosition(30, 0);
    err_window.draw(txt);
    err_window.display();
    while (err_window.isOpen())
    {
        sf::Event err_event;
        while (err_window.pollEvent(err_event))
        {
            if (err_event.type == sf::Event::TextEntered) err_window.close();
        }
    }
}

void Interface::warehouseSetObject(sf::Vector2f size, sf::Vector2f position, std::string string)
{
    _warehouse_texts.push_back(new sf::Text(string, _font, _font_size));
    _warehouse_texts[_warehouse_texts.size() - 1]->setPosition({ position.x + size.x / 2 - _warehouse_texts[_warehouse_texts.size() - 1]->getGlobalBounds().width / 2,
        position.y + size.y / 2 - _warehouse_texts[_warehouse_texts.size() - 1]->getGlobalBounds().height / 2 });
    _warehouse_texts[_warehouse_texts.size() - 1]->setFillColor(sf::Color::Black);
}