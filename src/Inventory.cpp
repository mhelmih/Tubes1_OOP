#include "Inventory.hpp"

Inventory::Inventory() {
    this->slot = new Item[INVENTORY_SLOT];
    for (int i = 0; i < INVENTORY_SLOT; i++) {
        this->slot[i] = Item();
    }
}

Inventory::~Inventory() {
    delete[] slot;
}

Item Inventory::operator[](int idx) {
    // harus ditambahin exception kalo lebih dari 27
    return this->slot[idx];
}

vector<int> Inventory::isIn(string name) {
    vector<int> idx;
    for (int i = 0; i < INVENTORY_SLOT; i++) {
        if (this->slot[i].get_name() == name) {
            idx.push_back(i);
        }
    }

    return idx;
}

// void Inventory::give(Tool item) {
//     int i = 0;
//     bool flag = false;
//     while(i < INVENTORY_SLOT && !flag){
//         if(this->slot[i].get_id()==-1){
//             this->slot[i] = item;
//             flag = true;
//         }else{
//             i++;
//         }
//     }
// }

// void Inventory::give(NonTool item, int quantity) {
//     vector<int> idx = isIn(item.get_name());
//     int i = 0;
//     while (idx.size() > 0 && quantity > 0) {
//         if (this->slot[idx[i]].get_quantity()) {
            
//         }
//     }
// }