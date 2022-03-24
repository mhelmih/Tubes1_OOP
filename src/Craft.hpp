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

        int optRow; // Optimized slot craft row
        int optCol; // Optimized slot craft col
    public:
        
        Craft(); //diisi sama item "null" (dibuat pake default constructor)
        ~Craft();
        
        bool isFull();
        void emptyingCraft();
        bool isRecipe(ItemRecipe ls);

        // void setIsMirrored(bool flag);
        // bool getIsMirrored();

        bool emptyRow(int idx);
        bool emptyCol(int idx);

        void swapCol(); // Swap columns 1 and 3

        Item* &operator[](int idx);
        void getCurCraft();
        string** getOptimizedCrft();

        //void give(NonTool item, int quantity);
        //void give(Tool item);


        
        
};

#endif