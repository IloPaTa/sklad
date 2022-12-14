#include <iostream>
#include <vector>
#include "Item.h"
class Order {
public:
    std::vector<Item*> geOrderList() { return _order_list;  }
    int getTimeReceipt() { return time_receipt; }
    void addItem(Item* item) { _order_list.push_back(item); }

protected:
    std::vector<Item*> _order_list;
    int time_receipt;
};