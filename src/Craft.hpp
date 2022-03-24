#ifndef CRAFT_HPP
#define CRAFT_HPP

#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "Item.hpp"
#include "configGame.hpp"

#define CRAFT_SLOT 9
#define CRAFT_ROW 3
#define CRAFT_COL 3

class Craft {
    private:
        vector<Item*> slot;
        string **curCraft;
        bool isMirrored;
    public:
        
        Craft(); //diisi sama item "null" (dibuat pake default constructor)
        ~Craft();

        Item* &operator[](int idx);
        string** getCurCraft();
        

        //vector<int> isIn(string name); // mencari semua indeks kemunculan item dengan nama name
        bool isFull();
        void emptyingCraft();

        void setIsMirrored(bool flag);
        bool getIsMirrored();

        int emptyRow();
        int emptyCol();

        //void give(NonTool item, int quantity);
        //void give(Tool item);


        
        
};

#endif