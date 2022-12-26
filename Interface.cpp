#include "Interface.h"
#include <random>
#include <time.h>
#include <fstream>
//ПЕРЕПИСАТЬ НА РУЧНОЙ ВВОД ИЗ ОКНА
std::mt19937 g(23);
std::uniform_int_distribution<> d;

int count_of_retail_outlets = 9;

std::vector<std::pair<Item*, int>> formNewOrder() {
    int cnt  = d(g) % 10;
    std::ifstream fin;
    fin.open("list_of_products.txt");
    std::string name;
    int data, cost, count;
    std::vector<std::pair<Item*, int>> items;
    while (fin >> name >> data >> cost >> count) {
        if (d(g) % 10 == 0) {
            Item* i = new Item(data, cost, std::wstring(name.begin(), name.end()));
            items.push_back({ i, 233 });
        }
    }
    fin.close();
    return items;
}

Interface::Interface()
{
    sf::Vector2f resolution;
    resolution.x = 1600;
    resolution.y = 900;

    _window.create(sf::VideoMode(resolution.x, resolution.y), "Wholesale warehouse management system", sf::Style::Default);
    _font.loadFromFile("Anonymous_Pro.ttf");
    _font_size = 40;
    _event = "start";

    _manager = Manager();
    _whouse = new Warehouse(5);

    setObject(sf::Vector2f(400, 75), sf::Vector2f(1200, 0), "");
    _current_date = 1;
    _text_current_date = _texts[_texts.size() - 1];

    // заголовки на стартовой странице 
    {
        startSetObject(sf::Vector2f(800, 50), sf::Vector2f(0, 0), "Select the products you need to sell");
        startSetObject(sf::Vector2f(250, 50), sf::Vector2f(50, 50), "Name");
        startSetObject(sf::Vector2f(300, 50), sf::Vector2f(280, 55), "Storage date");
        startSetObject(sf::Vector2f(200, 50), sf::Vector2f(550, 60), "Cost");
        startSetObject(sf::Vector2f(200, 50), sf::Vector2f(850, 60), "Quantity\nin whpackaging");
        startSetObject(sf::Vector2f(800, 50), sf::Vector2f(800, 0), "Enter store names");
    } 
    // товары на стартовой странице
    {int j = 130, k = 50;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Milk", "2 days", "200 RUB", "1", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Burger", "5 weeks", "20 RUB", "2", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Bread", "1 week", "100 RUB", "3", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Salt", "2 months", "10 RUB", "4", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Paper", "1 week", "2000 RUB", "5", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Apple", "1 week", "5200 RUB", "6", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Pineapple", "1 week", "7200 RUB", "7", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Cucumber", "1 week", "5200 RUB", "8", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Tomato", "1 week", "1200 RUB", "1", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Potato", "1 week", "2200 RUB", "1", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Cheese", "1 week", "10 RUB", "1", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Strawberry", "1 week", "2800 RUB", "1", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Strawberry", "1 week", "2800 RUB", "1", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Strawberry", "1 week", "2800 RUB", "1", _font, _font_size));
    j += k;
    _pin_buttons.push_back(new PinButton(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, j),
        "Strawberry", "1 week", "2800 RUB", "1", _font, _font_size));

    _buttons.push_back(new IButton(_window, "start sim",
        sf::Vector2f(400, 50),
        sf::Vector2f(1000, 800),
        "Start simulation", _font, _font_size));
    }
    for (int i = 0; i < 8; i++)
    {
        _pin_buttons[i]->changePin();
    }
    

    nextdaySetObject(sf::Vector2f(1, 900), sf::Vector2f(800, 0));
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
    for (auto i : _pin_buttons) {
        delete i;
    }
    /*for (auto i : _start_lines) {
        delete i;
    }*/
    for (auto i : _start_texts) {
        delete i;
    }
    for (auto i : _warehouse_texts) {
        delete i;
    }
}

