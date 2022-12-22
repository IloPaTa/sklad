#pragma once
#include <iostream>
#include <vector>
#include "Item.h"
class Order {
public:
    std::vector<std::pair<Item*, int> > getOrderList() { return _order_list;  }
    int getTimeReceipt() { return time_receipt; }
    void addItem(Item* item, int val) { _order_list.push_back({ item,val }); }

protected:
    std::vector< std::pair<Item*, int> > _order_list;
    int time_receipt;
};