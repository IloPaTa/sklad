#pragma once
#include <vector>
class Manager {
public:
    int getMood();
private:
    int _mood;
    int _shift_time;
    std::vector<int> _not_fav_id;
};

