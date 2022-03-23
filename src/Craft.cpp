#include "Craft.hpp"

Craft::Craft(){
    
    slot.assign(9, 0);
    // slot[0] = new Tool();
    // Tool* tool = slot[0];
    // tool->get_durability();
    // Tool* tool = dynamic_cast<Tool*>(slot[0]);
    // tool->get_durability();
}

Craft::~Craft(){
    for (Item* item : this->slot) {
        delete[] item;
    }
    this->slot.clear();
}

bool Craft::isRecipe(){
    return true;
}

void Craft::show(){
    cout << "test";
}

Item* &Craft::operator[](int idx) {
    // harus ditambahin exception kalo lebih dari 27
    return slot[idx];
}