#ifndef RESTAURANT_H
#define RESTAURANT_H

#include<iostream>
#include<vector>
#include<string>
#include "MenuItem.h"
using namespace std;


class Restaurant {
    private:
        inline static int nextRestaurantId = 0;
        int restaurantId;
        string name;
        string location;
        vector<MenuItem> menu;

    public:
        Restaurant(const string &name, const string &location) {
            this->restaurantId = ++nextRestaurantId;
            this->name = name;
            this->location = location;
        }

        ~Restaurant() {
            cout<<"Destroying Restaurant and clearing its menu: "<<name<<endl;
        }

        int getRestaurantId() const {
            return restaurantId;
        }

        string getName() const {
            return name;
        }

        string getLocation() const {
            return location;
        }

        vector<MenuItem> getMenu() const {
            return menu;
        }

        void setName(const string &name) {
            this->name = name;
        }

        void setLocation(const string &location) {
            this->location = location;
        }

        void addMenuItem(MenuItem item) {
            menu.push_back(item);
        }
};

#endif // RESTAURANT_H