// sample main file, replace this with your own code
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "src/configGame.cpp"
#include "src/item.cpp"
using namespace std;

void readItemConfig(vector<string> &words, ListItemConfig &listItemConfig)
{
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
  listItemConfig.addElmt(temp);
}

void readItemRecipe(vector<string> &wordsrecipe, ListRecipe &listRecipeConfig)
{
  int iwordsrecipe = 0;
  int row, col;
  row = get_number(wordsrecipe[iwordsrecipe]);
  iwordsrecipe++;
  col = get_number(wordsrecipe[iwordsrecipe]);
  iwordsrecipe++;

  ItemRecipe *temp = new ItemRecipe(row, col);
  
  // read matrix
  for (int i =0;i<row;i++){
    for (int j =0;j<col;j++){
      temp->set_matrix(wordsrecipe[iwordsrecipe], i, j);
      iwordsrecipe++;
    }
  }

  temp->set_item(wordsrecipe[iwordsrecipe]);
  iwordsrecipe++;
  temp->set_quantity(get_number(wordsrecipe[iwordsrecipe]));
  iwordsrecipe++;

  listRecipeConfig.addRecipe(*temp);
}

int main()
{
  string configPath = "./config";
  string itemConfigPath = configPath + "/item.txt";

  // menampung line yang sudah displit
  vector<string> words{};
  vector<string> wordsrecipe{};
  size_t pos;
  string delimiter = " ";

  // list itemconfig
  ListItemConfig listItemConfig;
  // list recipe
  ListRecipe listRecipeConfig;

  // read item from config file
  ifstream itemConfigFile(itemConfigPath);
  for (string line; getline(itemConfigFile, line);)
  {
    // cout << line << endl;
    // split line
    while ((pos = line.find(delimiter)) != string::npos)
    {
      words.push_back(line.substr(0, pos));
      line.erase(0, pos + delimiter.length());
    }
    words.push_back(line.substr(0, line.size()));

    // read item
    readItemConfig(words, listItemConfig);
    words.clear();
  }

  // show list
  listItemConfig.printList();

  // read recipes
  for (const auto &entry :
       filesystem::directory_iterator(configPath + "/recipe"))
  {
    // cout << entry.path() << endl;
    // read from file and do something

    ifstream itemConfigRecipe(entry.path());

    // split line setiap file config
    for (string line; getline(itemConfigRecipe, line);)
    {
      while ((pos = line.find(delimiter)) != string::npos)
      {
        wordsrecipe.push_back(line.substr(0, pos));
        line.erase(0, pos + delimiter.length());
      }
      wordsrecipe.push_back(line.substr(0, line.size()));
    }

    // read recipe
    readItemRecipe(wordsrecipe, listRecipeConfig);
    wordsrecipe.clear();
  }
  listRecipeConfig.printListRecipe();

  // sample interaction
  string command;
  while (cin >> command)
  {
    if (command == "EXPORT")
    {
      string outputPath;
      cin >> outputPath;
      ofstream outputFile(outputPath);

      // hardcode for first test case
      outputFile << "6:1" << endl;
      for (int i = 2; i < 24; i++)
      {
        outputFile << "0:0" << endl;
      }

      cout << "Exported" << endl;
    }
    else if (command == "CRAFT")
    {
      cout << "TODO" << endl;
    }
    else if (command == "GIVE")
    {
      string itemName;
      int itemQty;
      cin >> itemName >> itemQty;
      cout << "TODO" << endl;
    }
    else if (command == "MOVE")
    {
      string slotSrc;
      int slotQty;
      string slotDest;
      // need to handle multiple destinations
      cin >> slotSrc >> slotQty >> slotDest;
      cout << "TODO" << endl;
    }
    else
    {
      // todo
      cout << "Invalid command" << endl;
    }
  }
  return 0;
}
