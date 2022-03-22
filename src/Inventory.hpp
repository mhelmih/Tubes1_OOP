#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <vector>
#include "Item.hpp"

#define INVENTORY_SLOT 27
#define INVENOTRY_ROW 3
#define INVENTORY_COL 9

class Inventory {
    private:
        vector<Item*> slot;
    public:
        Inventory(); //diisi sama item "null" (dibuat pake default constructor)
        ~Inventory();
        Item operator[](int idx);
        vector<int> isIn(string name); // mencari semua indeks kemunculan item dengan nama name
        bool isFull();
        void give(NonTool item, int quantity);
        void give(Tool item);
        void discard(int idx, int quantity);
        void use(int idx);
};

#endif