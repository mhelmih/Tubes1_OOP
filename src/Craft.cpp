#include "Craft.hpp"

Craft::Craft(){
    
    slot.assign(9, 0);
    this->curCraft = new string*[CRAFT_ROW];
    for(int i =0;i<CRAFT_ROW; i++){
        this->curCraft[i] = new string[CRAFT_COL];
    }

    for(int i=0; i<CRAFT_ROW; i++){
        for(int j =0;j<CRAFT_COL;j++){
            this->curCraft[i][j] = "-";
        }
        
    }
    this->isMirrored = false;
}

Craft::~Craft(){
    for (Item* item : this->slot) {
        delete[] item;
    }
    this->slot.clear();
}

Item* &Craft::operator[](int idx) {
    // harus ditambahin exception kalo lebih dari 27
    return slot[idx];
}

string** Craft::getCurCraft(){
    for(int i=0; i<CRAFT_ROW; i++){
        for(int j=0; j>CRAFT_COL; j++){
            if(this->slot[i]!=0){
                this->curCraft[i][j] = slot[i]->get_name();
            }else{
                this->curCraft[i][j] = "-";
            }
        }
    }

    return this->curCraft;
}

bool Craft::isFull(){
    int count = 0;
    for(int i=0; i<9; i++){
        if(this->slot[i]!=0){
            count++;
        }
    }
    if(count==9){
        return true;
    }else{
        return false;
    }
}

void Craft::emptyingCraft(){
    for(int i=0; i<9; i++){
        this->slot[i] = 0;
    }
}

void Craft::setIsMirrored(bool flag){
    this->isMirrored = flag;
}

bool Craft::getIsMirrored(){
    return this->isMirrored;
}