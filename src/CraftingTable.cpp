#include "CraftingTable.hpp"

CraftingTable::CraftingTable() {
    this->command = "";
    this->configPath = "./config";
    this->itemConfigPath = configPath + "/item.txt";
    this->recipeConfigPath = configPath + "/recipe";
}

CraftingTable::~CraftingTable() {}

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
        this->listItemConfig.addElmt(temp);
    }
    catch(string& s){
        cout << s << endl;
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
        cout << s << endl;
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

    // read recipes
    for (const auto &entry : filesystem::directory_iterator(configPath + "/recipe")) {
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
}

void CraftingTable::help() {
    cout << "COMMAND LIST" << endl;
    cout << "=================================================================================================================" << endl;
    cout << "HELP    : to show the command list." << endl;
    cout << "ITEMS   : to show the item listed from the config file." << endl;
    cout << "RECIPE  : to show the recipe to craft an item." << endl;
    cout << "SHOW    : to show the inventory and crafting table." << endl;
    cout << "GIVE    : to add an item to inventory." << endl;
    cout << "          for NonTools: GIVE <ITEM_NAME> <ITEM_QTY>" << endl;
    cout << "          for Tools   : GIVE <ITEM_NAME>" << endl;
    cout << "DISCARD : to decrease a NonTool item from inventory." << endl;
    cout << "          syntax: DISCARD I<INVENTORY_SLOT_ID> <ITEM_QTY>" << endl;
    cout << "MOVE    : to move items between inventory slots or between inventory and crafting table slots." << endl;
    cout << "          inventory > inventory     : MOVE I<INVENTORY_SLOT_ID_SRC> 1 I<INVENTORY_SLOT_ID_DEST>" << endl;
    cout << "          inventory > crafting table: MOVE I<INVENTORY_SLOT_ID> N C<CRAFTING_SLOT_ID_1> ... C<CRAFTING_SLOT_ID_N>" << endl;
    cout << "          crafting table > inventory: MOVE C<CRAFTING_SLOT_ID> 1 I<INVENTORY_SLOT_ID>" << endl;
    cout << "USE     : to use an item (decrease the durability by one)." << endl;
    cout << "          syntax: USE I<INVENTORY_SLOT_ID>" << endl;
    cout << "CRAFT   : to craft items based on the recipe." << endl;
    cout << "EXPORT  : to export the items inside inventory." << endl;
    cout << "          syntax: EXPORT <FILE_NAME>" << endl;
    cout << "EXIT    : to exit the program." << endl;
}

void CraftingTable::show() {
    int crfIdx = 0;
    int invIdx = 0;

    // print craft slot
    cout << "                                              CRAFTING TABLE" << endl; 
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
    cout << "                                                 INVENTORY" << endl;
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
            if(cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw "Wrong quantity input.";
            } else{
                NonTool* itm = new NonTool(listItemConfig[i].get_id(), listItemConfig[i].get_name(), listItemConfig[i].get_type(), itemQty);
                inv.give(itm, itemQty);
            }
        } else {
            throw "Category unknown.";
        }
    } else {
        throw "Item not found.";
    }
}

void CraftingTable::discard() {
    string invSlot;
    int qty, invId = 0;
    cin >> invSlot >> qty;
    for (int i = 1; i < invSlot.length(); i++) {
        invId = invId * 10 + (invSlot[i] - '0');
    }
    inv.discard(invId, qty);
}

