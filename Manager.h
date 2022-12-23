#pragma once
#include <vector>
#include <random>
#include "Warehouse.h"
#include "Order.h"
#include "StoreOrder.h"
#include "WarehouseOrder.h"
#include "Trucks.h"


//std::mt19937 gen(42);
//std::uniform_int_distribution<> dis;

class Manager {
public:
    Manager() {
        _mood = 2;
        _wh_order = new WarehouseOrder();
    }
    int getMood() {
        return _mood;
    }

    std::map<std::wstring, std::pair<int, int>> funcShortage(Warehouse* _whouse) {
        std::map<std::wstring, std::pair<int, int>> result;
        for (auto i : order) {
            for (auto j : i->getOrderList()) {
                result[j.first->getName()].first += statusOfItem(_whouse, j.first);
                result[j.first->getName()].second += j.second;
            }
        }
        std::vector<std::wstring> vs;
        for (auto it = result.begin(); it != result.end(); ++it)
        {
            if ((*it).second.first >= (*it).second.second)
                vs.push_back((*it).first);
        }
        for (auto i = vs.begin(); i != vs.end(); ++i)
            result.erase(*i);
        return result;
    }
    int getMoney() {
        return money;
    }
   void processOrder( Warehouse* _whouse) {
        std::map<std::wstring, std::pair<int, int>> mp = funcShortage(_whouse);

        for (auto &i : order) {
           
            bool flag = true;
            std::vector< std::pair<Item*, int> > realOrder;
            for (auto j : i->getOrderList()) {
                if (mp[j.first->getName()].first > mp[j.first->getName()].second) {
                    realOrder.push_back(j);
                    money += j.first->getCost();
                }
                else {
                    realOrder.push_back({ j.first, 3});
                    money += j.first->getCost() * 3;
                }
                    
            }
            removeProducts(_whouse, i->getOrderList());
            i->clearOrder();
        }
    }
    
    void getProductsFromWhOrder(Warehouse* _whouse) {
        for (auto i : _wh_order->getOrderList()) {
            _whouse->addItem(i.first, i.second);
         }
        _wh_order->clearOrder();
    }
    void addProducts(Warehouse* _whouse, std::vector< std::pair<Item*, int>> products) {
        for (auto i : products) {
            _whouse->addItem(i.first, i.second);
        }
    }

    void removeProducts(Warehouse* _whouse, std::vector< std::pair<Item*, int>> products) {
        for (auto i : products) {
            return;
        }

        for (auto i : products) {
            _whouse->removeItem(i.first, i.second);
        }
    }

    int statusOfItem(Warehouse* _whouse, Item* item) {
        return _whouse->getColItem(item->getName());
    };

    void formOrder(Warehouse* _whouse) {
        for (auto i : order) {
            for (auto j : i->getOrderList()) {
                if (statusOfItem(_whouse, j.first) < _mood * 5)
                {
                    _wh_order->addItem(j.first, _mood * 5 * 1.5 - statusOfItem(_whouse, j.first));
                    money -= (_mood * 5 * 1.5 - statusOfItem(_whouse, j.first))* j.first->getCost();
                }
            }
        }
    }

    Item* findItemfromFile(std::wstring a) {
        std::string b = std::string(a.begin(), a.end());
        std::ifstream fin;
        fin.open("list_of_products.txt");
        std::string name;
        int date, cost, col;
        while (fin >> name >> date >> cost >> col) {
            if (name == b) {
                break;
            }
        }
        return new Item(col, cost,std::wstring(name.begin(), name.end()));
    }
    void setNewOrder(std::vector<StoreOrder*> ord) {
        order = ord;
    }
private:
    int _mood;
    int money;
    int _shift_time;
    std::vector<int> _not_fav_id;
    std::vector<StoreOrder*> order;
    WarehouseOrder* _wh_order;
};

