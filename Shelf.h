#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <fstream>

#include "wholesalePackaging.h"

class Shelf {
public:
    Shelf(int shelfSize = 132) {
        _shelf_size = shelfSize;
        _ws_packagings.resize(shelfSize);
    }
    void setShelfSize(size_t shelf_size) {
        _shelf_size = shelf_size;
    }
    void setWsPacks(std::vector<std::pair<wholesalePackaging*, int>> ws_packagings) {
        _ws_packagings = ws_packagings;
    }

    size_t getShelfSize() {
        return _shelf_size;
    }
    std::vector<std::pair<wholesalePackaging*, int>> getWsPacks() {
        return _ws_packagings;
    }

    int removeItem(Item* item, int val) {
        for (auto& i : _ws_packagings) {
            if (i.first->getItem() == item) {
                i.second -= std::min(i.second, val);
                return std::min(i.second, val);
            }
        }
    }

    int addNewItem(Item* item, int val) {
        int cnt = 0;
        for (auto& i : _ws_packagings) {
            cnt += i.second;
        }
        std::ifstream fin("list_of_products.txt");
        std::string name;
        int date, cost, col;
        while (fin >> name >> date >> cost >> col) {
            if (std::wstring(name.begin(), name.end()) == item->getName())
                break;
        }
        fin.close();
        _ws_packagings.push_back({new wholesalePackaging(*item, col), std::min(val, int(_shelf_size - cnt)) });
        return std::min(val, int(_shelf_size - cnt));
    }

    int getColItem(Item* item) {
        for (auto& i : _ws_packagings) {
            if (i.first->getItem() == item) {
                return i.second;
            }
        }
        return 0;
    }

    std::vector<Item*> getItem() {
        std::vector<Item*> items;
        for (auto& i : _ws_packagings) {
            items.push_back(i.first->getItem());
        }
        return items;
    }
    std::vector<std::pair<wholesalePackaging*, int>> getWSPackaging() {
        return _ws_packagings;
    }
private:
    std::vector<std::pair<wholesalePackaging*, int>> _ws_packagings;
    size_t _shelf_size;

};

