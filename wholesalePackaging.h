#pragma once
#include "Item.h"
class wholesalePackaging {
public:
    wholesalePackaging(Item item, int capacity) {
        _item = item;
        _capacity = capacity;
    }
    Item* getItem() {
        return &_item;
    }
    int getCapacity() {
        return _capacity;
    }
    void setItem(Item item) {
        _item = item;
    }
    void setCapacity(int capacity) {
        _capacity = capacity;
    }
private:
    int _capacity;
    Item _item;

};

