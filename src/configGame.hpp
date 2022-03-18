#ifndef CONFIGGAME_HPP
#define CONFIGGAME_HPP
#define MAX_LIST_CONFIG 100

#include <iostream>
#include <string>

using namespace std;

class ItemConfig
{
private:
    int id;
    string name;
    string type;
    string category;
public:
    ItemConfig();
    ItemConfig(int id, string name, string type, string category);
    void print();
    void set_id(int id);
    int get_id();
    void set_name(string name);
    string get_name();
    void set_type(string type);
    string get_type();
    void set_category(string category);
    string get_category();
};

class ItemRecipe
{
private:
    int row;
    int col;
    string **matrix;
    string itemCraft;
    int quantity;

public:
    ItemRecipe();
    ItemRecipe(int row, int col);
    ItemRecipe(const ItemRecipe& recipe);
    ~ItemRecipe();
    void setRow(int row);
    int getRow();
    void setCol(int col);
    int getCol();
    void new_matrix(int row,int col);
    void set_matrix(string line, int row,int col);
    string getElement(int row, int col);
    void set_quantity(int quantity);
    int get_quantity();
    void set_item(string itemCraft );
    string get_item();
    void printRecipe();
};

class ListItemConfig
{
private:
    ItemConfig *listconfig;
    int Neff;
public:
    ListItemConfig();
    ListItemConfig(int capacity);
    ~ListItemConfig();
    void addElmt(ItemConfig elemen);
    void printList();
    ItemConfig operator[](int index);
};

class ListRecipe
{
private:
    ItemRecipe *listRecipe;
    int Neff;
public:
    ListRecipe();
    ListRecipe(int capacity);
    ~ListRecipe();
    void addRecipe(const ItemRecipe &elemen);
    void printListRecipe();
    ItemRecipe operator[](int index);
};

int get_number(string number_string);
#endif