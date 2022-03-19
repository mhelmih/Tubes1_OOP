#include "Craft.hpp"

void Craft::readItemRecipe(vector<string> &wordsrecipe, ListRecipe &listRecipeConfig)
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

Craft::Craft(){
    
    // Keperluan read
    size_t pos;
    string delimiter = " ";
    string configPath = "../config";
    vector<string> wordsrecipe{};
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
    readItemRecipe(wordsrecipe, this->listRecipeConfig);
    wordsrecipe.clear();
  }
}

Craft::~Craft(){
    // delete[] this->slot;
}

bool Craft::isRecipe(){
    return true;
}

void Craft::show(){
    this->listRecipeConfig.printListRecipe();
}

void Craft::showRecipe(){
    cout << this->listRecipeConfig[3].getElement(0,0);
}