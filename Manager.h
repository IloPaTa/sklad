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
        money = _money;
    }
    void processOrder(Warehouse* _whouse);
    
    void getProductsFromWhOrder(Warehouse* _whouse);

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
    std::vector<int> _not_fav_id;
    std::vector<StoreOrder*> order;
    WarehouseOrder* _wh_order;
};

