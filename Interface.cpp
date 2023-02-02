#include "Interface.h"
#include <random>
#include <time.h>
#include <fstream>
//ѕ≈–≈ѕ»—ј“№ Ќј –”„Ќќ… ¬¬ќƒ »« ќ Ќј
//количество полок и ограничени¤ на полки сумма и количество магазов
std::mt19937 g(23);
std::uniform_int_distribution<> d;

std::vector<std::pair<Item*, int>> formNewOrder() {
    std::ifstream fin;
    fin.open("list_of_products.txt");
    std::string name;
    int data, cost, count;
    std::vector<std::pair<Item*, int>> items;
    while (fin >> name >> data >> cost >> count) {
        if (d(g) % 2 == 0) {
            int cnt = d(g) % 10;
            Item* i = new Item(data, cost, std::wstring(name.begin(), name.end()));
            items.push_back({ i, cnt });
        }
    }
    fin.close();
    return items;
}

Interface::Interface() {
    sf::Vector2f resolution;
    resolution.x = 1600;
    resolution.y = 900;

    _window.create(sf::VideoMode(resolution.x, resolution.y), "Wholesale warehouse management system", sf::Style::Default);
    _font.loadFromFile("Anonymous_Pro.ttf");
    _font_size = 40;

    _event = "start";



    setObject(sf::Vector2f(400, 75), sf::Vector2f(1100, 0), "");
    _current_date = 0;
    _text_current_date = _texts[_texts.size() - 1];

    // заголовки на стартовой странице 
    {
        startSetObject(sf::Vector2f(800, 50), sf::Vector2f(0, 0), "Add the products you need to sell");
        /*startSetObject(sf::Vector2f(250, 50), sf::Vector2f(50, 50), "Name");
        startSetObject(sf::Vector2f(300, 50), sf::Vector2f(280, 55), "Storage date");
        startSetObject(sf::Vector2f(200, 50), sf::Vector2f(550, 60), "Cost");
        startSetObject(sf::Vector2f(200, 50), sf::Vector2f(850, 60), "Quantity\nin whpackaging");*/
        //startSetObject(sf::Vector2f(800, 50), sf::Vector2f(800, 0), "Enter store names");
    }
    // товары на стартовой странице
    _start_input_fields.push_back(new InputField(
        sf::Vector2f(800, 50),
        sf::Vector2f(0, 80),
        "Name", "storage date", "cost RUB", "cnt", _font, _font_size));

    _buttons.push_back(new IButton(_window, "start sim",
        sf::Vector2f(400, 50),
        sf::Vector2f(1000, 800),
        "Start simulation", _font, _font_size));

    _buttons.push_back(new IButton(_window, "add new input field",
        sf::Vector2f(50, 50),
        sf::Vector2f(50, 130),
        "+", _font, _font_size));

    _buttons.push_back(new IButton(_window, "load",
        sf::Vector2f(400, 50),
        sf::Vector2f(1000, 700),
        "products from file", _font, _font_size));

    _start_buttons.push_back(new InputButton(
        sf::Vector2f(130, 70),
        sf::Vector2f(1200, 100),
        "value", _font, _font_size, "Enter shelfs limit"));

    _start_buttons.push_back(new InputButton(
        sf::Vector2f(130, 70),
        sf::Vector2f(1200, 250),
        "value", _font, _font_size, "Enter count of shelfs"));

    _start_buttons.push_back(new InputButton(
        sf::Vector2f(130, 70),
        sf::Vector2f(1200, 400),
        "value", _font, _font_size, "Enter start capital"));

    _start_buttons.push_back(new InputButton(
        sf::Vector2f(130, 70),
        sf::Vector2f(1200, 550),
        "value", _font, _font_size, "Enter count of shops"));
    //nextdaySetObject(sf::Vector2f(1, 900), sf::Vector2f(800, 0));
    setObject({ 1, 900 }, { 990, 0 });

    rect_nd.setSize({ 1, 900 });
    rect_nd.setPosition({ 800, 0 });
    rect_nd.setFillColor(sf::Color::Black);
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
    for (auto i : _start_input_fields) {
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

void Interface::launch() {
    while (_window.isOpen())
    {
        input();
        update();
        draw();
    }
}

void Interface::input() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        _window.close();
    }

    sf::Event event;
    while (_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) _window.close();
        _cursor_position = sf::Mouse::getPosition(_window);
        if (event.type == sf::Event::MouseWheelScrolled)
        {
            _delta_y += event.mouseWheelScroll.delta * 10;
            if (_delta_y > 0) _delta_y = 0;
        }
        if (_event == "start") {
            if (_start_input_fields[_start_input_fields.size() - 1]->getPosition().y < 80) _delta_y = 80 - _start_input_fields[_start_input_fields.size() - 1]->getStartPosition().y;
            for (auto i : _start_input_fields) {
                i->setPosition({ i->getStartPosition().x, i->getStartPosition().y + _delta_y });
            }
            _buttons[1]->setPosition({ _buttons[1]->getStartPosition().x, _buttons[1]->getStartPosition().y + _delta_y });
            for (auto i : _start_input_fields)
            {
                if (i->isInPointArea(_cursor_position) == "none") continue;
                if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                {
                    if (i->isInPointArea(_cursor_position) == "name") {
                        _event = "enter name";
                        _current_pressed_input_field = i;
                        i->getStringNameRef() = "";
                        i->updateTextName();
                    }
                    else if (i->isInPointArea(_cursor_position) == "date") {
                        _event = "enter date";
                        _current_pressed_input_field = i;
                        i->getStringDateRef() = "";
                        i->updateTextDate();
                    }
                    else if (i->isInPointArea(_cursor_position) == "cost") {
                        _event = "enter cost";
                        _current_pressed_input_field = i;
                        i->getStringCostRef() = " rub";
                        i->updateTextCost();
                    }
                    else if (i->isInPointArea(_cursor_position) == "quantity") {
                        _event = "enter quantity";
                        _current_pressed_input_field = i;
                        i->getStringQuantityRef() = "";
                        i->updateTextQuantity();
                    }
                }
            }
            for (auto i : _start_buttons)
            {
                if (i->isInPointArea(_cursor_position) == "none") continue;
                if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                {
                    _event = "enter string";
                    _current_pressed_input_button = i;
                    _current_pressed_input_button->getRefString() = "";
                    i->updateText();
                }

            }
        }
        if (_event == "enter string")
        {
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == '\b') {
                    if (_current_pressed_input_button->getString().size()) _current_pressed_input_button->getRefString().pop_back();
                }
                else if (event.text.unicode == '\r' && _current_pressed_input_button->getString().size())
                {
                    _event = "start";
                    for (auto i : _current_pressed_input_button->getString()) {
                        if (i < '0' || i > '9') {
                            _event = "enter string";
                            incorrectTextInput();
                            break;
                        }
                    }
                }
                else if (event.text.unicode >= '0' && event.text.unicode <= '9') _current_pressed_input_button->getRefString() += event.text.unicode;
                else incorrectTextInput();
                _current_pressed_input_button->updateText();
            }
        }
        if (_event == "enter name")
        {
            if (event.type == sf::Event::TextEntered)
            {
                if (checkName(event.text.unicode, _current_pressed_input_field, 1)) {
                    if (event.text.unicode == '\r') _event = "start";
                }
                else incorrectTextInput();
            }
        }
        if (_event == "enter date")
        {
            if (event.type == sf::Event::TextEntered)
            {
                if (checkDate(event.text.unicode, _current_pressed_input_field, 1)) {
                    if (event.text.unicode == '\r') _event = "start";
                }
                else incorrectTextInput();
            }
        }
        if (_event == "enter cost")
        {
            if (event.type == sf::Event::TextEntered)
            {
                if (checkCost(event.text.unicode, _current_pressed_input_field, 1)) {
                    if (event.text.unicode == '\r') _event = "start";
                }
                else incorrectTextInput();
            }
        }
        if (_event == "enter quantity") {
            if (event.type == sf::Event::TextEntered)
            {
                if (checkCnt(event.text.unicode, _current_pressed_input_field, 1)) {
                    if (event.text.unicode == '\r') _event = "start";
                }
                else incorrectTextInput();
            }
        }
        if (_event == "warehouse") {
            _warehouse_texts.resize(0);
            std::vector<Shelf*> shelfs = _whouse->getShelfs();
            warehouseSetObject(sf::Vector2f(150, 50), sf::Vector2f(30, 10), "Name");
            warehouseSetObject(sf::Vector2f(200, 50), sf::Vector2f(180, 10), "Quantity\nin pack");
            warehouseSetObject(sf::Vector2f(150, 50), sf::Vector2f(200 + 150, 10), "Days\nleft");
            warehouseSetObject(sf::Vector2f(150, 50), sf::Vector2f(200 + 300, 10), "Cost");
            int m = 0, m1 = 100;
            for (int i = 0; i < shelfs.size(); ++i) {
                auto j = shelfs[i];
                if (50 + m + _delta_y >= 0) warehouseSetObject(sf::Vector2f(150, 50), sf::Vector2f(10, m1 + m + _delta_y), "Shell " + std::to_string(i + 1));
                std::vector<std::pair<Item*, int>> items = j->getItem();
                for (auto k : items) {
                    std::wstring a = k.first->getName();
                    if (100 + m + _delta_y < 0) { m += 50; continue; }
                    warehouseSetObject(sf::Vector2f(220, 50), sf::Vector2f(0, 50 + m1 + m + _delta_y), std::string(a.begin(), a.end()));
                    warehouseSetObject(sf::Vector2f(150, 50), sf::Vector2f(200, 50 + m1 + m + _delta_y), std::to_string(k.second));
                    warehouseSetObject(sf::Vector2f(150, 50), sf::Vector2f(350, 50 + m1 + m + _delta_y), std::to_string(k.first->getShelfLife()));
                    warehouseSetObject(sf::Vector2f(150, 50), sf::Vector2f(500, 50 + m1 + m + _delta_y), std::to_string(k.first->getCost()));
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
                i->setPosition(sf::Vector2f(i->getPosition().x, m + _delta_y));
                if (j % 3 == 2) m += 50;
                j += 1;
            }
            j = 0;
            m = 100;
            /*for (auto i : _buttons) {
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

            }*/
            m = 100;
            /*for (auto i : _2buttons) {
                if (j == 0) {
                    j += 1;
                    continue;
                }
                if (j % 2 == 0) {
                    i->setPosition(sf::Vector2f(1030, m + _delta_y));
                    m += 50;
                }
                else
                {
                    i->setPosition(sf::Vector2f(830, m + _delta_y));

                }
                j += 1;

            }*/


        }
        if (_event.substr(0, 6) == "button") {
            _orders_text.resize(0);
            std::vector<StoreOrder*> store_orders = _manager.getStoreOrders();
            std::vector<int> pos(10, 100);
            for (auto i : store_orders) {
                std::vector<std::pair<Item*, int>> order_list = i->getOrderList();
                orderSetObject(sf::Vector2f(0 + 10, 10), "Desired products:");
                if (std::to_string(i->getId()) != _event.substr(6, 7)) continue;
                for (auto j : order_list) {
                    auto item = j.first;
                    int value = j.second;
                    std::wstring a = item->getName();
                    orderSetObject(sf::Vector2f(0 + 10, pos[i->getId()] + 10), std::string(a.begin(), a.end()) +
                        "    Requested quantity:" +
                        std::to_string(value));
                    pos[i->getId()] += 100;
                }
            }
        }
        if (_event == "manu") {

            for (auto i : _input_buttons)
            {
                if (i->isInPointArea(_cursor_position) == "1")
                {
                    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                        _event = "manu enter";
                        i->getRefString() = "";
                        i->updateText();
                        _current_pressed_input_button = i;
                    }
                }

            }
        }
        if (_event == "manu enter") {
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == '\b') {
                    if (_current_pressed_input_button->getRefString().size()) _current_pressed_input_button->getRefString().pop_back();
                }
                else if (event.text.unicode == '\r') {
                    bool b = true;
                    for (auto i : _current_pressed_input_button->getString()) {
                        if (i < '0' || i > '9') {
                            b = false;
                            break;
                        }
                    }
                    if (b && _current_pressed_input_button->getRefString().size())
                        _event = "manu";
                    else incorrectTextInput();
                }
                else {
                    if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                        _current_pressed_input_button->getRefString() += event.text.unicode;
                    }
                }
                _current_pressed_input_button->updateText();
            }
        }

        for (auto i : _buttons)
        {
            if (i->isInPointArea(_cursor_position))
            {
                i->setRectColor("highlight");
                if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                {
                    _event = i->getId();
                    _current_pressed_button = i;

                    bool check = 1;
                    if (i->getId() == "add new input field") {
                        _event = "start";
                        _current_pressed_button = 0;

                        _start_input_fields.push_back(new InputField(
                            sf::Vector2f(800, 50),
                            sf::Vector2f(0, _start_input_fields[_start_input_fields.size() - 1]->getStartPosition().y + 50),
                            "Name", "storage date", "cost RUB", "cnt", _font, _font_size));

                        _start_input_fields[_start_input_fields.size() - 1]->setPosition({ 0, _start_input_fields[_start_input_fields.size() - 2]->getPosition().y + 50 });
                        _buttons[1]->setStartPosition(sf::Vector2f(_buttons[1]->getStartPosition().x, _start_input_fields[_start_input_fields.size() - 1]->getStartPosition().y + 50));
                        _buttons[1]->setPosition(sf::Vector2f(_buttons[1]->getPosition().x, _start_input_fields[_start_input_fields.size() - 1]->getPosition().y + 50));
                        i->setRectColor("none");
                    }
                    else if (i->getId() == "load")
                    {
                        _event = "start";
                        _current_pressed_button = 0;
                        i->setRectColor("none");
                        std::ifstream input;
                        input.open("list_of_products.txt");
                        std::string name;
                        int data, cost, count;
                        if (_start_input_fields.size() == 1) _start_input_fields.pop_back();
                        while (input >> name >> data >> cost >> count) {
                            _start_input_fields.push_back(new InputField(
                                sf::Vector2f(800, 50),
                                sf::Vector2f(0, (_start_input_fields.size() == 0) ? 80 : _start_input_fields[_start_input_fields.size() - 1]->getStartPosition().y + 50),
                                name, std::to_string(data) + " d", std::to_string(cost) + " rub", std::to_string(count), _font, _font_size));

                            _start_input_fields[_start_input_fields.size() - 1]->setPosition({ 0, (_start_input_fields.size() == 1) ? 80 : _start_input_fields[_start_input_fields.size() - 2]->getPosition().y + 50 });
                            _buttons[1]->setStartPosition(sf::Vector2f(_buttons[1]->getStartPosition().x, _start_input_fields[_start_input_fields.size() - 1]->getStartPosition().y + 50));
                            _buttons[1]->setPosition(sf::Vector2f(_buttons[1]->getPosition().x, _start_input_fields[_start_input_fields.size() - 1]->getPosition().y + 50));
                        }


                        input.close();
                    }
                    else if (i->getId() == "start sim") {
                        for (auto i : _start_input_fields)
                        {
                            if (!checkInputField(i)) {
                                _event = "start";
                                _current_pressed_button = 0;
                                incorrectTextInput();
                                check = 0;
                                break;
                            }
                        }
                        for (auto i : _start_buttons)
                        {
                            if (i->getString() == "value") {
                                _event = "start";
                                _current_pressed_button = 0;
                                incorrectTextInput();
                                check = 0;
                                break;
                            }
                        }
                        if (!check) break;
                        _lines.pop_back();
                        std::ofstream out;
                        out.open("list_of_products.txt");
                        for (auto i : _start_input_fields)
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
                            out << i->getStringName() << ' ' << days << ' ' << i->getStringCost() << ' ' << i->getStringQuantity() << '\n';
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




                        _event = "main";
                        _shelfs_limit = 0;
                        _cnt_Shelfs = 0;
                        for (auto i : _start_buttons[1]->getString())
                        {
                            _cnt_Shelfs *= 10;
                            _cnt_Shelfs += i - '0';
                        }

                        for (auto i : _start_buttons[0]->getString())
                        {
                            _shelfs_limit *= 10;
                            _shelfs_limit += i - '0';
                        }
                        _start_capital = 0;
                        for (auto i : _start_buttons[2]->getString())
                        {
                            _start_capital *= 10;
                            _start_capital += i - '0';
                        }
                        _cnt_of_shops = 0;
                        for (auto i : _start_buttons[3]->getString())
                        {
                            _cnt_of_shops *= 10;
                            _cnt_of_shops += i - '0';
                        }
                        {
                            setObject(sf::Vector2f(1, 900), sf::Vector2f(800, 0));
                            setObject(sf::Vector2f(800, 1), sf::Vector2f(800, 600));
                            setObject(sf::Vector2f(1, 600), sf::Vector2f(1200, 0));
                            setObject(sf::Vector2f(400, 1), sf::Vector2f(1200, 150));

                            setObject(sf::Vector2f(400, 100), sf::Vector2f(800, 0), "SHOPS");
                            setObject(sf::Vector2f(400, 100), sf::Vector2f(730, 100), "Money: " + std::to_string(_start_capital));
                            _money = _texts[_texts.size() - 1];
                            /*setObject(sf::Vector2f(400, 75), sf::Vector2f(1200, 75), "00:00:00");
                            text_current_time = _texts[_texts.size() - 1];*/

                            setObject(sf::Vector2f(250, 250), sf::Vector2f(1275, 200));

                            setObject(sf::Vector2f(400, 75), sf::Vector2f(1200, 450), "Manager");
                            setObject(sf::Vector2f(400, 75), sf::Vector2f(1200, 500), "Natalia Petrovna");

                        }
                        createMainButtons();
                        _manager = Manager();
                        _whouse = new Warehouse(_cnt_Shelfs);
                        _whouse->setSize(_shelfs_limit);
                        _manager.setMoney(_start_capital);
                        _manager.addProducts(_whouse, items);
                        break;
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
                            std::vector<std::pair<Item*, int>> items = j->getItem();
                            for (auto k : items) {
                                std::wstring a = k.first->getName();
                                if (100 + m + _delta_y < 0) { m += 50; continue; }
                                warehouseSetObject(sf::Vector2f(220, 50), sf::Vector2f(0, 50 + m1 + m + _delta_y), std::string(a.begin(), a.end()));
                                warehouseSetObject(sf::Vector2f(150, 50), sf::Vector2f(200, 50 + m1 + m + _delta_y), std::to_string(k.second));
                                warehouseSetObject(sf::Vector2f(150, 50), sf::Vector2f(350, 50 + m1 + m + _delta_y), std::to_string(k.first->getShelfLife()));
                                warehouseSetObject(sf::Vector2f(150, 50), sf::Vector2f(500, 50 + m1 + m + _delta_y), std::to_string(k.first->getCost()));
                                m += 50;
                            }
                            m += 50;
                        }
                        _event = "warehouse";
                    }
                    else if (i->getId() == "next day") {
                        _manager.updateData();
                        createNextdayButtons();
                        _event = "next day";
                        _current_date++;
                        _delta_y = 0;
                        map_lack_products = _manager.funcShortage(_whouse);
                        _manager.formOrder(_whouse);
                        it = map_lack_products.begin();
                        //std::cout << map.size() << '\n';
                        int m = 0;
                        _nextday_texts.resize(0);
                        nextdaySetObject(sf::Vector2f(150, 50), sf::Vector2f(0, 0), "Name");
                        nextdaySetObject(sf::Vector2f(150, 50), sf::Vector2f(150, 0), "avail");
                        nextdaySetObject(sf::Vector2f(200, 50), sf::Vector2f(250, 0), "req");
                        m += 100;
                        _buttons.resize(4);
                        _need_prod.resize(0);
                        for (int i = 1; it != map_lack_products.end(); it++, i++) {
                            //std::cout << _delta_y << '\n';
                            if (m + _delta_y < 0) continue;
                            nextdaySetObject(sf::Vector2f(200, 50), sf::Vector2f(0, m + _delta_y), std::string(it->first.begin(), it->first.end()));
                            nextdaySetObject(sf::Vector2f(150, 50), sf::Vector2f(150, m + _delta_y), std::to_string(it->second.first));
                            nextdaySetObject(sf::Vector2f(200, 50), sf::Vector2f(250, m + _delta_y), std::to_string(it->second.second));

                            _need_prod.push_back({ std::string(it->first.begin(), it->first.end()), 0 });
                            /*_buttons.push_back(new IButton(_window, "auto " + std::string(it->first.begin(), it->first.end()),
                                sf::Vector2f(150, 40),
                                sf::Vector2f(430, m + _delta_y),
                                "auto", _font, _font_size));
                            _buttons.push_back(new IButton(_window, "manu " + std::string(it->first.begin(), it->first.end()),
                                sf::Vector2f(150, 40),
                                sf::Vector2f(630, m + _delta_y),
                                "manual", _font, _font_size));*/
                            m += 50;
                        }
                        _money->setString("Money: " + std::to_string(_manager.getMoney()));
                        _money->setPosition({ _money->getPosition().x, _money->getPosition().y });

                    }
                    else if (i->getId() == "done") {
                        for (int i = 0; i < _need_prod.size() && _need_prod.size() == _input_buttons.size(); i++)
                        {
                            std::string str = _input_buttons[i]->getString();
                            int num = 0; int q = 1;
                            for (int i = str.size() - 1; i >= 0; i--) {
                                num += (str[i] - '0') * q;
                                q *= 10;
                            }
                            _need_prod[i].second = num;
                        }
                        for (auto i : _need_prod) {
                            _manager.buyProducts(_whouse, i.first, i.second);
                        }
                        
                        _event = "main";
                        _manager.processOrder(_whouse);
                        _manager.getProductsFromWhOrder(_whouse);
                        _whouse->updateItems();
                        _whouse->getDeleteItem();
                        _whouse->updateShelfs();
                        int n = 4;
                        std::vector<StoreOrder*> ord;
                        for (int i = 0; i < n; ++i) {
                            StoreOrder* newOrder = new StoreOrder(i);
                            newOrder->setOrderList(formNewOrder());
                            ord.push_back(newOrder);
                        }
                        _manager.addNewOrder(ord);
                        createMainButtons();
                        _input_buttons.resize(0);

                    }
                    else if (i->getId().substr(0, 4) == "auto") {
                        _manager.formOrder(_whouse); //
                        _event = "next day";
                        _current_pressed_button = nullptr;

                        _event = "main"; //DON`t TOUCH
                        _manager.processOrder(_whouse);
                        _manager.getProductsFromWhOrder(_whouse);
                        _whouse->updateItems();
                        _whouse->updateShelfs();
                        _whouse->getDeleteItem();
                        int n = 4;
                        std::vector<StoreOrder*> ord;
                        for (int i = 0; i < n; ++i) {
                            StoreOrder* newOrder = new StoreOrder(i);
                            newOrder->setOrderList(formNewOrder());
                            ord.push_back(newOrder);
                        }
                        _manager.addNewOrder(ord);
                        createMainButtons();
                        _input_buttons.resize(0);
                    }
                    else if (i->getId().substr(0, 4) == "manu") {
                        _input_buttons.resize(0);
                        _whouse->updateItems();
                        _whouse->updateShelfs();
                        for (int i = 0; i < _need_prod.size(); ++i)
                        {
                            _input_buttons.push_back(new InputButton(sf::Vector2f(200, 50), sf::Vector2f(500, i * 50 + 100 + _delta_y), "0", _font, _font_size, ""));
                        }

                        _current_pressed_button = nullptr;
                    }
                    else if (i->getId() == "finish") {
                        
                        _start_texts.resize(0);
                        StoreOrder* order = _manager.getStat().first;
                        int money = _manager.getStat().second.first;
                        int start_money = _manager.getStat().second.second;

                        startSetObject({ 200, 200 }, { 800, 200 }, "Start-up capital");
                        startSetObject({ 200, 200 }, { 800, 400 }, "Final capital");
                        startSetObject({ 200, 200 }, { 800, 600 }, "Profit");
                        startSetObject({ 200, 200 }, { 1200, 200 }, std::to_string(start_money));
                        startSetObject({ 200, 200 }, { 1200, 400 }, std::to_string(money));
                        startSetObject({ 200, 200 }, { 1200, 600 }, std::to_string(money - start_money));


                        std::vector<std::pair<Item*, int> > vect = order->getOrderList();
                        int m = 200;
                        for (auto i : vect)
                        {
                            std::wstring a = i.first->getName();
                            std::string str = std::string(a.begin(), a.end());
                            int num = i.second;
                            
                            startSetObject({ 200, 200 }, sf::Vector2f( 200, m ), str);
                            startSetObject({ 200, 200 }, sf::Vector2f (400, m ), std::to_string(num));
                            m += 200;
                        }
                    }
                }
            }
            else
            {
                i->setRectColor("none");
            }
        }
        if (_current_pressed_button) _current_pressed_button->setRectColor("pressed");
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

