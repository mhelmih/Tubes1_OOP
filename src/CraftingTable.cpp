#include "CraftingTable.hpp"

CraftingTable::CraftingTable() {
    this->command = "";
    this->configPath = "./config";
    this->itemConfigPath = configPath + "/item.txt";
    this->recipeConfigPath = configPath + "/recipe";
}

CraftingTable::~CraftingTable() {

}

void CraftingTable::readItemConfig(vector<string> &words) {
    ItemConfig temp;
    int iwords = 0;
    temp.set_id(get_number(words[iwords]));
    iwords++;
    temp.set_name(words[iwords]);
    iwords++;
    temp.set_type(words[iwords]);
    iwords++;
    temp.set_category(words[iwords]);
    iwords++;
    try{
        this->listItemConfig.addElmt(temp);;
    }
    catch(string& s){
        cout << "list item config is full"<< endl;
    }
}

void CraftingTable::readItemRecipe(vector<string> &wordsrecipe) {
    int iwordsrecipe = 0;
    int row, col;
    row = get_number(wordsrecipe[iwordsrecipe]);
    iwordsrecipe++;
    col = get_number(wordsrecipe[iwordsrecipe]);
    iwordsrecipe++;

    ItemRecipe *temp = new ItemRecipe(row, col);
    
    // read matrix
    for (int i =0;i<row;i++) {
        for (int j =0;j<col;j++) {
            temp->set_matrix(wordsrecipe[iwordsrecipe], i, j);
            iwordsrecipe++;
        }
    }

    temp->set_item(wordsrecipe[iwordsrecipe]);
    iwordsrecipe++;
    temp->set_quantity(get_number(wordsrecipe[iwordsrecipe]));
    iwordsrecipe++;
    try{
        this->listRecipeConfig.addRecipe(*temp);
    }
    catch(string& s){
        cout << "list recipe is full"<< endl;
    }
}

void CraftingTable::readConfig() {
    // menampung line yang sudah displit
    vector<string> words{};
    vector<string> wordsrecipe{};
    size_t pos;
    string delimiter = " ";

    // read item from config file
    ifstream itemConfigFile(this->itemConfigPath);
    for (string line; getline(itemConfigFile, line);) {
        // menghapus newline
        line.pop_back();
        // split line
        while ((pos = line.find(delimiter)) != string::npos) {
            words.push_back(line.substr(0, pos));
            line.erase(0, pos + delimiter.length());
        }
        words.push_back(line.substr(0, line.size()));

        // read item
        readItemConfig(words);
        words.clear();
    }

    // show list
    listItemConfig.printList();

    // read recipes
    for (const auto &entry : filesystem::directory_iterator(configPath + "/recipe")) {
        // cout << entry.path() << endl;
        // read from file and do something

        ifstream itemConfigRecipe(entry.path());

        // split line setiap file config
        for (string line; getline(itemConfigRecipe, line);) {

            while ((pos = line.find(delimiter)) != string::npos) {
                wordsrecipe.push_back(line.substr(0, pos));
                line.erase(0, pos + delimiter.length());
            }
            wordsrecipe.push_back(line.substr(0, line.size()));
        }

        // read recipe
        readItemRecipe(wordsrecipe);
        wordsrecipe.clear();
    }
    // print recipe
    this->listRecipeConfig.printListRecipe();

    // test list exception
    try{
        ItemRecipe *temp = new ItemRecipe(listRecipeConfig[0]);
        cout << temp->getElement(1, 0)<<endl;
    }
    catch (const char* msg){
        cout << msg <<endl;
    }
}

void CraftingTable::help() {
    cout << "TODO" << endl;
}

void CraftingTable::printItemList() {
    cout << "TODO" << endl;
}

void CraftingTable::show() {
    int crfIdx = 0;
    int invIdx = 0;

    while (crfIdx < CRAFT_SLOT) {
        if (crfIdx % CRAFT_COL == 0) {
            for (int i = 0; i < 27; i++) {
                cout << " ";
            }
        }
        cout << "[0" << crfIdx + 1 << "|";
        if (!crf[crfIdx]->isA<Tool>() && !crf[crfIdx]->isA<NonTool>()) {
            cout << "-- --";
        } else{
            crf[crfIdx]->printInfo();
        }
        cout << "] ";
        if ((crfIdx + 1) % CRAFT_COL == 0) {
            cout << endl;
        }
        crfIdx++;
    }
    cout << endl;

    while (invIdx < INVENTORY_SLOT) {
        if (invIdx < 9) {
            cout << "[0" << invIdx + 1 << "|";
        } else {
            cout << "[" << invIdx + 1 << "|";
        }
        
        if (!inv[invIdx]->isA<Tool>() && !inv[invIdx]->isA<NonTool>()) {
            cout << "-- --";
        } else{
            inv[invIdx]->printInfo();
        }
        cout << "] ";
        if ((invIdx + 1) % INVENTORY_COL == 0) {
            cout << endl;
        }
        invIdx++;
    }
    cout << endl;
}

void CraftingTable::give() {
    string itemName;
    int itemQty, i;
    bool found;

    cin >> itemName >> itemQty;
    i = 0;
    found = false;
    while (i < listItemConfig.get_Neff() && !found) {
        if (itemName == listItemConfig[i].get_name()) {
            found = true;
        } else {
            i++;
        }
    }

    if (found) {
        if (listItemConfig[i].get_category() == "TOO") {
            Tool* itm = new Tool(listItemConfig[i].get_id(), listItemConfig[i].get_name(), listItemConfig[i].get_type());
            inv.give(itm);
            // masih belum bisa masukin tool lebih dari 1
        } else if (listItemConfig[i].get_category() == "NONTOO") {
            NonTool* itm = new NonTool(listItemConfig[i].get_id(), listItemConfig[i].get_name(), listItemConfig[i].get_type(), itemQty);
            inv.give(itm, itemQty);
        } else {
            cout << "Category " << listItemConfig[i].get_category() << " Unknown." << endl;
        }
    } else {
        cout << "Item " << itemName << " Not Found." << endl;
    }
    
}

void CraftingTable::discard(int invId, int qty) {
    inv.discard(invId, qty);
}

void CraftingTable::moveToCraft(int invIdx, int qty, int crfId) {
    cout << "TODO" << endl;
}
void CraftingTable::movetoStack(int invIdxSrc, int invIdDest) {
    cout << "TODO" << endl;
}
void CraftingTable::moveToInventory(int crfIdx, int invIdx) {
    cout << "TODO" << endl;
}
void CraftingTable::use() {
    int invIdx;
    cin >> invIdx;
    cout << "TODO" << endl;
}
void CraftingTable::craft() {
    cout << "TODO" << endl;
}
void CraftingTable::exportInventory() {
    cout << "TODO" << endl;
}

void CraftingTable::readCommand() {
    cout << ">>> ";
    cin >> this->command;
    while (this->command != "EXIT") {
        if (command == "EXPORT") {
            cout << "TODO" << endl;
        } else if (command == "SHOW") {
            show();
        } else if (command == "GIVE") {
            give();
        } else if (command == "USE") {
            use();
        } else if (command == "MOVE") {
            string slotSrc;
            int slotQty;
            string slotDest;
            // need to handle multiple destinations
            cin >> slotSrc >> slotQty >> slotDest;
            cout << "TODO" << endl;
        } else {
            // todo
            cout << "Invalid command" << endl;
        }
        cout << ">>> ";
        cin >> this->command;
    }
}