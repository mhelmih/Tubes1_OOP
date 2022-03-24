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
        line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
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
    // listItemConfig.printList();

    // read recipes
    for (const auto &entry : filesystem::directory_iterator(configPath + "/recipe")) {
        // cout << entry.path() << endl;
        // read from file and do something

        ifstream itemConfigRecipe(entry.path());

        // split line setiap file config
        for (string line; getline(itemConfigRecipe, line);) {
             // menghapus newline
            line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
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
    // this->listRecipeConfig.printListRecipe();

    // test list exception
    // try{
    //     ItemRecipe *temp = new ItemRecipe(listRecipeConfig[0]);
    //     cout << temp->getElement(1, 0)<<endl;
    // }
    // catch (const char* msg){
    //     cout << msg <<endl;
    // }
}

void CraftingTable::help() {
    cout << "COMMAND LIST" << endl;
    cout << "================================================================================================================" << endl;
    cout << "HELP   : to show the command list." << endl;
    cout << "ITEMS  : to show the item listed from the config file." << endl;
    cout << "RECIPE : to show the recipe to craft an item." << endl;
    cout << "SHOW   : to show the inventory and crafting table." << endl;
    cout << "GIVE   : to add an item to inventory." << endl;
    cout << "         for NonTools: GIVE <ITEM_NAME> <ITEM_QTY>" << endl;
    cout << "         for Tools   : GIVE <ITEM_NAME>" << endl;
    cout << "DISCARD: to decrease a NonTool item from inventory." << endl;
    cout << "         syntax: DISCARD I<INVENTORY_SLOT_ID> <ITEM_QTY>" << endl;
    cout << "MOVE   : to move items between inventory slots or between inventory and crafting table slots." << endl;
    cout << "         inventory > inventory     : MOVE I<INVENTORY_SLOT_ID_SRC> 1 I<INVENTORY_SLOT_ID_DEST>" << endl;
    cout << "         inventory > crafting table: MOVE I<INVENTORY_SLOT_ID> N C<CRAFTING_SLOT_ID_1> ... C<CRAFTING_SLOT_ID_N>" << endl;
    cout << "         crafting table > inventory: MOVE C<CRAFTING_SLOT_ID> 1 I<INVENTORY_SLOT_ID>" << endl;
    cout << "USE    : to use an item (decrease the durability by one)." << endl;
    cout << "         syntax: USE I<INVENTORY_SLOT_ID>" << endl;
    cout << "CRAFT  : to craft items based on the recipe." << endl;
    cout << "EXPORT : to export the items inside inventory." << endl;
    cout << "         syntax: EXPORT <FILE_NAME>" << endl;
    cout << "EXIT   : to exit the program." << endl;
}

void CraftingTable::printItemList() {
    cout << "TODO" << endl;
}

void CraftingTable::show() {
    int crfIdx = 0;
    int invIdx = 0;

    // print craft slot
    while (crfIdx < CRAFT_SLOT) {
        // padding
        if (crfIdx % CRAFT_COL == 0) {
            for (int i = 0; i < 36; i++) {
                cout << " ";
            }
        }
        cout << "[C" << crfIdx << " |";
        if (!crf[crfIdx]->isA<Tool>() && !crf[crfIdx]->isA<NonTool>()) {
            cout << "-- --";
        } else{
            crf[crfIdx]->printInfo();
        }
        cout << "] ";

        // newline every 3
        if ((crfIdx + 1) % CRAFT_COL == 0) {
            cout << endl;
        }
        crfIdx++;
    }
    cout << endl;

    // print inventory slot
    while (invIdx < INVENTORY_SLOT) {
        if (invIdx < 10) {
            cout << "[I" << invIdx << " |";
        } else {
            cout << "[I" << invIdx << "|";
        }
        if (!inv[invIdx]->isA<Tool>() && !inv[invIdx]->isA<NonTool>()) {
            cout << "-- --";
        } else{
            inv[invIdx]->printInfo();
        }
        cout << "] ";
        // newline every 9
        if ((invIdx + 1) % INVENTORY_COL == 0) {
            cout << endl;
        }
        invIdx++;
    }
}

void CraftingTable::give() {
    string itemName;
    int itemQty, i;
    bool found;

    cin >> itemName;
    i = 0;
    found = false;
    while (i <= listItemConfig.get_Neff() && !found) {
        if (itemName == listItemConfig[i].get_name()) {
            found = true;
        } else {
            i++;
        }
    }

    if (found) {
        if (listItemConfig[i].get_category() == "TOOL") {
            Tool* itm = new Tool(listItemConfig[i].get_id(), listItemConfig[i].get_name(), listItemConfig[i].get_type());
            inv.give(itm);
        } else if (listItemConfig[i].get_category() == "NONTOOL") {
            cin >> itemQty;
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

// void CraftingTable::moveToCraft(int invIdx, int qty, int crfId) {
//     cout << "TODO" << endl;
// }
// void CraftingTable::movetoStack(int invIdxSrc, int invIdDest) {
//     cout << "TODO" << endl;
// }
// void CraftingTable::moveToInventory(int crfIdx, int invIdx) {
//     cout << "TODO" << endl;
// }

void CraftingTable::moveToCraft(int invIdx, int* crfIdx){
    string tipeInv = this->inv[invIdx]->get_type();
    int size = sizeof(crfIdx) / sizeof(crfIdx[0]);
    for (int i=0; i < size; i++) {
        if (this->crf[crfIdx[i]] == 0) {
            this->crf[crfIdx[i]] = this->inv[invIdx];
            if(this->inv[invIdx]->get_type() == "TOOL"){
                this->inv[invIdx] = 0;
            } else if (this->inv[invIdx]->get_type() == "NONTOOL"){
                NonTool* nt = dynamic_cast<NonTool*>(this->inv[invIdx]);
                nt->set_quantity(nt->get_quantity() - 1);
            };
        } else {
            //sudah terisi
            cout << "slot crafting sudah terisi" << endl;
        }
    }
    

}
void CraftingTable::movetoStack(int invIdxSrc, int invIdxDest){
    string tipeSrc = this->inv[invIdxSrc]->get_type();
    string tipeDest = this->inv[invIdxDest]->get_type();
    if (tipeSrc == "NONTOOL" && tipeDest == "NONTOOL") {
        NonTool* ntSrc = dynamic_cast<NonTool*>(this->inv[invIdxSrc]);
        NonTool* ntDest = dynamic_cast<NonTool*>(this->inv[invIdxDest]);
        if (ntSrc->get_name() == ntDest->get_name()) {
            if (ntSrc->get_quantity() + ntDest->get_quantity() <= 64) {
                ntDest->set_quantity(ntSrc->get_quantity() + ntDest->get_quantity());
                this->inv[invIdxSrc] = 0;
            }
            else {
                ntDest->set_quantity(64);
                ntSrc->set_quantity(ntSrc->get_quantity() - (64 - ntDest->get_quantity()));
            }
        } else {
            cout << "invalid move" << endl;
        }
    } else {
        cout << "invalid move" << endl;
    }
}
void CraftingTable::moveToInventory(int crfIdx, int invIdx){
    string tipeCraft = this->crf[crfIdx]->get_type();
    string tipeInv = this->inv[invIdx]->get_type();
    if (this->inv[invIdx] == 0) {
        this->inv[invIdx] = this->crf[crfIdx];
        this->crf[crfIdx] = 0;
    } else if (this->crf[crfIdx] == 0) {
        //slot crafting kosong
        cout << "Crafting kosong" << endl;
    } else if (tipeCraft == "NonTool" && tipeInv == "NonTool") {
        if (this->crf[crfIdx]->get_name() == this->inv[invIdx]->get_name()) {
            NonTool* ntCraft = dynamic_cast<NonTool*>(this->crf[crfIdx]);
            NonTool* ntInv = dynamic_cast<NonTool*>(this->inv[invIdx]);
            if (ntInv->get_quantity() <= 64-1) {
                ntInv->set_quantity(1 + ntInv->get_quantity());
                this->crf[crfIdx] = 0;
            }
            else {
                //full
                cout << "Inventory Full" << endl;
            }
        } else {
            //inventory ada isinya
            cout << "Inventory sudah terisi" << endl;
        }
    } else {
        //crafting ada isinya
        cout << "Inventory sudah terisi" << endl;
    }
}


void CraftingTable::use() {
    string invIdx;
    int idx;

    cin >> invIdx;
    invIdx = invIdx.substr(1,2);
    idx = stoi(invIdx);
    if (idx < INVENTORY_SLOT) {
        if (inv[idx] == 0) {
            cout << "I" << invIdx << " is empty." << endl;
        } else if (inv[idx]->isA<Tool>()) {
            Tool* temp = dynamic_cast<Tool*>(inv[idx]);
            temp->use();

            // if durability = 0, delete the tool
            if (temp->get_durability() == 0) {
                inv[idx] = 0;
            }
        } else {
            cout << inv[idx]->get_name() << " is not a tool." << endl;
        }
    } else {
        cout << "Index out of range." << endl;
    }
    
}
void CraftingTable::craft() {
    bool flag = false;
    int i = 0;
    while(i<listRecipeConfig.get_Neff() && !flag){
        if(true){
            flag = true;
        }else{
            i++;
        }
    }

    if(i<listRecipeConfig.get_Neff()){
        string itemName = listRecipeConfig[i].get_item();
        int itemQty = listRecipeConfig[i].get_quantity();
        int i=0;
        bool found=false;
        while (i < listItemConfig.get_Neff() && !found) {
            if (itemName == listItemConfig[i].get_name()) {
                found = true;
            } else {
                i++;
            }
        }

        if (found) {
            if (listItemConfig[i].get_category() == "TOOL") {
                Tool* itm = new Tool(listItemConfig[i].get_id(), listItemConfig[i].get_name(), listItemConfig[i].get_type());
                inv.give(itm);
            } else if (listItemConfig[i].get_category() == "NONTOOL") {
                NonTool* itm = new NonTool(listItemConfig[i].get_id(), listItemConfig[i].get_name(), listItemConfig[i].get_type(), itemQty);
                inv.give(itm, itemQty);
            } else {
                cout << "Category " << listItemConfig[i].get_category() << " Unknown." << endl;
            }
        } else {
            cout << "Item " << itemName << " Not Found." << endl;
        }
    }else{
        cout << "recipe not found";
    }
}

void CraftingTable::exportInventory(string outputPath) {
    ofstream outputFile(outputPath);
    int invIdx = 0;
    while (invIdx < INVENTORY_SLOT){
        if (!inv[invIdx]->isA<Tool>() && !inv[invIdx]->isA<NonTool>()) {
            outputFile << "0:0";
        } else{
            outputFile<< inv[invIdx]->printExport();
        }
        outputFile<<endl;
        invIdx++;
    }
}

void CraftingTable::readCommand() {
    cout << ">>> ";
    cin >> this->command;
    while (this->command != "EXIT") {
        if (command == "HELP") {
            help();
        } else if (command == "ITEMS") {
            this->listItemConfig.printList();
        } else if (command == "RECIPE") {
            this->listRecipeConfig.printListRecipe();
        } else if (command == "SHOW") {
            show();
        } else if (command == "GIVE") {
            give();
        } else if (command == "DISCARD") {
            cout << "TODO" << endl;
        }else if (command == "MOVE") {
            string slotSrc;
            int slotQty;
            string* multislotDest;
            // need to handle multiple destinations
            cin >> slotSrc >> slotQty;
            
            multislotDest = new string[slotQty];
            for (int i=0; i<slotQty; i++) {
                cin >> multislotDest[i];
            }
            
            string source;
            string destination;
            int idxSrc;
            int* idxDest;
            
            source = slotSrc[0];
            idxSrc = stoi(slotSrc);
            destination = multislotDest[0][0];
            
            idxDest = new int[slotQty];
            for (int i=0; i<slotQty; i++) {
                idxDest[i] = multislotDest[i][1];
            }
            
            if (source == "C"){
                moveToInventory(idxSrc, idxDest[0]);
            } else if (source == "I") {
                if (destination == "I") {
                    movetoStack(idxSrc, idxDest[0]);
                } else if (destination == "C") {
                    moveToCraft(idxSrc, idxDest);
                }
            }
            
        
            cout << "TODO" << endl;
        } else if (command == "USE") {
            use();
        } else if (command == "CRAFT") {
            cout << "TODO" << endl;
        } else if (command == "EXPORT") {
            string outputPath;
            cout << "masukkan nama file: ";
            cin >> outputPath;
            exportInventory(outputPath);
        } else {
            cout << "Invalid command" << endl;
        }
        cout << endl;
        cout << ">>> ";
        cin >> this->command;
    }
}