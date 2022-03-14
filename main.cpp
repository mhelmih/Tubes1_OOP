// sample main file, replace this with your own code
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "src/configGame.hpp"

using namespace std;

int main() {
  string configPath = "./config";
  string itemConfigPath = configPath + "/item.txt";

  // menampung line yang sudah displit
  vector<string> words{};
  vector<string> wordsrecipe{};
  int iwords = 0;
  size_t pos;
  string delimiter = " ";

  // list itemconfig
  ListItemConfig listItemConfig;
  ItemConfig temp;

  // read item from config file
  ifstream itemConfigFile(itemConfigPath);
  for (string line; getline(itemConfigFile, line);) {
    // cout << line << endl;
    // do something
    while ((pos = line.find(delimiter)) != string::npos)
    {
      words.push_back(line.substr(0, pos));
      line.erase(0, pos + delimiter.length());
    }
    words.push_back(line.substr(0, line.size()));
    while (iwords < words.size())
    {
      // for (const auto &str : words) {
      // cout << words[i] << endl;
      temp.set_id(get_number(words[iwords]));
      iwords++;
      temp.set_name(words[iwords]);
      iwords++;
      temp.set_type(words[iwords]);
      iwords++;
      temp.set_category(words[iwords]);
      iwords++;
      listItemConfig.addElmt(temp);
    }
  }

  //show list
  listItemConfig.printList();

  ListRecipe listRecipeConfig;
  ItemRecipe Recipe(3,3);
  int in_line =0;
  int in_col = 0;
  int row = 0;
  int col = 0;
  int iwordsrecipe =0;
  // read recipes
  for (const auto &entry :
       filesystem::directory_iterator(configPath + "/recipe")) {
    // cout << entry.path() << endl;
    // read from file and do something
  
    in_line =0;
    row = 0;
    col = 0;
    ifstream itemConfigRecipe(entry.path());
    for (string line; getline(itemConfigRecipe, line);)
    {
      in_col =0;
      while ((pos = line.find(delimiter)) != string::npos)
      {
        wordsrecipe.push_back(line.substr(0, pos));
        line.erase(0, pos + delimiter.length());
      }
      
      wordsrecipe.push_back(line.substr(0, line.size()));
      while (iwordsrecipe < wordsrecipe.size() && in_line == 0)
      {
        row=get_number(wordsrecipe[iwordsrecipe]);
        iwordsrecipe++; 
        col =get_number(wordsrecipe[iwordsrecipe]);
        iwordsrecipe++; 
        Recipe.setRow(row);
        Recipe.setCol(col);
      }
      while (iwordsrecipe < wordsrecipe.size() && in_line != 0 && in_col <col && in_line -1< row)
      {
        Recipe.set_matrix(wordsrecipe[iwordsrecipe], in_line-1, in_col);
        in_col++;
        iwordsrecipe++;
      }
      while(iwordsrecipe<wordsrecipe.size() && in_line != 0 && in_line-1 >= row){
        Recipe.set_item(wordsrecipe[iwordsrecipe]);
        iwordsrecipe++;
        Recipe.set_quantity(get_number(wordsrecipe[iwordsrecipe]));
        iwordsrecipe++;
      }
      in_line++;
    }
    ItemRecipe *Temp = new ItemRecipe(Recipe);
    listRecipeConfig.addRecipe(*Temp);
    //show recipe
    // Recipe.printRecipe();
    // cout << endl;
  }
  listRecipeConfig.printListRecipe();

  // sample interaction
  string command;
  while (cin >> command) {
    if (command == "EXPORT") {
      string outputPath;
      cin >> outputPath;
      ofstream outputFile(outputPath);

      // hardcode for first test case
      outputFile << "21:10" << endl;
      outputFile << "6:1" << endl;
      for (int i = 2; i < 27; i++) {
        outputFile << "0:0" << endl;
      }

      cout << "Exported" << endl;
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
    } else {
      // todo
      cout << "Invalid command" << endl;
    }
  }
  return 0;
}