void Interface::draw() {
    _window.clear(sf::Color(255, 235, 228));
    for (auto i : _buttons)
    {
        i->draw();
    }
    if (_event == "start" || _event == "enter string" || _event == "enter name" || _event == "enter date" || _event == "enter cost" || _event == "enter quantity")
    {
        for (auto i : _start_input_fields)
        {
            if (i->getPosition().y >= 50) i->draw(_window);
        }
        for (auto i : _start_texts)
        {
            _window.draw(*i);
        }
        for (auto i : _start_buttons)
        {
            i->draw(_window);
        }
        _window.draw(*_lines[0]);
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
    if (_event == "next day" || _event == "manu" || _event == "manu enter")
    {
        for (auto i : _nextday_texts)
        {
            _window.draw(*i);
        }
        for (auto i : _nextday_lines)
        {
            _window.draw(*i);
        }
        _window.draw(rect_nd);
        for (auto i : _input_buttons)
        {
            i->draw(_window);
        }
    }
    if (_event.substr(0, 6) == "button") {
        for (auto i : _orders_text) {
            _window.draw(*i);
        }
    }
    if (_event == "final") {
        for (auto i : _start_texts)
        {
            _window.draw(*i);
        }
    }
    _window.display();
}

void Interface::setObject(sf::Vector2f size, sf::Vector2f position) {
    _lines.push_back(new sf::RectangleShape(size));
    _lines[_lines.size() - 1]->setPosition(position);
    _lines[_lines.size() - 1]->setOutlineColor(sf::Color::Black);
    _lines[_lines.size() - 1]->setOutlineThickness(1);
}

void Interface::setObject(sf::Vector2f size, sf::Vector2f position, std::string string) {
    _texts.push_back(new sf::Text(string, _font, _font_size));
    _texts[_texts.size() - 1]->setPosition({ position.x + size.x / 2 - _texts[_texts.size() - 1]->getGlobalBounds().width / 2,
        position.y + size.y / 2 - _texts[_texts.size() - 1]->getGlobalBounds().height / 2 });
    _texts[_texts.size() - 1]->setFillColor(sf::Color::Black);
}

void Interface::startSetObject(sf::Vector2f size, sf::Vector2f position, std::string string) {
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

void Interface::incorrectTextInput() {
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
            if (err_event.type == sf::Event::TextEntered || sf::Mouse::isButtonPressed(sf::Mouse::Left)) err_window.close();
        }
    }
}

