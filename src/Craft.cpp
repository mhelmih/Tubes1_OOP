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
    this->toolInSlot = 0;
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
    return slot[idx];
}

void Craft::updateCurCraft(){
    int k = 0;
    for(int i=0; i<CRAFT_ROW; i++){
        for(int j=0; j<CRAFT_COL; j++){
            if(this->slot[k]!=0){
                if(namedBased){
                    this->curCraft[i][j] = slot[k]->get_name();
                }else{
                    this->curCraft[i][j] = slot[k]->get_type();
                    if(slot[k]->get_type()=="-"){
                        this->curCraft[i][j] = slot[k]->get_name();
                    }
                }
                
            }else{
                this->curCraft[i][j] = "-";
            }
            k++;
        }
    }
    this->optCraft = curCraft;

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
    cout << "masuk craft" << endl;
    updateCurCraft();
    cout << "masuk0" << endl;
    swapCol();
    cout << "masuk 1" << endl;
    int newRow = CRAFT_ROW;
    int newCol = CRAFT_COL;
    
    cout << "masuk2" << endl;
    if ((emptyRow(1) || emptyCol(1)) && ((!emptyCol(0) && !emptyCol(2)) || (!emptyRow(0) && !emptyRow(2)))){
        this->optCraft = this->curCraft;
    } else {
        cout << "masuk4" << endl;
        for(int x = 0; x < CRAFT_ROW; x++) {
            if(emptyRow(x)){
                newRow-=1;
            }
            if(emptyCol(x)){
                newCol-=1;
            }
        }
        cout << "masuk5" << endl;
        //bool flag = false;
        this->optCraft= new string*[newRow];
        cout << "masuk6" << endl;
        for(int i =0;i<this->optRow; i++){
            this->optCraft[i] = new string[newCol];
        }
        cout << "masuk7" << endl;
        int rIdx =0;
        int cIdx = 0;

        // assign nilai aslinya
        for(int i = 0; i < CRAFT_ROW; i++) {
            cIdx = 0;
            cout << "masuk for 1" << endl;
            for(int j = 0; j < CRAFT_COL; j++){
                cout << "r/c " << rIdx << " " << cIdx << endl;
                if(!emptyRow(i) && !emptyCol(j)) {
                    cout << "masuk for 2" << endl;
                    this->optCraft[rIdx][cIdx] = this->curCraft[i][j];
                    //flag = true;
                    cIdx++;
                }
                cout << "tes" << endl;
            }
            if(!emptyRow(i)){
                rIdx++;
            }
        }
        
    }
    this->optRow = newRow;
    this->optCol = newCol;
}

bool Craft::isRecipe(ItemRecipe ls, bool isName){
    this->namedBased=isName;
    updateOptimizedCrft();

    cout << optRow << optCol << endl;
    for(int i = 0; i < optRow; i++){
        for(int j = 0; j < optCol; j++){
            cout << this->optCraft[i][j] << " ";
        }
        cout << endl;
    }

    bool flag = false;
    int row = ls.getRow();
    int col = ls.getCol();

    if ((this->optRow != row) && (this->optCol != col)) {
        return false;
    } else {
        int i = 0;
        int j = 0;
        int count = 0;
        while(!flag && i < row){
            int j = 0;
            while(!flag && j < col){
                if(this->optCraft[i][j] != ls.getElement(i,j)){
                    flag=true;
                }
                else{
                    count++;
                }
                j++;
            }
            i++;
        }

        if (count == (row * col)){
            return true;
        } else {
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