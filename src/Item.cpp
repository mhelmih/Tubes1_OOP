#include "Item.hpp"

//Class Item
Item::Item() {
    this->id = -1;
    this->name = "-";
    this->type = "-";
}

Item::Item(int id, string name, string type) {
    this->id = id;
    this->name = name;
    this->type = type;
}

Item::Item(const Item& other) {
    this->id = other.id;
    this->name = other.name;
    this->type = other.type;
}

Item& Item::operator=(const Item& other) {
    // Masih error
    this->id = other.id;
    this->name = other.name;
    this->type = other.type;

    return *this;
}

Item::~Item() {
    
}

int Item::get_id() const {
    return this->id;
}

string Item::get_name() const {
    return this->name;
}

string Item::get_type() const {
    return this->type;
}





// Class Tool
Tool::Tool() : Item() {
    this->durability = -1;
}

Tool::Tool(int id,string name, string type) : Item(id,name, type) {
    this->durability = 10;
}

Tool::Tool(const Tool& other) : Item(other.id,other.name,other.type){
    this->durability = other.durability;
}

Tool& Tool::operator=(const Tool& other) {
    this->id = other.id;
    this->name = other.name;
    this->type = other.type;
    this->durability = other.durability;
    
    return *this;
}

Tool::~Tool() {

}

int Tool::get_durability() const {
    return this->durability;
}

void Tool::set_durability(int durability) {
    this->durability = durability;
}

void Tool::use() {
    this->durability -= 1;
}

Tool& Tool::operator+(const Tool& other) {
    Tool *temp = new Tool(*this);
    temp->durability = this->durability + other.durability;
    if (temp->durability > 10) temp->durability = 10;

    return *temp;
}



// class NonTool
NonTool::NonTool() : Item() {
    this->quantity = -1;
}

NonTool::NonTool(int id,string name, string type, int quantity) : Item(id,name, type) {
    this->quantity = quantity;
}

NonTool::NonTool(const NonTool& other) : Item(other.id, other.name,other.type) {
    this->quantity = other.quantity;
}

NonTool::~NonTool(){
    
}

NonTool& NonTool::operator=(const NonTool& other) {
    this->id = other.id;
    this->name = other.name;
    this->type = other.type;
    this->quantity = other.quantity;

    return *this;
}

int NonTool::get_quantity() {
    return this->quantity;
}

void NonTool::set_quantity(int quantity) {
    this->quantity = quantity;
}

NonTool& NonTool::operator+(const NonTool& other) {
    NonTool *temp = new NonTool(*this);
    temp->quantity = this->quantity + other.quantity;

    return *temp;
}