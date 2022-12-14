#pragma once
#include <iostream>
#include <vector>
#include "wholesalePackaging.h"

class Shelf {
public:
    void setShelfSize(size_t shelf_size) {
        _shelf_size = shelf_size;
    }
    void setWsPacks(std::vector<std::pair<wholesalePackaging*, int>> ws_packagings) {
        _ws_packagings = ws_packagings;
    }

    size_t getShelfSize() {
        return _shelf_size;
    }
    std::vector<std::pair<wholesalePackaging*, int>> getWsPacks() {
        return _ws_packagings;
    }


private:
    std::vector<std::pair<wholesalePackaging*, int>> _ws_packagings;
    size_t _shelf_size;

};

