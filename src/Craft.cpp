#include "Craft.hpp"

Craft::Craft(){
    slot.assign(9, 0);
    this->curCraft = new string*[CRAFT_ROW];
    for(int i =0;i<CRAFT_ROW; i++){
        this->curCraft[i] = new string[CRAFT_COL];
    }

    this->optCraft= new string*[CRAFT_ROW];
    for(int i =0;i<CRAFT_ROW; i++){
        this->optCraft[i] = new string[CRAFT_COL];
    }

    for(int i=0; i<CRAFT_ROW; i++){
        for(int j =0;j<CRAFT_COL;j++){
            this->curCraft[i][j] = "-";
        }
    }

    for(int i=0; i<CRAFT_ROW; i++){
        for(int j =0;j<CRAFT_COL;j++){
            this->optCraft[i][j] = this->curCraft[i][j];
        }
    }

    this->optRow = 3;
    this->optCol = 3;
    this->namedBased = false;
    this->isMirrored = false;
    
}

Craft::~Craft(){
    for (Item* item : this->slot) {
        delete[] item;
    }
    delete[] this->curCraft;
    delete[] this->optCraft;
    this->slot.clear();
}

Item* &Craft::operator[](int idx) {
    return slot[idx];
}

void Craft::updateCurCraft() {
    int k = 0;
    for (int i = 0; i < CRAFT_ROW; i++){
        for (int j = 0; j < CRAFT_COL; j++){
            if (!(this->slot[k] == 0)) {
                if (this->namedBased) {
                    this->curCraft[i][j] = slot[k]->get_name();
                } else{
                    this->curCraft[i][j] = slot[k]->get_type();
                    if (slot[k]->get_type() == "-") {
                        this->curCraft[i][j] = slot[k]->get_name();
                    }
                }
            } else {
                this->curCraft[i][j] = "-";
            }
            k++;
        }
    }
    this->optCraft = curCraft;
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
    updateCurCraft();
}

bool Craft::emptyRow(int idx){
    int count = 0;
    for(int j=0; j<CRAFT_COL; j++){
        if(this->curCraft[idx][j]=="-"){
            count++;
        }
    }
    if(count==CRAFT_ROW){
        return true;
    }else{
        return false;
    }
}

bool Craft::emptyCol(int idx){
    int count = 0;
    for(int i=0; i<CRAFT_ROW; i++){
        if(this->curCraft[i][idx]=="-"){
            count++;
        }
    }
    if(count==CRAFT_COL){
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

void Craft::updateOptimizedCrft(){
    updateCurCraft();

    if(this->isMirrored){
        swapCol();
    }
    int newRow = CRAFT_ROW;
    int newCol = CRAFT_COL;
    
    if ((emptyRow(1) && (!emptyRow(0) && (!emptyRow(2)))) || (emptyCol(1) && (!emptyCol(0) && (!emptyCol(2))))){
        
        this->optCraft = this->curCraft;
    } else {
        for(int x = 0; x < 3; x++) {
            if(emptyRow(x)){
                newRow--;
            }
            if(emptyCol(x)){
                newCol--;
                cout << "masuk";
            }
        }
        this->optCraft= new string*[newRow];
        for(int i =0;i<this->optRow; i++){
            this->optCraft[i] = new string[newCol];
        }
        int rIdx =0;
        int cIdx = 0;

        // assign nilai aslinya
        for(int i = 0; i < CRAFT_ROW; i++) {
            cIdx = 0;
            for(int j = 0; j < CRAFT_COL; j++){
                if(!emptyRow(i) && !emptyCol(j)) {
                    this->optCraft[rIdx][cIdx] = this->curCraft[i][j];
                    //flag = true;
                    if(cIdx < newCol) {
                        cIdx++;
                    }
                }
            }
            if(!emptyRow(i) && rIdx < newRow) {
                rIdx++;
            }
        }
        
    }
    this->optRow = newRow;
    this->optCol = newCol;
}

bool Craft::isRecipe(ItemRecipe ls, bool isName){
    this->namedBased = isName;
    updateOptimizedCrft();
    int row = ls.getRow();
    int col = ls.getCol();

    if (!(this->optRow == row && this->optCol == col)) {
        return false;
    } else {
        int i = 0;
        int j = 0;
        int count = 0;
        bool flag = false;
        
        while (!flag && i < optRow) {
            int j = 0;
            while(!flag && j < optCol){
                if(this->optCraft[i][j] != ls.getElement(i,j)){
                    flag=true;
                }
                else{
                    count++;
                    j++;
                }
            }
            i++;
        }

        if (count == (row * col)){
            return true;
        } else if (flag && !isMirrored){
            this->isMirrored = true;
            bool temp = isRecipe(ls,isName);
            this->isMirrored = false;
            return temp;
        }
        else{
            return false;
        }
    }
    
}

vector<int> Craft::idxSlotTool(){
    vector<int> idx;
    for(int i = 0; i < 9; i++) {
        if (this->slot[i]->isA<Tool>()) {
            idx.push_back(i);
        }
    }

    return idx;
}