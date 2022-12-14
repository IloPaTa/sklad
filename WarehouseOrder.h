#include <iostream>
#include "Order.h"

class WarehouseOrder : protected Order {
public:
    WarehouseOrder(std::vector<Item*> store_order) {
        _order_list = store_order;
    }
};