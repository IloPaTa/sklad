#include <iostream>
#include "Order.h"

class StoreOrder: protected Order {
public:
    StoreOrder(std::vector<Item*> store_order, int store_id, int urgency = 1) {
        _order_list = store_order;
        _store_id = store_id;
        _urgency = urgency;
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