void Interface::warehouseSetObject(sf::Vector2f size, sf::Vector2f position, std::string string) {
    _warehouse_texts.push_back(new sf::Text(string, _font, _font_size));
    _warehouse_texts[_warehouse_texts.size() - 1]->setPosition({ position.x + size.x / 2 - _warehouse_texts[_warehouse_texts.size() - 1]->getGlobalBounds().width / 2,
        position.y + size.y / 2 - _warehouse_texts[_warehouse_texts.size() - 1]->getGlobalBounds().height / 2 });
    _warehouse_texts[_warehouse_texts.size() - 1]->setFillColor(sf::Color::Black);
}

void Interface::nextdaySetObject(sf::Vector2f size, sf::Vector2f position) {
    _nextday_lines.push_back(new sf::RectangleShape(size));
    _nextday_lines[_nextday_lines.size() - 1]->setPosition(position);
    _nextday_lines[_nextday_lines.size() - 1]->setOutlineColor(sf::Color::Black);
    _nextday_lines[_nextday_lines.size() - 1]->setOutlineThickness(1);
}

void Interface::nextdaySetObject(sf::Vector2f size, sf::Vector2f position, std::string string) {
    _nextday_texts.push_back(new sf::Text(string, _font, _font_size));
    _nextday_texts[_nextday_texts.size() - 1]->setPosition({ position.x + size.x / 2 - _nextday_texts[_nextday_texts.size() - 1]->getGlobalBounds().width / 2,
        position.y });
    _nextday_texts[_nextday_texts.size() - 1]->setFillColor(sf::Color::Black);
}

