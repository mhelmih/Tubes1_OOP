
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "Craft.cpp"
#include "Item.cpp"
#include "configGame.cpp"
#include "CraftingTable.cpp"
#include "Inventory.cpp"
using namespace std;

int main() {
    // Inventory tes;
    // Craft a;
    // a[0]->printInfo();
    // cout << "Tes" << endl;
    CraftingTable ct;
    ct.readConfig();
    ct.readCommand();
    return 0;
}