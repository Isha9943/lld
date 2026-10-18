#ifndef USER_H
#define USER_H

#include<iostream>
#include<string>
#include "Cart.h"
using namespace std;

class User {
    private:
        int userId;
        string name;
        string address;
        Cart* cart;

    public:
        User(int userId, const string& name, const string& address) {
            this->userId = userId;
            this->name = name;
            this->address = address;
            this->cart = new Cart();
        }

        ~User() {
            delete cart;
        }

        User(const User&) = delete;
        User& operator=(const User&) = delete;

        int getUserId() const {
            return userId;
        }

        string getName() const {
            return name;
        }

        void setName(const string& name) {
            this->name = name;
        }

        string getAddress() const {
            return address;
        }

        void setAddress(const string& address) {
            this->address = address;
        }

        Cart* getCart() const{
            return cart;
        }   
};

#endif