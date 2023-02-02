#pragma once
#include <iostream>
#include "Order.h"

class StoreOrder: public Order {
public:
    StoreOrder(std::vector<std::pair<Item*, int> > store_order, int store_id, int urgency = 1) {
        _order_list = store_order;
        _store_id = store_id;
        _urgency = urgency;
    }
    StoreOrder(int id = 0) {
        _order_list.resize(1);
        _urgency = 1;
        _store_id = id;
    }
    int getId() {
        return _store_id;
    }
    int getUrgency() {
        return _urgency;
    }

protected:
    int _store_id;
    int _urgency;
};