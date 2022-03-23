#include "CraftingTable.hpp"
#include <iostream>

using namespace std;

/**
 * Memindahkan Item ke slot crafting. Satu jenis item dapat dipindahkan ke beberapa 
 * slot crafting. Jumlah item harus lebih besar atau sama dengan jumlah slot crafting.
 * 
 * I.S. : Jumlah Item pada INVENTORY_SLOT_ID sebanyak Qty, dengan Qty >= N (jumlah slot crafting).
 * F.S. : Jumlah Item pada INVENTORY_SLOT_ID sebanyak Qty - N.
 *        CRAFTING_SLOT_ID_1 hingga N berisi Item yang sama dengan INVENTORY_SLOT_ID 
 *        dengan jumlah masing-masing 1.
 * 
 * MOVE <INVENTORY_SLOT_ID> N <CRAFTING_SLOT_ID_1> ... <CRAFTING SLOT_ID_N>
 * Contoh: MOVE I0 N C0 C1 C2 ... CN
 */
void CraftingTable::moveToCraft(int invIdx, int crfIdx){ //ini parameternya gatau harus apa
    string tipeInv = this->inv[invIdx]->get_type();
    if (this->crf[crfIdx] == 0) {
        this->crf[crfidx] = this->inv[invIdx];
        if(this->inv[invIdx]->get_type() == "Tool"){
            this->inv[invIdx] = 0);
        } else if (this->inv[invIdx]->get_type() == "NonTool"){
            NonTool* nt = dynamic_cast<NonTool*>(this->inv[invIdx]);
            nt->set_quantity(nt->get_quantity() - 1);
        }
    } else {
        //sudah terisi
        cout << "slot crafting sudah terisi" << endl;
    }

}
/**
 * Menumpuk Item. Dua buah item non tool yang sama pada inventory dapat ditumpuk.
 * 
 * I.S. :
 *  1. Jumlah Item pada INVENTORY_SLOT_ID_SRC sebanyak Qty1.
 *  2. Jumlah Item pada INVENTORY_SLOT_ID_DEST sebanyak Qty2.
 * F.S. :
 *  1. Jumlah Item pada INVENTORY_SLOT_ID_SRC sebanyak 0 (item hilang / habis), jika memungkinkan.
 *  2. Jumlah Item pada INVENTORY_SLOT_ID_DEST sebanyak Qty1 + Qty2, namun maksimal sebanyak 64.
 * 
 * MOVE <INVENTORY_SLOT_ID_SRC> 1 <INVENTORY_SLOT_ID_DEST>
 * Contoh: MOVE I0 1 I1
 */
void CraftingTable::movetoStack(int invIdxSrc, int invIdDest){
    string tipeSrc = this->inv[invIdxSrc]->get_type();
    string tipeDest = this->inv[invIdxDest]->get_type();
    if (tipeSrc == "NonTool" && tipeDest == "NonTool") {
        NonTool* ntSrc = dynamic_cast<NonTool*>(this->inv[invIdxSrc]);
        NonTool* ntDest = dynamic_cast<NonTool*>(this->inv[invIdxDest]);
        if (ntSrc->get_name() == ntDest->get_name()) {
            if (ntSrc->get_quantity() + ntDest->get_quantity() <= 64) {
                ntDest->set_quantity(ntSrc->get_quantity() + ntDest->get_quantity());
                this->inv[invIdxSrc] = 0;
            }
            else {
                ntDest->set_quantity(64);
                ntSrc->set_quantity(ntSrc->get_quantity() - (64 - ntDest->get_quantity()));
            }
        } else {
            cout << "invalid move" << endl;
        }
    } else {
        cout << "invalid move" << endl;
    }
}

/**
 * Mengembalikan Item dari slot crafting ke inventory.
 * 
 * I.S. :
 *  1. CRAFTING_SLOT_ID tidak kosong.
 *  2. INVENTORY_SLOT_ID kosong / berisi item dengan jenis yang sama dan tidak penuh.
 * F.S. : 
 *  1. CRAFTING_SLOT_ID kosong.
 *  2. Jumlah Item pada INVENTORY_SLOT_ID bertambah 1.
 * 
 * MOVE <CRAFTING_SLOT_ID> 1 <INVENTORY_SLOT_ID>
 * Contoh: MOVE C0 1 I0
 */
void CraftingTable::moveToInventory(int crfIdx, int invIdx){
    string tipeCraft = this->crf[crfIdx]->get_type();
    string tipeInv = this->inv[invIdx]->get_type();
    if (this->inv[invIdx] == 0) {
        this->inv[invIdx] = this->crf[crfIdx];
        this->crf[crfIdx] = 0;
    } else if (this->crf[crfIdx] == 0) {
        //slot crafting kosong
        cout << "Crafting kosong" << endl;
    } else if (tipeCraft == "NonTool" && tipeInv == "NonTool") {
        if (this->crf[crfIdx].get_name() == this->inv[invIdx]->get_name()) {
            NonTool* ntCraft = dynamic_cast<NonTool*>(this->crf[crfIdx]);
            NonTool* ntInv = dynamic_cast<NonTool*>(this->inv[invIdx]);
            if (ntInv->get_quantity() <= 64-1) {
                ntInv->set_quantity(1 + ntInv->get_quantity());
                this->crf[crfIdx] = 0;
            }
            else {
                //full
                cout << "Inventory Full" << endl;
            }
        } else {
            //inventory ada isinya
            cout << "Inventory sudah terisi" << endl;
        }
    } else {
        //crafting ada isinya
        cout << "Inventory sudah terisi" << endl;
    }
}

