#pragma once
#include "Warehouse.h"
#include "Trucks.h"
class Control {
public:
    void addProducts(std::vector< std::pair<Item*, int>> products) {
        for (auto i : products) {
            _whouse->addItem(i.first, i.second);
        }
    }
    void removeProducts(std::vector< std::pair<Item*, int>> products) {
        for (auto i : products) {
            return;
        }

        for (auto i : products) {
            _whouse->removeItem(i.first, i.second);
        }
    }
    int statusOfItem(Item* item) {
        _whouse->getItem(item);
    };
    Trucks* getEmptyTruck(int  time) {
        for (auto i : trucks) {
            if (!i->isBusy(time)) {
                i->addTime(time);
                return i;
            }
        }
    }
    Warehouse* getWarehouse() {
        return _whouse;
    }
    std::vector<Shelf*> getShelf() {
        return _whouse.getShelf();
    }
private:
    Warehouse* _whouse;
    std::vector<Trucks*> trucks;
};

