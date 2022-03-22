
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "Craft.cpp"
#include "Item.cpp"
#include "configGame.cpp"

using namespace std;

int main() {
    // Inventory tes;
    Craft a;
    a.slot[0]->printInfo();
    cout << "Tes" << endl;
    return 0;
}