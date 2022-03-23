#include "Inventory.hpp"

Inventory::Inventory() {
    this->slot.assign(27, 0);
}

Inventory::~Inventory() {
    for (Item* item : this->slot) {
        delete[] item;
    }
    this->slot.clear();
}

Item* &Inventory::operator[](int idx) {
    // harus ditambahin exception kalo lebih dari 27
    return slot[idx];
}

vector<int> Inventory::isIn(string name) {
    vector<int> idx;
    for (int i = 0; i < INVENTORY_SLOT; i++) {
        if (this->slot[i]->isA<Tool>() || this->slot[i]->isA<NonTool>()) {
            cout << this->slot[i]->get_name() << endl;
            if (this->slot[i]->get_name() == name) {
                idx.push_back(i);
            }
        }
    }

    return idx;
}

void Inventory::give(Tool* item) {
    int i = 0;
    bool flag = false;
    while(i < INVENTORY_SLOT && !flag){
        if(this->slot[i]->get_id() == -1){
            this->slot[i] = item;
            flag = true;
        }
        else{
            i++;
        }
    }
}

void Inventory::give(NonTool* item, int quantity) {
    vector<int> idx = isIn(item->get_name());
    int i = 0;
    while (idx.size() > 0 && quantity > 0) {
        NonTool* nt = dynamic_cast<NonTool*>(this->slot[idx[i]]);
        if (nt->get_quantity() + quantity <= 64) {
            nt->set_quantity(nt->get_quantity() + quantity);
            quantity = 0;
        }
        else {
            quantity = quantity + nt->get_quantity() - 64;
            nt->set_quantity(64);
        }
        this->slot[idx[i]] = nt;
    }
}

void Inventory::discard(int idx, int quantity) {
    if (this->slot[idx]->isA<NonTool>()) {
        NonTool* nt = dynamic_cast<NonTool*>(this->slot[idx]);
        if (quantity <= nt->get_quantity()) {
            nt->set_quantity(nt->get_quantity() - quantity);
            this->slot[idx] = nt;
        }
        else {
            this->slot.erase(slot.begin() + idx);
        }
    }
    else {
        cout << "Tidak bisa membuang item tool dengan kauntitas yang diberikan" << '\n';
    }
}