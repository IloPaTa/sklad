#pragma once
#include <vector>
#include "Warehouse.h"
#include "Order.h"
#include "StoreOrder.h"
#include "WarehouseOrder.h"
#include "Trucks.h"
class Manager {
public:
    Manager() {}
    int getMood() {
        return _mood;
    }

    std::map<std::wstring, std::pair<int, int>> funcForSemen(Warehouse* _whouse) {
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

    int processOrder(std::vector<Trucks*> trucks, Warehouse* _whouse) {
        for (auto i : order) {
           
            bool flag = true;
            for (auto j : i->getOrderList()) {
                if (statusOfItem(_whouse, j.first) < j.second)
                    flag = false;
            }
            int time;
            Trucks* truck = getEmptyTruck(trucks, time);
            if (truck != nullptr && flag) {
                removeProducts(_whouse, i->getOrderList());
            }
        }
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

    Trucks* getEmptyTruck(std::vector<Trucks*> trucks, int  time) {
        for (auto i : trucks) {
            if (!i->isBusy(time)) {
                i->addTime(time);
                return i;
            }
        }
    }

    void formOrder(Warehouse* _whouse) {
        for (auto i : order) {
            for (auto j : i->getOrderList()) {
                if (statusOfItem(_whouse, j.first) < j.second)
                {
                    _wh_order->addItem(j.first, j.second - statusOfItem(_whouse, j.first));
                }
            }
            int time;
        }
    }

    void setNewOrder(std::vector<StoreOrder*> ord) {
        order = ord;
    }
private:
    int _mood;
    int _shift_time;
    std::vector<int> _not_fav_id;
    std::vector<StoreOrder*> order;
    WarehouseOrder* _wh_order;
};