void CraftingTable::move() {
    string* multislotDest;
    string slotSrc, source, destination;
    int* idxDest;
    int slotQty, idxSrc;
    
    // need to handle multiple destinations
    cin >> slotSrc >> slotQty;
    
    multislotDest = new string[slotQty];
    for (int i=0; i<slotQty; i++) {
        cin >> multislotDest[i];
    }
    
    // string slicing to capture important keywords
    source = slotSrc.substr(0,1);
    idxSrc = stoi(slotSrc.substr(1,2));
    destination = multislotDest[0].substr(0,1);
    idxDest = new int[slotQty];
    for (int i=0; i<slotQty; i++) {
        idxDest[i] = stoi(multislotDest[i].substr(1,2));
    }
    
    if (slotQty > 0) {
        if (source == "C"){
            moveToInventory(idxSrc, idxDest[0]);
        } else if (source == "I") {
            if (this->inv[idxSrc] == 0) {
                cout << "I" << idxSrc << " is empty." << endl;
            } else {
                if (destination == "I") {
                    if (slotQty == 1) {
                        movetoStack(idxSrc, idxDest[0]);    
                    } else {
                        cout << "Wrong syntax." << endl;
                    }
                } else if (destination == "C" && slotQty) {
                    // Tool harus 1
                    if (this->inv[idxSrc]->isA<Tool>() && slotQty == 1) {
                        moveToCraft(idxSrc, idxDest, slotQty);
                    // NonTool harus <= quantity
                    } else if (this->inv[idxSrc]->isA<NonTool>()) {
                        NonTool* temp = dynamic_cast<NonTool*>(inv[idxSrc]);
                        if (temp->get_quantity() >= slotQty) {
                            moveToCraft(idxSrc, idxDest, slotQty);
                        } else {
                            cout << slotQty << " is too much." << endl;
                        }
                    } else {
                        cout << slotQty << " is too much." << endl;
                    }
                } else {
                    cout << "Wrong syntax." << endl;
                }
            }
        }
    }
    show();
}

void CraftingTable::moveToCraft(int invIdx, int* crfIdx, int qty){
    if (this->inv[invIdx] == 0) {
        cout << "I " << invIdx << "is empty." << endl;
    } else {
        for (int i=0; i < qty; i++) {
            if (this->crf[crfIdx[i]] == 0) {
                if (this->inv[invIdx]->isA<Tool>()){
                    Tool* temp = dynamic_cast<Tool*>(inv[invIdx]);
                    Tool* temp1 = new Tool(*temp);
                    this->crf[crfIdx[0]] = temp1;
                    this->inv[invIdx] = 0;
                } else if (this->inv[invIdx]->isA<NonTool>()) {
                    NonTool* temp = dynamic_cast<NonTool*>(inv[invIdx]);
                    NonTool* temp1 = new NonTool(*temp);    
                    temp1->set_quantity(1);
                    this->crf[crfIdx[i]] = temp1;
                    NonTool* nt = dynamic_cast<NonTool*>(this->inv[invIdx]);
                    nt->set_quantity(nt->get_quantity() - 1);
                    if (nt->get_quantity() == 0) {
                        this->inv[invIdx] = 0;
                    }
                };
            } else {
                //sudah terisi
                cout << "C" << crfIdx[i] << " is occupied." << endl;
            }
        }
    }
}

void CraftingTable::movetoStack(int invIdxSrc, int invIdxDest){
    if (this->inv[invIdxSrc] == 0) {
        cout << "I" << invIdxSrc << "is empty." << endl;
    } else {
        if (this->inv[invIdxDest] == 0) {
            this->inv[invIdxDest] = this->inv[invIdxSrc];
            this->inv[invIdxSrc] = 0;
        } else {
            if (this->inv[invIdxSrc]->isA<NonTool>() && this->inv[invIdxDest]->isA<NonTool>()) {
                NonTool* ntSrc = dynamic_cast<NonTool*>(this->inv[invIdxSrc]);
                NonTool* ntDest = dynamic_cast<NonTool*>(this->inv[invIdxDest]);
                if (ntSrc->get_name() == ntDest->get_name()) {
                    if (ntSrc->get_quantity() + ntDest->get_quantity() <= 64) {
                        ntDest->set_quantity(ntSrc->get_quantity() + ntDest->get_quantity());
                        this->inv[invIdxSrc] = 0;
                    }
                    else {
                        ntSrc->set_quantity(ntSrc->get_quantity() - (64 - ntDest->get_quantity()));
                        ntDest->set_quantity(64);
                    }
                } else {
                    cout << "Invalid move." << endl;
                }
            } else {
                cout << "Invalid move." << endl;
            }    
        }   
    }
}

