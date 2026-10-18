#ifndef MENUITEM_H
#define MENUITEM_H

#include<iostream>
#include<string>
using namespace std;

class MenuItem {
    private:
        string code;
        string name;
        double price;

    public:
        MenuItem(const string &code, const string &name, double price) {
            this->code = code;
            this->name = name;
            this->price = price;
        }

        string getCode() const {
            return code;
        }

        string getName() const {
            return name;
        }

        double getPrice() const {
            return price;
        }

        void setName(const string &name) {
            this->name = name;
        }

        void setPrice(double price) {
            this->price = price;
        }
};

#endif // MENUITEM_H