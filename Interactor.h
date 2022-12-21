#pragma once
#include "Manager.h"
#include "Interface.h"
#include "StoreOrder.h"
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

class Interactor {
public:
      Interactor(){}
      void Run() {
          _interface.launch();
          _manager.processOrder();
          _manager.formOrder();
          int cnt = rnd() % 5;
          std::vector<StoreOrder*> order;
          for (int i = 0; i < cnt; ++i) {
              order.push_back(makeStoreOrder());
          }
          _manager.setNewOrder(order);
      }
private:
    StoreOrder* makeStoreOrder() {
        StoreOrder* order = new StoreOrder({}, rnd()%10);
        std::ifstream fin("ListOfProducts.txt");
        std::string name;
        int date, cost, col;
        while (fin >> name >> date >> cost >> col) {
            Item* item = new Item(date, cost, std::wstring(name.begin(), name.end()));
            if (rnd() % 100 > 50) {
                order->addItem(item, rnd()%100);
            }
        }
    }
    Interface _interface;
    Manager _manager;
};

