#pragma once
#include<iostream>
#include<vector>
#include"SFML/Graphics.hpp"
#include "Shelf.h"
class Warehouse {
public:
    void addItem(Item* item, int val) {
        bool cover = false;
        for (auto i : _list_of_items) {
            if (item->getName() == i) {
                cover = true;
            }
        }
        if (!cover) {
            for (auto i : _shelfs) {
                if (val > 0) {
                    val -= i->addNewItem(item, val);
                }
            }           
        }
        for(auto i: _shelfs){
            if (val > 0) {
                val -= i->addItem(item, val);
            }
        }
    }

    void removeItem(Item* item, int val) {
        bool cover = false;
        for (auto i : _shelfs) {
            if (i->getItem(item) > 0) {
                cover = true;
            }
        }
        if (!cover)
            return;
        for (auto i : _shelfs) {
            if (val > 0) {
                val -= i->removeItem(item, val);
            }
        }
    }
    Item* getItem(Item* item) {
        int cnt = 0;
        for (auto i : _shelfs) {
            cnt += i->getItem(item);
        }
    }
    Shelf* getShelph(int val) {
        return _shelfs[val];
    }
    std::vector<Shelf*> getShelfs() {
        return _shelfs;
    }
    int getWareHouseSize() {
        return _shelfs.size();
    }

private:
    std::vector<std::wstring> _list_of_items;
    std::vector<Shelf*> _shelfs;
};

