#ifndef PICKUPORDER_H
#define PICKUPORDER_H

#include "Order.h"
using namespace std;

class PickupOrder : public Order {
    private: 
        string restaurantAddress;
    public:
        PickupOrder() : Order() {
            restaurantAddress = "";
        }
        virtual string getType() const override {
            return "Pickup";
        }

        void setRestaurantAddress(const string& address) {
            restaurantAddress = address;
        }

        string getRestaurantAddress() const {
            return restaurantAddress;
        }
};

#endif