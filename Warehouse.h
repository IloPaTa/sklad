#pragma once
#include<iostream>
#include<vector>
#include"SFML/Graphics.hpp"
#include "Shelf.h"
class Warehouse {
public:
    Warehouse(int shelf_size = 10) {
        _size = 0;
        for (int i = 0; i < shelf_size; ++i) {
            _shelfs.push_back(new Shelf(_size));
        }
    }

    void setShelfSize(int val) {
        _size = 0;
        _shelfs.clear();
        for (int i = 0; i < val; ++i) {
            _shelfs.push_back(new Shelf(_size));
        }
    }
    void setSize(int val) {
        _size = val;
        for (int i = 0; i < _shelfs.size(); ++i) {
            _shelfs[i]->setShelfSize(_size);
        }
    }
    void addItem(Item* item, int val) {
        for (auto i : _shelfs) {
            if (val > 0) {
                val -= i->addNewItem(item, val);
            }
        }
    }

    void updateItems() {
        for (auto &i : _shelfs) {
            std::vector<std::pair<Item*, int>> items = i->getItem();
            for (auto &j : items) {
                j.first->setShelfLife(j.first->getShelfLife() - 1);
            }
        }
    }

    void updateShelfs() {
        for (auto& i : _shelfs) {
            std::vector<std::pair<Item*, int>> items = i->getItem();
            for (auto& j : items) {
                if (j.first->getShelfLife() <= 0)
                {
                    j.second = 0;
                }
            }
        }
        std::vector<Shelf*> tmp;
        for (auto& i : _shelfs) {
            std::vector<std::pair<Item*, int>> items = i->getItem();
            bool flag = true;
            for (auto& j : items) {
                if (j.second > 0)
                {
                    flag = false;
                }
            }
            if (!flag) {
                tmp.push_back(new Shelf(_size));
                for (auto& j : items) {
                    if (j.second > 0)
                    {
                        tmp[tmp.size() - 1]->addNewItem(j.first, j.second);
                    }
                }
            }
        }
        while (tmp.size() != _shelfs.size()) {
            tmp.push_back(new Shelf(_size));
        }
        _shelfs = tmp;
    }

    void removeItem(Item* item, int& val) {
        bool cover = false;
        for (auto i : _shelfs) {
            if (val > 0) {
                val -= i->removeItem(item, val);
            }
        }
    }

    std::vector<std::pair<Item*, int>> getDelayItem(int val = 5) {
        std::vector<std::pair<Item*, int>> items;
        for (auto i : _shelfs) {
            for (auto j : i->getItem()) {
                if(j.first->getShelfLife() < val)
                   items.push_back(j);
            }
        }
        return items;
    }

    void getDeleteItem(int val = 5) {
        std::vector<std::pair<Item*, int>> items;
        for (auto i : _shelfs) {
            for (auto j : i->getItem()) {
                if (j.first->getShelfLife() <= 0)
                    removeItem(j.first, j.second);
            }
        }
    }


    int getColItem(std::wstring name){
       int cnt = 0;
       for (auto i : _shelfs) {
           for (auto j : i->getItem()) {
               if (j.first->getShelfLife() > 0 && name == j.first->getName())
                   cnt += j.second;
           }
       }
       return cnt;
    }
    Shelf* getShelf(int val) {
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
    size_t _size;
};

