#pragma once
#include <iostream>
#include <vector>
#include "Item.h"
class Order {
public:
    std::vector<std::pair<Item*, int> > getOrderList() { return _order_list;  }
    void setOrderList(std::vector<std::pair<Item*, int> > order_list) { _order_list = order_list; }
    int getTimeReceipt() { return time_receipt; }
    void addItem(Item* item, int val) { _order_list.push_back({ item,val }); }
    void clearOrder() { _order_list.clear(); }
protected:
    std::vector< std::pair<Item*, int> > _order_list;
    int time_receipt;
};