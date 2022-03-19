#include "CraftingTable.hpp"

CraftingTable::CraftingTable() {
    this->command = "";
    this->configPath = "./config";
    this->itemConfigPath = configPath + "/item";
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
    this->listItemConfig.addElmt(temp);
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

    this->listRecipeConfig.addRecipe(*temp);
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
        // cout << line << endl;
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
    this->listRecipeConfig.printListRecipe();
}

void CraftingTable::help() {
    cout << "TODO" << endl;
}

void CraftingTable::printItemList() {
    cout << "TODO" << endl;
}

void CraftingTable::show() {
    cout << "TODO" << endl;
}

void CraftingTable::give(Item itm, int qty) {
    cout << "TODO" << endl;
}

void CraftingTable::discard(int invId, int qty) {
    cout << "TODO" << endl;
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
void CraftingTable::use(int invIdx) {
    cout << "TODO" << endl;
}
void CraftingTable::craft() {
    cout << "TODO" << endl;
}
void CraftingTable::exportInventory() {
    cout << "TODO" << endl;
}

void CraftingTable::readCommand() {
    while (cin >> this->command && this->command != "EXIT") {
        if (command == "EXPORT") {
            
        } else if (command == "CRAFT") {
            cout << "TODO" << endl;
        } else if (command == "GIVE") {
            string itemName;
            int itemQty;
            cin >> itemName >> itemQty;
            cout << "TODO" << endl;
        } else if (command == "MOVE") {
            string slotSrc;
            int slotQty;
            string slotDest;
            // need to handle multiple destinations
            cin >> slotSrc >> slotQty >> slotDest;
            cout << "TODO" << endl;
        } else if (command == "EXIT"){
            cout << "TODO" << endl;
        } else {
            // todo
            cout << "Invalid command" << endl;
        }
    }
}