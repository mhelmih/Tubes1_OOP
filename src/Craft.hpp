#ifndef CRAFT_HPP
#define CRAFT_HPP

#include <vector>
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
        string **optCraft;

        bool namedBased; // for switching name and type based crafting
        bool isMirrored; 

        int optRow; // Optimized slot craft row
        int optCol; // Optimized slot craft col
    public:
        
        Craft(); //diisi sama item "null" (dibuat pake default constructor)
        ~Craft();
        
        bool isFull();
        void emptyingCraft();
        bool isRecipe(ItemRecipe ls,bool isName);

        bool emptyRow(int idx);
        bool emptyCol(int idx);

        void swapCol(); // Swap columns 1 and 3
        vector<int> idxSlotTool();

        Item* &operator[](int idx);
        void updateCurCraft();
        void updateOptimizedCrft();
};

#endif