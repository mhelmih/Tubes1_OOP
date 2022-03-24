#ifndef CRAFTINGTABLE_HPP
#define CRAFTINGTABLE_HPP

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "configGame.hpp"
#include "Craft.hpp"
#include "Inventory.hpp"
#include "Item.hpp"

using namespace std;

class CraftingTable {
    private:
        Inventory inv;
        Craft crf;
        ListItemConfig listItemConfig;
        ListRecipe listRecipeConfig;

        string command;
        string configPath;
        string itemConfigPath;
        string recipeConfigPath;

        /* ******* CONFIG ******* */

        void readItemConfig(vector<string> &words);
        void readItemRecipe(vector<string> &wordsrecipe);

        /* ******* COMMAND ******* */

        void help();
        void printItemList();

        /**
         * Menampilkan crafting table dan inventory
         * 
         * I.S. : -
         * F.S. : isi slot crafting dan inventory ditampilkan
         * 
         * SHOW
         */
        void show();

        /**
         * Menambahkan Item ke Inventory. Sejumlah Item dengan jenis yang 
         * sama akan ditambahkan ke slot inventory:
         *  - Berisi item nontool dengan jenis yang sama
         *  - Memiliki quantity < 64 (tidak penuh)
         * Apabila tidak ditemukan slot yang memenuhi syarat tersebut, 
         * item ditambahkan pada slot kosong. Penambahan item dilakukan 
         * dari ID inventory terkecil.
         * 
         * I.S. : -
         * F.S. : Item ITEM_NAME pada inventory bertambah sebanyak ITEM_QTY. 
         *        Otomatis masuk pada slot ID inventory sesuai ketentuan di atas.
         * 
         * GIVE <ITEM_NAME> <ITEM_QTY>
         * Contoh: GIVE OAK_WOOD 10
         */
        void give();

        /**
         * Membuang item di slot inventory dengan kuantitas yang diberikan. 
         * Gagal bila kuantitas item lebih kecil dari item yang dijadikan masukan perintah.
         * 
         * I.S. : Kuantitas item lebih besar sama dengan item pada ITEM_QTY.
         * F.S. : Item pada inventory slot INVENTORY_SLOT_ID berkurang sebanyak ITEM_QTY. 
         *        Hapus item pada slot bila item pada INVENTORY_SLOT_ID = 0.
         * 
         * DISCARD <INVENTORY_SLOT_ID> <ITEM_QTY>
         * Contoh: DISCARD I0 32
         */
        void discard();

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
        void moveToCraft(int invIdx, int* crfId, int qty); //ini parameternya gatau harus apa

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
        void movetoStack(int invIdxSrc, int invIdDest);

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
        void moveToInventory(int crfIdx, int invIdx);

        /**
         * Menggunakan Item. Item tool dapat digunakan dan durabilitasnya akan berkurang.
         * 
         * I.S. : INVENTORY_SLOT_ID berisi Item tool.
         * F.S. : Durability Item pada INVENTORY_SLOT_ID berkurang 1. 
         *        Jika durabilitynya mencapai 0, maka item hilang dari inventory.
         * 
         * USE <INVENTORY_SLOT_ID>
         * Contoh: USE I0
         */
        void use();

        /**
         * Craft Item. Jika terdapat resep yang memenuhi, Item bahan akan hilang dan 
         * Item hasil akan muncul. Item akan otomatis ditambahkan ke inventory dengan 
         * algoritma yang sama dengan command GIVE.
         * 
         * I.S. : Slot crafting membentuk pattern sesuai salah satu recipe.
         * F.S. :
         *  1. Seluruh slot crafting kosong
         *  2. Item hasil crafting ditambahkan ke inventory sesuai ketentuan di atas.
         * 
         * CRAFT
         */
        void craft();

        /**
         * Export inventory. Semua item pada inventory akan di export ke file argumen. 
         * Format dari hasil export adalah sebagai berikut:
         *  - Untuk item nontool: <ITEM_ID_0>:<ITEM_QTY_0>
         *  - Untuk item tool: <ITEM_ID_0>:<ITEM_DURA_0>
         *  - Jika tidak ada item pada slot, keluarkan “0:0”. 
         * 
         * I.S. : -
         * F.S. : muncul file dengan nama NAMA_FILE yang berisi pasangan ITEM_ID dengan 
         *        ITEM_QTY / ITEM_DURA untuk setiap slot pada inventory.
         * 
         * EXPORT <NAMA_FILE>
         * EXPORT inventory.txt
         */
        void exportInventory();

        void move();

    public:
        CraftingTable();
        ~CraftingTable();
        void readConfig();
        void readCommand();
};

#endif