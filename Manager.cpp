#include "Manager.h"

std::mt19937 gen(23);
std::uniform_int_distribution<> dis;

Manager::Manager() {
    _mood = 2;
    _wh_order = new WarehouseOrder();
}
int Manager::getMood() {
    return _mood;
}

std::vector<StoreOrder*> Manager::getStoreOrders() {
    return order;
}

std::map<std::wstring, std::pair<int, int>> Manager::funcShortage(Warehouse* _whouse) {
    std::map<std::wstring, std::pair<int, int>> result;
    for (auto i : order) {
        for (auto j : i->getOrderList()) {
            result[j.first->getName()].first += statusOfItem(_whouse, j.first);
            result[j.first->getName()].second += j.second;
        }
    }
    std::vector<std::wstring> vs;
    for (auto it = result.begin(); it != result.end(); ++it)
    {
        if ((*it).second.first >= (*it).second.second)
            vs.push_back((*it).first);
    }
    for (auto i = vs.begin(); i != vs.end(); ++i)
        result.erase(*i);
    return result;
}
int Manager::getMoney() {
    return money;
}
void Manager::processOrder(Warehouse* _whouse) {
    std::map<std::wstring, std::pair<int, int>> mp = funcShortage(_whouse);

    for (auto& i : order) {

        bool flag = true;
        std::vector< std::pair<Item*, int> > realOrder;
        for (auto j : i->getOrderList()) {
            if (mp[j.first->getName()].first >= mp[j.first->getName()].second) {
                realOrder.push_back(j);
                money += j.first->getCost();
            }
            else {
                int k = dis(gen);
                realOrder.push_back({ j.first, k });
                money += j.first->getCost() * k;
            }

        }
        removeProducts(_whouse, i->getOrderList());
        i->clearOrder();
    }
}

void Manager::getProductsFromWhOrder(Warehouse* _whouse) {
    for (auto i : _wh_order->getOrderList()) {
        _whouse->addItem(i.first, i.second);
    }
    _wh_order->clearOrder();
}
void Manager::addProducts(Warehouse* _whouse, std::vector< std::pair<Item*, int>> products) {
    for (auto i : products) {
        _whouse->addItem(i.first, i.second);
    }
}

void Manager::removeProducts(Warehouse* _whouse, std::vector< std::pair<Item*, int>> products) {
    for (auto i : products) {
        return;
    }

    for (auto i : products) {
        _whouse->removeItem(i.first, i.second);
    }
}

int Manager::statusOfItem(Warehouse* _whouse, Item* item) {
    return _whouse->getColItem(item->getName());
};

void Manager::formOrder(Warehouse* _whouse) {
    for (auto i : order) {
        for (auto j : i->getOrderList()) {
            if (statusOfItem(_whouse, j.first) < _mood * 5)
            {
                _wh_order->addItem(j.first, _mood * 5 * 1.5 - statusOfItem(_whouse, j.first));
                money -= abs(_mood * 5  - statusOfItem(_whouse, j.first)) * j.first->getCost();
            }
        }
    }
}

Item* Manager::findItemfromFile(std::wstring a) {
    std::string b = std::string(a.begin(), a.end());
    std::ifstream fin;
    fin.open("list_of_products.txt");
    std::string name;
    int date, cost, col;
    while (fin >> name >> date >> cost >> col) {
        if (name == b) {
            break;
        }
    }
    return new Item(col, cost, std::wstring(name.begin(), name.end()));
}
void Manager::addNewOrder(std::vector<StoreOrder*> ord) {
    for (auto i : ord) {
        order.push_back(i);
    }
}