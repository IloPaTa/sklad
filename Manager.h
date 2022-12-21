#pragma once
#include <vector>
#include "Control.h"
#include "Order.h"
#include "StoreOrder.h"
#include "WarehouseOrder.h"
#include "Trucks.h"
class Manager {
public:
    int getMood() {
        return _mood;
    }
    int processOrder() {
        for (auto i : order) {
           
            bool flag = true;
            for (auto j : i->getOrderList()) {
                if (control.statusOfItem(j.first) < j.second)
                    flag = false;
            }
            int time;
            Trucks* truck = control.getEmptyTruck(time);
            if (truck != nullptr && flag) {
                control.removeProducts(i->getOrderList());
            }
        }
    }

    void formOrder() {
        
        for (auto i : order) {
            for (auto j : i->getOrderList()) {
                if (control.statusOfItem(j.first) < j.second)
                {
                    _wh_order->addItem(j.first, j.second - control.statusOfItem(j.first));
                }
            }
            int time;
        }
    }
private:
    int _mood;
    int _shift_time;
    Control control;
    std::vector<int> _not_fav_id;
    std::vector<StoreOrder*> order;
    WarehouseOrder* _wh_order;
};

