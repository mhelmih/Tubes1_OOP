#include <iostream>
#include "configGame.hpp"
#include <sstream>

ItemConfig::ItemConfig()
{
    this->id = 0;
    this->name = "name";
    this->type = "-";
    this->category = "tool/nontool";
}
ItemConfig::ItemConfig(int id, string name, string type, string category)
{
    this->id = id;
    this->name = name;
    this->type = type;
    this->category = category;
}


void ItemConfig::print()
{
    cout << "id      : " << this->id << endl;
    cout << "name    : " << this->name << endl;
    cout << "type    : " << this->type << endl;
    cout << "category: " << this->category << endl;
}

void ItemConfig::set_id(int id)
{
    this->id = id;
}
int ItemConfig::get_id()
{
    return this->id;
}
void ItemConfig::set_name(string name)
{
    this->name = name;
}
string ItemConfig::get_name()
{
    return this->name;
}
void ItemConfig::set_type(string type)
{
    this->type = type;
}
string ItemConfig::get_type()
{
    return this->type;
}
void ItemConfig::set_category(string category)
{
    this->category = category;
}
string ItemConfig::get_category()
{
    return this->category;
}

ItemRecipe::ItemRecipe()
{
    this->matrix = new string*[3];
    this->row =3;
    this->col =3;
    this->itemCraft = "none";
    this->quantity =0;
    for (int i=0; i<row;i++){
        this->matrix[i] = new string[3];
    }
    for(int i=0; i<col;i++){
        for(int j=0; j<col;j++){
            this->matrix[i][j] ="-";
        }
    }
}
ItemRecipe::ItemRecipe(int row, int col)
{
    this->row =row;
    this->col =col;
    this->itemCraft = "-";
    this->quantity =0;
    this->matrix = new string*[row];
    for (int i=0; i<row;i++){
        matrix[i] = new string[col];
    }
    for(int i=0; i<col;i++){
        for(int j=0; j<col;j++){
            this->matrix[i][j] ="-";
        }
    }
}


ItemRecipe::ItemRecipe(ItemRecipe& recipe)
{
    this->row =recipe.row;
    this->col =recipe.col;
    this->itemCraft = recipe.itemCraft;
    this->quantity = recipe.quantity;
    this->matrix = new string*[recipe.row];
    for (int i=0; i<recipe.row;i++){
        this->matrix[i] = new string[recipe.col];
    }
    for (int i=0; i<recipe.row;i++){
        for (int j=0; j<recipe.col;j++){
            this->matrix[i][j] = recipe.matrix[i][j];
        }
    }
    // this->printRecipe();
}
ItemRecipe::~ItemRecipe()
{
    for (int i=0; i<row;i++){
        delete[] this->matrix[i];
    }
    delete[] this->matrix;

}

void ItemRecipe::new_matrix(int row, int col){
    for (int i=0; i<row;i++){
        delete[] this->matrix[i];
    }
    delete[] this->matrix;
    this->row =row;
    this->col =col;
    this->itemCraft = "-";
    this->matrix = new string*[row];
    for (int i=0; i<row;i++){
        matrix[i] = new string[col];
    }
}
void ItemRecipe::set_matrix(string line, int row, int col){
    this->matrix[row][col] = line;
}

void ItemRecipe::setRow(int row){
    this->row = row;
}
void ItemRecipe::setCol(int col){
    this->col =col;
}

void ItemRecipe::set_quantity(int quantity){
    this->quantity = quantity;
}

void ItemRecipe::set_item(string itemCraft){
    this->itemCraft =itemCraft;
}

void ItemRecipe::printRecipe()
{
    cout << "row     : " << this->row << endl;
    cout << "col     : " << this->col << endl;
    cout << "matrix  : " <<endl;
    for (int i =0;i<this->row;i++){
        for (int j =0;j<this->col;j++){
            cout << this->matrix[i][j] << " "; 
        }
        cout << endl;
    }
    cout << "item    : " << this->itemCraft << endl;
    cout << "quantity: " << this->quantity<< endl;
}


ListItemConfig::ListItemConfig(){
    this->listconfig = new ItemConfig[MAX_LIST_CONFIG];
    this->Neff = 0;
}
ListItemConfig::ListItemConfig(int capacity){
    this->listconfig = new ItemConfig[capacity];
    this->Neff = 0;
}

ListItemConfig::~ListItemConfig(){
    delete[] this->listconfig;
}
void ListItemConfig::addElmt(ItemConfig elemen) {
    if (this->Neff == MAX_LIST_CONFIG) {
        throw "Queue is full";
    } else {
        this->listconfig[this->Neff] = elemen;
    }
    this->Neff++;
}

void ListItemConfig::printList(){
    for (int i =0;i<this->Neff;i++){
        this->listconfig[i].print();
    }
}


int get_number(string number_string){
    int number;
    stringstream geek(number_string);
    geek >> number;
    return number;
}