void CraftingTable::moveToInventory(int crfIdx, int invIdx){
    if (this->crf[crfIdx] == 0) {
        //slot crafting kosong
        cout << "C" << crfIdx << " is empty." << endl;
    } else if (this->inv[invIdx] == 0) {
        this->inv[invIdx] = this->crf[crfIdx];
        this->crf[crfIdx] = 0;
    } else if (this->crf[crfIdx]->isA<NonTool>() && this->inv[invIdx]->isA<NonTool>()) {
        if (this->crf[crfIdx]->get_name() == this->inv[invIdx]->get_name()) {
            NonTool* ntCraft = dynamic_cast<NonTool*>(this->crf[crfIdx]);
            NonTool* ntInv = dynamic_cast<NonTool*>(this->inv[invIdx]);
            if (ntInv->get_quantity() <= 64-1) {
                ntInv->set_quantity(1 + ntInv->get_quantity());
                this->crf[crfIdx] = 0;
            }
            else {
                //full
                cout << "I" << invIdx << " is full." << endl;
            }
        } else {
            //inventory ada isinya
            cout << "Different type of NonTool" << endl;
        }
    } else {
        cout << "Invalid move. I" << invIdx << " is a Tool." << endl;
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
    bool craftTool = false;
    if (crf.idxSlotTool().size() == 2) { // Combine TOOL
        cout << "Success !!!" << endl;
        craftTool = true;
        int i = crf.idxSlotTool()[0];
        int j = crf.idxSlotTool()[1];
        Tool *srcTool = dynamic_cast<Tool *>(crf[i]);
        Tool *dstTool = dynamic_cast<Tool *>(crf[j]);
        if (srcTool->get_name() == dstTool->get_name()){
            dstTool->set_durability(srcTool->get_durability() + dstTool->get_durability());
            if (dstTool->get_durability() > 10) {
                dstTool->set_durability(10);
            }
            inv.give(dstTool);
            crf.emptyingCraft();
        } else {
            throw "Two different type of tools can't be combined.";
        }
    } else if (crf.idxSlotTool().size() == 1) {
        throw "Can't craft anything with 1 tool.";
    } else if (crf.idxSlotTool().size() == 0) { 
        // Craft NONTOOL & TOOL
        int i = 0;
        bool flag = false;
        while (i < listRecipeConfig.get_Neff() && !flag) {
            if (crf.isRecipe(listRecipeConfig[i], false)) {
                flag = true;
            }else if(crf.isRecipe(listRecipeConfig[i], true)){
                flag = true;
            } 
            else {
                i++;
            }
        }

        if(flag) {
            string itemName = listRecipeConfig[i].get_item();
            int itemQty = listRecipeConfig[i].get_quantity();
            int j=0;
            bool found=false;
            while (i < listItemConfig.get_Neff() && !found) {
                if (itemName == listItemConfig[j].get_name()) {
                    found = true;
                } else {
                    j++;
                }
            }
    
            cout << "Success !!!" << endl;
            if (found) {
                crf.emptyingCraft();
                if (listItemConfig[j].get_category() == "TOOL") {
                    Tool* itm = new Tool(listItemConfig[j].get_id(), listItemConfig[j].get_name(), listItemConfig[j].get_type());
                    inv.give(itm);
                } else if (listItemConfig[j].get_category() == "NONTOOL") {
                    NonTool* itm = new NonTool(listItemConfig[j].get_id(), listItemConfig[j].get_name(), listItemConfig[j].get_type(), itemQty);
                    inv.give(itm, itemQty);
                } else {
                    cout << "Category " + listItemConfig[j].get_category() + " Unknown." << endl;
                }
            } else {
                cout << "Item " << itemName + " not found." << endl;
            }
        } else {
            throw "Recipe not found.";
        }
    }else{
        throw "Too many tool at crafting table. Maximum of 2";
    }
}

void CraftingTable::exportInventory() {
    string outputPath;
    cin >> outputPath;
    ofstream outputFile(outputPath);
    int invIdx = 0;
    while (invIdx < INVENTORY_SLOT) {
        if (!inv[invIdx]->isA<Tool>() && !inv[invIdx]->isA<NonTool>()) { // empty slot
            outputFile << "0:0";
        } else {
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
        try {
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
                discard();
            }else if (command == "MOVE") {
                move();
            } else if (command == "USE") {
                use();
            } else if (command == "CRAFT") {
                craft();
            } else if (command == "EXPORT") {
                exportInventory();
            } else {
                cout << "Invalid command" << endl;
            }
        } catch (char const* s) {
            cout << s << endl;
        }
        cout << endl;
        cout << "Enter 'HELP' to show the command list." << endl;
        cout << ">>> ";
        cin >> this->command;
    }
}