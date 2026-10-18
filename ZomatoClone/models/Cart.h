#ifndef CART_H
#define CART_H

#include<iostream>
#include<string>
#include<vector>
#include "MenuItem.h"
#include "Restaurant.h"
using namespace std;

class Cart {
    private:
        Restaurant* restaurant;
        vector<MenuItem> items;
    public:
        Cart(){
            restaurant = nullptr;
        }

        void addItem(const MenuItem& item) {
            if(!restaurant) {
                cerr<<"Select a restaurant before adding items."<<endl;
                return;
            }
            items.push_back(item);
        }

        double getTotalCost() const {
            double total = 0;
            for(const auto& item : items) {
                total += item.getPrice();
            }
            return total;
        }

        bool isEmpty() const {
            return (!restaurant || items.empty());
        }

        void clear(){
            items.clear();
            restaurant = nullptr;
        }

        void setRestaurant(Restaurant* res) {
            if (!items.empty() && res != restaurant) {
                cerr<<"Clear the cart before changing restaurants."<<endl;
                return;
            }
            restaurant = res;
        }

        Restaurant* getRestaurant() const {
            return restaurant;
        }

        vector<MenuItem> getItems() const {
            return items;
        }
};

#endif