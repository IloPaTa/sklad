#pragma once
#include<iostream>
#include<vector>
//пока что вместо структуры time используется инт, думаю как лучше сделать наследование пока что
class Trucks
{
public:
    int getCapacity() {
        return _capacity;
    }
    int getDeliveryTime() {
        return _delivery_time;
    }
    std::vector<int>* getTime() {
        return &_time;
    }
    void setCapacity(int capacity) {
        _capacity = capacity;
    }
    void setDeliveryTime(int delivery_time) {
        _delivery_time = delivery_time;
    }
    void addTime(int time) {
        _time.push_back(time);
    }
    bool isBusy(int time) {
        for (int i = 0; i < _time.size(); ++i) {
            if (_time[i] + 2 * _delivery_time > time && _time[i] <= time)
                return true;
        }
        return false;
    }
private:
    std::vector<int> _time;
    int _capacity, _delivery_time;
};

