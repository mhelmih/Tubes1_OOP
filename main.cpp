#include "src/CraftingTable.cpp"
#include "src/Item.cpp"
#include "src/configGame.cpp"
#include "src/Inventory.cpp"
#include "src/Craft.cpp"
#include <bits\stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    CraftingTable ct;
    ct.readConfig();
    ct.readCommand();
    return 0;
}