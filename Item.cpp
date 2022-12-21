#include "Item.h"

int Item::getShelfLife() {
    return _shelf_life;
}
int Item::getCost() {
    return _cost;
}
std::wstring Item::getName() {
    return _name;
}
date Item::getDateOfCreating() {
    return _date_of_creating;
}
void Item::setShelfLife(int shelf_life) {
    _shelf_life = shelf_life;
}
void Item::setCost(int cost) {
    _cost = cost;
}
void Item::setName(std::wstring name) {
    _name = name;
}
void Item::setDateofCreating(date date_of_create) {
    _date_of_creating = date_of_create;
}