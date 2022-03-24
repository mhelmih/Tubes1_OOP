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
    this->optRow = 0;
    this->optCol = 0;
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

void Craft::getCurCraft(){
    int k = 0;
    for(int i=0; i<CRAFT_ROW; i++){
        for(int j=0; j<CRAFT_COL; j++){
            if(this->slot[k]!=0){
                this->curCraft[i][j] = slot[k]->get_name();
            }else{
                this->curCraft[i][j] = "-";
            }
            k++;
        }
    }

    //return this->curCraft;
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

// void Craft::setIsMirrored(bool flag){
//     this->isMirrored = flag;
// }

// bool Craft::getIsMirrored(){
//     return this->isMirrored;
// }

bool Craft::emptyRow(int idx){
    //string **craftSlot = getCurCraft();
    getCurCraft();
    int count = 0;
    for(int j=0; j<CRAFT_COL; j++){
        if(this->curCraft[idx][j]=="-"){
            count++;
        }
    }
    if(count==3){
        return true;
    }else{
        return false;
    }
}

bool Craft::emptyCol(int idx){
    //string **craftSlot = getCurCraft();

    int count = 0;
    for(int i=0; i<CRAFT_ROW; i++){
        if(this->curCraft[i][idx]=="-"){
            count++;
        }
    }
    if(count==3){
        return true;
    }else{
        return false;
    }
}

void Craft::swapCol(){
    if(emptyCol(0) && !emptyCol(2)){
        for(int i=0;i<CRAFT_ROW;i++){
            string temp = this->curCraft[i][0];
            this->curCraft[i][0] = this->curCraft[i][2];
            this->curCraft[i][2] = temp;
        }
    }
}

string** Craft::getOptimizedCrft(){
    getCurCraft();
    swapCol();
    if((emptyRow(1) || emptyCol(1)) && (!emptyCol(0) && !emptyCol(2))){
        return curCraft;
    }else{
        int newRow = CRAFT_ROW;
        int newCol = CRAFT_COL;
        for(int i=0;i<3;i++){
            if(emptyRow(i)){
                newRow-=1;
            }
            if(emptyCol(i)){
                newCol-=1;
            }
        }

        string** newCraft = new string*[newRow];
        for(int i=0;i<newRow;i++){
            newCraft[i] = new string[newCol];
        }

        int rIdx = 0;
        int cIdx = 0; 
        bool flag = false;
        for(int i=0;i<CRAFT_ROW;i++){
            cIdx = 0; 
            for(int j=0;j<CRAFT_COL;j++){
                if(curCraft[i][j]!="-"){
                    newCraft[rIdx][cIdx] = this->curCraft[i][j];
                    cIdx++;
                    flag=true;
                }
            }
            if(flag && rIdx < newRow){
                rIdx++;
            }
        }
        this->optRow = newRow;
        this->optCol = newCol;

        return newCraft;
    }
}

bool Craft::isRecipe(ItemRecipe ls){
    string** optCraft = getOptimizedCrft();
    bool flag = false;
    int row = ls.getRow();
    int col = ls.getCol();

    if((this->optRow != row) && (this->optCol != col)){
        return false;
    }else{
        int i=0;
        int j=0;
        int count = 0;
        while(!flag && i<row){
            while(!flag && i<col){
                if(optCraft[i][j]!=ls.getElement(i,j)){
                    flag=true;
                }
                else{
                    count++;
                }
                j++;
            }
            i++;
        }

        if(count == (row+col)){
            return true;
        }else{
            return false;
        }
    }
    
}