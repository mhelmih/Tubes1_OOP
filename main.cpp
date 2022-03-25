#include "src/CraftingTable.cpp"
#include "src/Item.cpp"
#include "src/configGame.cpp"
#include "src/Inventory.cpp"
#include "src/Craft.cpp"
#include <bits\stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    
    cout << " __  __ _____ _____  _____ _____  __  __ ______ _   _ _  _______  ______ _____  " << endl;
    cout << "|  \\/  |_   _|  __ \\|_   _|  __ \\|  \\/  |  ____| \\ | | |/ /  __ \\|  ____|  __ \\ " << endl;
    cout << "| \\  / | | | | |__) | | | | |__) | \\  / | |__  |  \\| | ' /| |__) | |__  | |__) |" << endl;
    cout << "| |\\/| | | | |  _  /  | | |  ___/| |\\/| |  __| | . ` |  < |  _  /|  __| |  ___/ " << endl;
    cout << "| |  | |_| |_| | \\ \\ _| |_| |    | |  | | |____| |\\  | . \\| | \\ \\| |____| |     " << endl;
    cout << "|_|  |_|_____|_|  \\_\\_____|_|    |_|  |_|______|_| \\_|_|\\_\\_|  \\_\\______|_|     " << endl;
    cout << endl;                                                                             
    cout << "Enter 'HELP' to show the command list." << endl;                                                                        

    CraftingTable ct;
    ct.readConfig();
    ct.readCommand();
    return 0;
}