#ifndef ITEM_HPP
#define ITEM_HPP
#include <iostream>
#include <string>

using namespace std;

class Item {
    protected:
        int id;
        string name;
        string type;
    public:
        Item();
        Item(int id, string name, string type);
        Item(const Item& other);
        Item& operator=(const Item& other);
        ~Item();
        int get_id() const;
        string get_name() const;
        string get_type() const;
        virtual void printInfo()=0;
        virtual string printExport()=0;
        // virtual int get_quantity();
        template<typename T>
        bool isA(){
            return (dynamic_cast<T*>(this) != NULL);
        }
};


class Tool : public Item {
    private:
        int durability;
    public:
        Tool();
        Tool(int id, string name, string type);
        Tool(const Tool& other);
        Tool& operator=(const Tool& other);
        ~Tool();
        int get_durability() const;
        void set_durability(int durability);
        void use();
        Tool& operator+(const Tool& other);
        void printInfo();
        string printExport();
};


class NonTool : public Item {
    private:
        int quantity;
    public:
        NonTool();
        NonTool(int id, string name, string type, int quantity);
        NonTool(const NonTool& other);
        NonTool& operator=(const NonTool& other);
        ~NonTool();
        int get_quantity();
        void set_quantity(int quantity);
        NonTool& operator+(const NonTool& other);
        void printInfo();
        string printExport();
};

#endif
