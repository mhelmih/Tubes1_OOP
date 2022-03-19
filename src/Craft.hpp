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
        Item slot[9];

        //Atribut buat pengecekan
        string curName[3][3];

    public:
        Craft(); //diisi sama item "null" (dibuat pake default constructor)
        ~Craft();

        bool isRecipe();
        void show();
        // void Crafting();
        // Item operator[](int idx);
        // vector<int> isIn(string name); // mencari semua indeks kemunculan item dengan nama name
        // bool isFull();
        // void give(NonTool item, int quantity);
        // void give(Tool item);
        // void discard(int idx, int quantity);
        // void use(int idx);


        //Keperluan read recipe sementara
        
};

#endif