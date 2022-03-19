#include "src/CraftingTable.cpp"
#include "src/Item.cpp"
#include "src/configGame.cpp"
#include "src/Inventory.cpp"
#include "src/Craft.cpp"

int main() {
    CraftingTable ct;
    ct.readConfig();
    ct.readCommand();
    return 0;
}