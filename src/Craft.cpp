#include "Craft.hpp"

Craft::Craft(){
    
    slot.assign(9, 0);
    for(int i=0; i<9; i++){
        this->curName[i] = "";
    }
}

Craft::~Craft(){
    for (Item* item : this->slot) {
        delete[] item;
    }
    this->slot.clear();
}

Item* &Craft::operator[](int idx) {
    // harus ditambahin exception kalo lebih dari 27
    return slot[idx];
}