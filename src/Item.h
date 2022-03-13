#ifndef _ITEM_H_
#define _ITEM_H_

#include <string>

using namespace std;

class Item{
    private:
        static int id;
        string name;
        string type;
    public:
        Item();
        Item(string name, string type);
        ~Item();
        virtual Item& operator+(const Item& other)=0;
};


class Tool : public Item {
    private:
        int durability;
    public:
        Tool();
        ~Tool();
};


class NonTool : public Item {
    private:
        int quantity;
    public:
        NonTool();
        ~NonTool();
};

#endif
