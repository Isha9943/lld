#ifndef ORDERFACTORY_H
#define ORDERFACTORY_H

#include "../models/Order.h"
#include "../models/Cart.h"
#include "../models/Restaurant.h"
#include "../strategies/PaymentStrategy.h"
#include<vector>
#include<string>
#include<iostream>
using namespace std;

class OrderFactory {
    public:
        // Caller owns the returned order; only a successful creation transfers payment ownership.
        virtual Order* createOrder(User* user, Cart* cart, Restaurant* restaurant, const vector<MenuItem>& menuItems, 
                                    PaymentStrategy* paymentStrategy, const string& orderType) = 0;

        virtual ~OrderFactory() {}
};

#endif