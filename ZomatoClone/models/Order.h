#ifndef ORDER_H
#define ORDER_H

#include<iostream>
#include<string>
#include<vector>
#include "MenuItem.h"
#include "Restaurant.h"
#include "User.h"
#include "../strategies/PaymentStrategy.h"
using namespace std;

class Order {
    protected:
        inline static int nextOrderId = 0;
        int orderId;
        User* user;
        Restaurant* restaurant;
        vector<MenuItem> items;
        Cart* cart;
        PaymentStrategy* paymentStrategy;
        double total;
        string scheduled;

    public:
        Order() {
            orderId = ++nextOrderId;
            user = nullptr;
            restaurant = nullptr;
            cart = nullptr;
            paymentStrategy = nullptr;
            total = 0.0;
            scheduled = "";
        }

        virtual ~Order() {
            delete paymentStrategy;
        }

        Order(const Order&) = delete;
        Order& operator=(const Order&) = delete;

        bool processPayment() {
            if(paymentStrategy) {
                paymentStrategy->pay(total);
                return true;
            }
            cerr << "No payment strategy set." << endl;
            return false;
        }

        virtual string getType() const = 0;

        int getOrderId() const {
            return orderId;
        }

        void setUser(User* u) {
            user = u;
        }

        void setRestaurant(Restaurant* r) {
            restaurant = r;
        }

        Restaurant* getRestaurant() const {
            return restaurant;
        }

        void setItems(const vector<MenuItem>& its) {
            items = its;
            total = 0.0;
            for(const auto& item : items) {
                total += item.getPrice();
            }
        }

        vector<MenuItem> getItems() const {
            return items;
        }

        void setPaymentStrategy(PaymentStrategy* ps) {
            // The order owns its payment strategy; user, restaurant, and cart are borrowed.
            if (paymentStrategy != ps) {
                delete paymentStrategy;
                paymentStrategy = ps;
            }
        }

        User* getUser() const {
            return user;
        }

        double getTotal() const {
            return total;
        }
        
        void setCart(Cart* c) {
            cart = c;
        }
        Cart* getCart() const {
            return cart;
        }

        void setOrderTime(const string& time) {
            scheduled = time;
        }

        string getOrderTime() const {
            return scheduled;
        }

};

#endif