void Interface::createMainButtons() {
    _buttons.resize(0);
    for (int i = 0; i < _cnt_of_shops; i++)
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

void Interface::createNextdayButtons() {
    _buttons.resize(0);

    _buttons.push_back(new IButton(_window, "done",
        sf::Vector2f(200, 150),
        sf::Vector2f(1000, 675),
        "Done", _font, _font_size));

    _buttons.push_back(new IButton(_window, "finish",
        sf::Vector2f(200, 150),
        sf::Vector2f(1300, 675),
        "Finish", _font, _font_size));

    _buttons.push_back(new IButton(_window, "auto",
        sf::Vector2f(150, 40),
        sf::Vector2f(1000, 200),
        "auto", _font, _font_size));
    _buttons.push_back(new IButton(_window, "manu",
        sf::Vector2f(150, 40),
        sf::Vector2f(1200, 200),
        "manu", _font, _font_size));
}

void Interface::orderSetObject(sf::Vector2f position, std::string string) {
    _orders_text.push_back(new sf::Text(string, _font, _font_size));
    _orders_text[_orders_text.size() - 1]->setPosition({ position.x, position.y });
    _orders_text[_orders_text.size() - 1]->setFillColor(sf::Color::Black);
}

bool Interface::checkName(char c, InputField* value, bool b) {
    if (c == '\b') {
        if (value->getStringNameRef().size()) value->getStringNameRef().pop_back();
    }
    else if (c == '\r') {
        if (value->getStringNameRef().size())
            return true;
        else return false;
    }
    else if (value->getStringNameRef().size() < 10)
        if (b) value->getStringNameRef() += c;
    value->updateTextName();
    return true;
}

bool Interface::checkDate(char c, InputField* value, bool b) {
    if (c == '\b') { if (value->getStringDateRef().size()) value->getStringDateRef().pop_back(); }
    else if (c == '\r')
    {
        int st = 0; bool ok = true;
        std::string string = value->getStringDateRef();
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
            && st && ok && value->getStringDateRef().size()) return true;
        else return false;
    }
    else {
        if (!((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == ' ')) return false;
        else if (b && value->getStringDateRef().size() < 10) value->getStringDateRef() += c;
    }
    value->updateTextDate();
    return true;
}

bool Interface::checkCost(char c, InputField* value, bool b) {
    if (c == '\b') { if (value->getStringCostRef().size() > 4) value->getStringCostRef().erase(value->getStringCostRef().end() - 5); }
    else if (c == '\r') {
        if (value->getStringCostRef().size() > 4) {
            bool b = true;
            for (auto i : value->getStringCost().substr(0, value->getStringCost().size() - 4)) {
                if (i < '0' || i > '9') {
                    b = false;
                    break;
                }
            }
            if (b) return true;
            else return false;
        }
        else return false;
    }
    else {
        if (!(c >= '0' && c <= '9')) return false;
        else if (b && value->getStringCostRef().size() < 10) value->getStringCostRef().insert(value->getStringCostRef().end() - 4, c);
    }
    value->updateTextCost();
    return true;
}

bool Interface::checkCnt(char c, InputField* value, bool b) {
    if (c == '\b') {
        if (value->getStringQuantityRef().size()) value->getStringQuantityRef().pop_back();
    }
    else if (c == '\r') {
        bool b = true;
        for (auto i : value->getStringQuantity()) {
            if (i < '0' || i > '9') {
                b = false;
                break;
            }
        }
        if (b && value->getStringQuantityRef().size())
            return true;
        else return false;
    }
    else {
        if (!(c >= '0' && c <= '9')) return false;
        else if (value->getStringQuantityRef().size() < 3)
            if (b) value->getStringQuantityRef() += c;
    }
    value->updateTextQuantity();
    return true;
}

bool Interface::checkInputField(InputField* value) {
    for (auto i : value->getStringName()) {
        if (!checkName(i, value)) {
            return false;
        }
    }
    if (!checkDate('\r', value)) {
        return false;
    }
    for (auto i : value->getStringCost().substr(0, value->getStringCost().size() - 4)) {
        if (!checkCost(i, value)) {
            return false;
        }
    }
    for (auto i : value->getStringQuantity()) {
        if (!checkCnt(i, value)) {
            return false;
        }
    }
    return true;
}