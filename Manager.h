#pragma once
#include <vector>
#include <random>
#include <chrono>
#include "Warehouse.h"
#include "Order.h"
#include "StoreOrder.h"
#include "WarehouseOrder.h"
#include "Trucks.h"


class Manager {
public:
    Manager();
    int getMood();

    std::vector<StoreOrder*> getStoreOrders();
    std::map<std::wstring, std::pair<int, int>> funcShortage(Warehouse* _whouse);

    int getMoney();

    void setMoney(int _money) {
        start_money = _money;
        money = _money;
    }
    void processOrder(Warehouse* _whouse);
    
    void getProductsFromWhOrder(Warehouse* _whouse);

    void buyProducts(Warehouse* _whouse, std::string str, int col);

    void updateData() {
        for (auto j : order) {
            if (j != nullptr) {
                for (auto k : j->getOrderList()) {
                    bool f = true;
                    for (auto& i : all_orders->getOrderList()) {
                        if (i.first != nullptr && k.first->getName() == i.first->getName()) {
                            i.second += k.second;
                            f = false;
                        }
                    }
                    if (f) {
                        all_orders->addItem(new Item(0, 0, k.first->getName()), k.second);
                    }
                }
            }
        }
    }

    std::pair<StoreOrder*, std::pair<int,int>> getStat() {
        if (all_orders->getOrderList().size() != 0)
            return { all_orders,{ money, start_money} };
        else
            return { 0, {money, start_money} };
    }
    void addProducts(Warehouse* _whouse, std::vector< std::pair<Item*, int>> products);

    void removeProducts(Warehouse* _whouse, std::vector< std::pair<Item*, int>> products);

    int statusOfItem(Warehouse* _whouse, Item* item);

    void formOrder(Warehouse* _whouse);

    Item* findItemfromFile(std::wstring a);

    std::map<std::wstring, int> listOfProducts(Warehouse* _whouse);

    void addNewOrder(std::vector<StoreOrder*> ord);
private:
    int _mood;
    int money;
    int _shift_time;
    int start_money;
    StoreOrder* all_orders;
    std::vector<int> _not_fav_id;
    std::vector<StoreOrder*> order;
    WarehouseOrder* _wh_order;
};

