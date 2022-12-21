#pragma once
#include <iostream>
struct date {
    int d, m, y;
};
class Item {
public:
    Item() {}
    Item(int shelf_life, int cost, std::string name, date date_of_creating) :
        _shelf_life(shelf_life),
        _cost(cost),
        _name(name),
        _date_of_creating(date_of_creating){ }

    int getShelfLife();
    int getCost();
    std::wstring getName();
    date getDateOfCreating();
    void setShelfLife(int shelf_life);
    void setCost(int cost);
    void setName(std::string name);
    void setDateofCreating(date date_of_create);
private:
    int _shelf_life, _cost;
    std::wstring _name;
    date _date_of_creating;
};

