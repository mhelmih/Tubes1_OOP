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
            this->optCraft[i][j] = "-";
        }
    }

    this->optRow = 0;
    this->optCol = 0;

    this->namedBased = false;
    
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
    // harus ditambahin exception kalo lebih dari 27
    return slot[idx];
}

void Craft::updateCurCraft(){
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

bool Craft::emptyRow(int idx){
    updateCurCraft();
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

void Craft::updateOptimizedCrft(){
    updateCurCraft();
    
    swapCol();

    // for(int i=0;i<3;i++){
    //     for(int j=0; j<3;j++){
    //         cout << this->curCraft[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    if((emptyRow(1) || emptyCol(1)) && (!emptyCol(0) && !emptyCol(2))){
        this->optCraft = this->curCraft;
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

        if(newRow == 0 && newCol==0){
            this->optCraft= new string*[CRAFT_ROW];
            for(int i =0;i<CRAFT_ROW; i++){
                this->optCraft[i] = new string[CRAFT_COL];
            }

            for(int i=0; i<CRAFT_ROW; i++){
                for(int j =0;j<CRAFT_COL;j++){
                    this->optCraft[i][j] = "-";
                }
            }
        }else{
            this->optCraft= new string*[newRow];
            for(int i =0;i<newRow; i++){
                this->optCraft[i] = new string[newCol];
            }
            int rIdx = 0;
            int cIdx = 0; 
            bool flag = false;
            for(int i=0;i<CRAFT_ROW;i++){
                cIdx = 0; 
                for(int j=0;j<CRAFT_COL;j++){
                    if(curCraft[i][j]!="-"){
                        this->optCraft[rIdx][cIdx] = this->curCraft[i][j];
                        cIdx++;
                        flag=true;
                    }
                }
                if(flag && rIdx < newRow){
                    rIdx++;
                }
            }
            
            
            //return newCraft;
        }
        this->optRow = newRow;
        this->optCol = newCol;
    }
}

bool Craft::isRecipe(ItemRecipe ls){
    updateOptimizedCrft();
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
            while(!flag && j<col){
                if(this->optCraft[i][j]!=ls.getElement(i,j)){
                    flag=true;
                }
                else{
                    count++;
                }
                j++;
            }
            i++;
        }

        if(count == (row*col)){
            return true;
        }else{
            return false;
        }
    }
    
}