void Interface::launch()
{
    while (_window.isOpen())
    {
        /*sf::Time dt = clock.restart();
        float dt_as_seconds = dt.asSeconds();*/
        input();
        update();
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
        if (_event == "start") {
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
                        _event = "enter name";
                        _current_entered_button = i;
                    }
                    else if (i->isInPointArea(position) == "date") {
                        _event = "enter date";
                        _current_entered_button = i;
                    }
                    else if (i->isInPointArea(position) == "cost") {
                        _event = "enter cost";
                        _current_entered_button = i;
                    }
                    else if (i->isInPointArea(position) == "quantity") {
                        _event = "enter quantity";
                        _current_entered_button = i;
                    }
                }
            }
        }
        if (_event == "enter name")
        {
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == '\b') {
                    if (_current_entered_button->getStringNameRef().size()) _current_entered_button->getStringNameRef().pop_back();
                }
                else if (event.text.unicode == '\r') {
                    if (_current_entered_button->getStringNameRef().size())
                        _event = "start";
                    else incorrectTextInput();
                }
                else if (_current_entered_button->getStringNameRef().size() < 10)
                    _current_entered_button->getStringNameRef() += event.text.unicode;
                _current_entered_button->updateTextName();
            }
        }
        if (_event == "enter date")
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
                        && st && ok && _current_entered_button->getStringDateRef().size()) _event = "start";
                    else incorrectTextInput();
                }
                else { 
                    if (!((event.text.unicode >= 'a' && event.text.unicode <= 'z') || (event.text.unicode >= '0' && event.text.unicode <= '9') || event.text.unicode == ' ')) incorrectTextInput();
                    else if (_current_entered_button->getStringDateRef().size() < 10) _current_entered_button->getStringDateRef() += event.text.unicode;
                }
                _current_entered_button->updateTextDate();
            }
        }
        if (_event == "enter cost")
        {
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == '\b') { if (_current_entered_button->getStringCostRef().size() > 4) _current_entered_button->getStringCostRef().erase(_current_entered_button->getStringCostRef().end() - 5); }
                else if (event.text.unicode == '\r') { if (_current_entered_button->getStringCostRef().size() > 4) _event = "start"; else incorrectTextInput(); }
                else { 
                    if (!(event.text.unicode >= '0' && event.text.unicode <= '9')) incorrectTextInput();
                    else if (_current_entered_button->getStringCostRef().size() < 10) _current_entered_button->getStringCostRef().insert(_current_entered_button->getStringCostRef().end() - 4, event.text.unicode);
                }
                _current_entered_button->updateTextCost();
            }
        }
        if (_event == "enter quantity") {
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == '\b') {
                    if (_current_entered_button->getStringQuantityRef().size()) _current_entered_button->getStringQuantityRef().pop_back();
                }
                else if (event.text.unicode == '\r') {
                    if (_current_entered_button->getStringQuantityRef().size())
                        _event = "start";
                    else incorrectTextInput();
                }
                else {
                    if (!(event.text.unicode >= '0' && event.text.unicode <= '9')) incorrectTextInput();
                    else if (_current_entered_button->getStringQuantityRef().size() < 3)
                        _current_entered_button->getStringQuantityRef() += event.text.unicode;
                }
                _current_entered_button->updateTextQuantity();
            }
        }
        if (_event == "warehouse") {
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                _delta_y += event.mouseWheelScroll.delta* 10;
                if (_delta_y > 0) _delta_y = 0;
            }
            _warehouse_texts.resize(0);
            std::vector<Shelf*> shelfs = _whouse->getShelfs();
            warehouseSetObject(sf::Vector2f(150, 50), sf::Vector2f(30, 10), "Name");
            warehouseSetObject(sf::Vector2f(200, 50), sf::Vector2f(180, 10), "quantity\nin pack");
            warehouseSetObject(sf::Vector2f(150, 50), sf::Vector2f(200 + 150, 10), "days\nleft");
            warehouseSetObject(sf::Vector2f(150, 50), sf::Vector2f(200 + 300, 10), "cost");
            int m = 0, m1 = 100;
            for (int i = 0; i < shelfs.size(); ++i) {
                auto j = shelfs[i];
                if (50 + m + _delta_y >= 0) warehouseSetObject(sf::Vector2f(150, 50), sf::Vector2f(10, m1 + m + _delta_y), "Shell " + std::to_string(i + 1));
                std::vector<Item*> items = j->getItem();
                for (auto k : items) {
                    std::wstring a = k->getName();
                    if (100 + m + _delta_y < 0) { m += 50; continue; }
                    warehouseSetObject(sf::Vector2f(220, 50), sf::Vector2f(0, 50 + m1 + m + _delta_y), std::string(a.begin(), a.end()));
                    warehouseSetObject(sf::Vector2f(150, 50), sf::Vector2f(200, 50 + m1 + m + _delta_y), std::to_string(j->getColItem(k)));
                    warehouseSetObject(sf::Vector2f(150, 50), sf::Vector2f(350, 50 + m1 + m + _delta_y), std::to_string(k->getShelfLife()));
                    warehouseSetObject(sf::Vector2f(150, 50), sf::Vector2f(500, 50 + m1 + m + _delta_y), std::to_string(k->getCost()));
                    m += 50;
                }
                m += 50;
            }
        }
        if (_event == "next day") {
            
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                _delta_y += event.mouseWheelScroll.delta * 10;
                if (_delta_y > 0) _delta_y = 0;
            }
            int m = 100; int j = 0;
            for (auto i : _nextday_texts)
            {
                if (j < 3) {
                    j += 1; 
                    continue;
                }
               // position.y + size.y / 2 - _nextday_texts[_nextday_texts.size() - 1]->getGlobalBounds().height / 2
                i->setPosition(sf::Vector2f(i->getPosition().x, m + _delta_y));
                if (j%3 == 2) m += 50;
                j += 1;
            }
            j = 0;
            m = 100;
            for (auto i : _buttons) {
                if (j == 0) {
                    j += 1;
                    continue;
                }
                if (j % 2 == 0) {
                    i->setPosition(sf::Vector2f(630, m + _delta_y));
                    m += 50;
                }
                else
                {
                    i->setPosition(sf::Vector2f(430, m + _delta_y));
                    
                }
                j += 1;
                
            }
        }
        if (_event.substr(0, 6) == "button") {
            _orders_text.resize(0);
            std::vector<StoreOrder*> store_orders = _manager.getStoreOrders();
            int m = 0;
            for (auto i : store_orders) {
                
                if (std::to_string(i->getId()) != _event.substr(6, 7)) continue;
                std::vector<std::pair<Item*, int>> order_list = i->getOrderList();
                
                for (auto j : order_list) {
                    auto item = j.first;
                    int value = j.second;
                    std::wstring a = item->getName();
                    orderSetObject(sf::Vector2f(200, 50), sf::Vector2f(100, m+100), std::string(a.begin(), a.end()));
                    orderSetObject(sf::Vector2f(200, 50), sf::Vector2f(200, m+100), std::to_string(item->getDateOfCreating().d) + ":" + std::to_string(item->getDateOfCreating().m) + ":" + std::to_string(item->getDateOfCreating().y));
                    orderSetObject(sf::Vector2f(200, 50), sf::Vector2f(300, m+100), std::to_string(item->getShelfLife()));
                    orderSetObject(sf::Vector2f(200, 50), sf::Vector2f(400, m+100), std::to_string(item->getCost()));
                    m += 100;
                }
                m += 100;
            }
        }


        for (auto i : _buttons)
        {
            if (i->isInPointArea(position)) {
                i->setRectColor(1);
                if (event.type == sf::Event::MouseButtonReleased &&
                    event.mouseButton.button == sf::Mouse::Left)
                {
                    i->setRectColor(2);
                    _current_pressed_button = i;

                    _event = i->getId();
                    _delta_y = 0;

                    if (i->getId() == "start sim") {
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
                        fin.close();
                        _manager.addProducts(_whouse, items);

                        createMainButtons();
                        {
                            setObject(sf::Vector2f(1, 900), sf::Vector2f(800, 0));
                            setObject(sf::Vector2f(800, 1), sf::Vector2f(800, 600));
                            setObject(sf::Vector2f(1, 600), sf::Vector2f(1200, 0));
                            setObject(sf::Vector2f(400, 1), sf::Vector2f(1200, 150));

                            setObject(sf::Vector2f(400, 150), sf::Vector2f(800, 0), "SHOPS");

                            /*setObject(sf::Vector2f(400, 75), sf::Vector2f(1200, 75), "00:00:00");
                            text_current_time = _texts[_texts.size() - 1];*/

                            setObject(sf::Vector2f(250, 250), sf::Vector2f(1275, 200));

                            setObject(sf::Vector2f(400, 75), sf::Vector2f(1200, 450), "Manager");
                            setObject(sf::Vector2f(400, 75), sf::Vector2f(1200, 500), "Natalia Petrovna");

                        }
                        _event = "main";
                    }
                    else if (i->getId() == "warehouse") {
                        _delta_y = 0;
                        _warehouse_texts.resize(0);
                        std::vector<Shelf*> shelfs = _whouse->getShelfs();
                        warehouseSetObject(sf::Vector2f(150, 50), sf::Vector2f(30, 10), "Name");
                        warehouseSetObject(sf::Vector2f(200, 50), sf::Vector2f(180, 10), "quantity\nin pack");
                        warehouseSetObject(sf::Vector2f(150, 50), sf::Vector2f(200 + 150, 10), "days\nleft");
                        warehouseSetObject(sf::Vector2f(150, 50), sf::Vector2f(200 + 300, 10), "cost");
                        int m = 0, m1 = 100;
                        for (int i = 0; i < shelfs.size(); ++i) {
                            auto j = shelfs[i];
                            if (50 + m + _delta_y >= 0) warehouseSetObject(sf::Vector2f(150, 50), sf::Vector2f(10, m1 + m + _delta_y), "Shell " + std::to_string(i + 1));
                            std::vector<Item*> items = j->getItem();
                            for (auto k : items) {
                                std::wstring a = k->getName();
                                if (100 + m + _delta_y < 0) { m += 50; continue; }
                                warehouseSetObject(sf::Vector2f(220, 50), sf::Vector2f(0, 50 + m1 + m + _delta_y), std::string(a.begin(), a.end()));
                                warehouseSetObject(sf::Vector2f(150, 50), sf::Vector2f(200, 50 + m1 + m + _delta_y), std::to_string(j->getColItem(k)));
                                warehouseSetObject(sf::Vector2f(150, 50), sf::Vector2f(350, 50 + m1 + m + _delta_y), std::to_string(k->getShelfLife()));
                                warehouseSetObject(sf::Vector2f(150, 50), sf::Vector2f(500, 50 + m1 + m + _delta_y), std::to_string(k->getCost()));
                                m += 50;
                            }
                            m += 50;
                        }
                        _event = "warehouse";
                    }
                    else if (i->getId() == "next day") {
                        _manager.processOrder(_whouse);
                        _whouse->updateItems();
                        createNextdayButtons();
                        _event = "next day";

                        _delta_y = 0;
                        map = _manager.funcShortage(_whouse);
                        it = map.begin();
                        //std::cout << map.size() << '\n';
                        int m = 0;
                        _nextday_texts.resize(0);
                        nextdaySetObject(sf::Vector2f(150, 50), sf::Vector2f(0, 0), "Name");
                        nextdaySetObject(sf::Vector2f(150, 50), sf::Vector2f(150, 0), "avail");
                        nextdaySetObject(sf::Vector2f(200, 50), sf::Vector2f(250, 0), "req");


                        m += 100;
                        _buttons.resize(1);
                        for (int i = 1; it != map.end(); it++, i++) {
                            //std::cout << _delta_y << '\n';
                            if (m + _delta_y < 0) continue;
                            nextdaySetObject(sf::Vector2f(200, 50), sf::Vector2f(0, m + _delta_y), std::string(it->first.begin(), it->first.end()));
                            nextdaySetObject(sf::Vector2f(150, 50), sf::Vector2f(150, m + _delta_y), std::to_string(it->second.first));
                            nextdaySetObject(sf::Vector2f(200, 50), sf::Vector2f(250, m + _delta_y), std::to_string(it->second.second));
                            _buttons.push_back(new IButton(_window, "auto" + std::to_string(i),
                                sf::Vector2f(150, 40),
                                sf::Vector2f(430, m + _delta_y),
                                "auto", _font, _font_size));
                            _buttons.push_back(new IButton(_window, "manu" + std::to_string(i),
                                sf::Vector2f(150, 40),
                                sf::Vector2f(630, m + _delta_y),
                                "manual", _font, _font_size));
                            m += 50;
                        }




                        _manager.getProductsFromWhOrder(_whouse);
                        int n = 4;
                        std::vector<StoreOrder*> ord;
                        for (int i = 0; i < n; ++i) {
                            StoreOrder* newOrder = new StoreOrder(i);
                            newOrder->setOrderList(formNewOrder());
                            ord.push_back(newOrder);
                        }
                        _manager.addNewOrder(ord);
                        
                    }
                    else if (i->getId() == "done") {
                        _event = "main";
                        createMainButtons();
                    }
                    else if (i->getId().substr(0, 6) == "button") {
                        _event = i->getId();
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

void Interface::update() 
{
    _text_current_date->setString("The " + std::to_string(_current_date) + " day");
    //current_time += 1;
    /*text_current_time->setString(((current_time / 3600 % 24 < 10)?"0":"") +
        std::to_string(current_time / 3600 % 24) + ":" +
        ((current_time / 60 % 60 < 10) ? "0" : "")
        + std::to_string(current_time / 60 % 60) + ":" +
        ((current_time % 60 < 10) ? "0" : "") +
        std::to_string(current_time % 60));*/

}

void Interface::draw()
{
    _window.clear(sf::Color(255, 235, 228));
    for (auto i : _buttons)
    {
        i->draw();
    }
    if (_event == "start" || _event == "enter name" || _event == "enter date" || _event == "enter cost" || _event == "enter quantity")
    {
        for (auto i : _pin_buttons)
        {
            i->draw(_window);
        }
        for (auto i : _start_texts)
        {
            _window.draw(*i);
        }
        /*for (auto i : _start_lines)
        {
            _window.draw(*i);
        }*/
    }
    if (_event == "main" || _event == "warehouse" || _event.substr(0, 6) == "button")
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
    if (_event == "warehouse")
    {
        for (auto i : _warehouse_texts)
        {
            _window.draw(*i);
        }
    }
    if (_event == "next day")
    {
        for (auto i : _nextday_texts)
        {
            _window.draw(*i);
        }
        for (auto i : _nextday_lines)
        {
            _window.draw(*i);
        }
    }
    if (_event.substr(0, 6) == "button") {
        for (auto i : _orders_text) {
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

//void Interface::startSetObject(sf::Vector2f size, sf::Vector2f position)
//{
//    _start_lines.push_back(new sf::RectangleShape(size));
//    _start_lines[_start_lines.size() - 1]->setPosition(position);
//    _start_lines[_start_lines.size() - 1]->setOutlineColor(sf::Color::Black);
//    _start_lines[_start_lines.size() - 1]->setOutlineThickness(1);
//}

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

void Interface::nextdaySetObject(sf::Vector2f size, sf::Vector2f position)
{
    _nextday_lines.push_back(new sf::RectangleShape(size));
    _nextday_lines[_nextday_lines.size() - 1]->setPosition(position);
    _nextday_lines[_nextday_lines.size() - 1]->setOutlineColor(sf::Color::Black);
    _nextday_lines[_nextday_lines.size() - 1]->setOutlineThickness(1);
}

void Interface::nextdaySetObject(sf::Vector2f size, sf::Vector2f position, std::string string)
{
    _nextday_texts.push_back(new sf::Text(string, _font, _font_size));
    _nextday_texts[_nextday_texts.size() - 1]->setPosition({ position.x + size.x / 2 - _nextday_texts[_nextday_texts.size() - 1]->getGlobalBounds().width / 2,
        position.y});
    _nextday_texts[_nextday_texts.size() - 1]->setFillColor(sf::Color::Black);
}

void Interface::createMainButtons()
{
    _buttons.resize(0);
    for (int i = 0; i < count_of_retail_outlets; i++)
    {
        _buttons.push_back(new IButton(_window, "button" + std::to_string(i + 1),
            sf::Vector2f(100, 100),
            sf::Vector2f(25 + 800 + i % 3 * 125, 50 + 150 + i / 3 * 125),
            "ID " + std::to_string(i + 1), _font, _font_size));
    }


    _buttons.push_back(new IButton(_window, "warehouse",
        sf::Vector2f(225, 150),
        sf::Vector2f(825, 675),
        "WAREHOUSE", _font, _font_size));

    _buttons.push_back(new IButton(_window, "next day",
        sf::Vector2f(225, 150),
        sf::Vector2f(1200 + 150, 675),
        "next day", _font, _font_size));
}

void Interface::createNextdayButtons()
{
    _buttons.resize(0);

    _buttons.push_back(new IButton(_window, "done",
        sf::Vector2f(200, 150),
        sf::Vector2f(1000, 675),
        "Done", _font, _font_size));
}

void Interface::orderSetObject(sf::Vector2f size, sf::Vector2f position, std::string string)
{
    _orders_text.push_back(new sf::Text(string, _font, _font_size));
    _orders_text[_orders_text.size() - 1]->setPosition({ position.x + size.x / 2 - _orders_text[_orders_text.size() - 1]->getGlobalBounds().width / 2,
        position.y });
    _orders_text[_orders_text.size() - 1]->setFillColor(sf::Color::Black);
}