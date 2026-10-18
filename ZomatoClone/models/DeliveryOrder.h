#ifndef DELIVERYORDER_H
#define DELIVERYORDER_H

#include "Order.h"
using namespace std;

class DeliveryOrder : public Order {
    private:
        string userAddress;
    public:
        DeliveryOrder() : Order() {
            userAddress = "";
        }

        virtual string getType() const override {
            return "Delivery";
        }

        void setUserAddress(const string& address) {
            userAddress = address;
        }

        string getUserAddress() const {
            return userAddress;
        }

};

#endif