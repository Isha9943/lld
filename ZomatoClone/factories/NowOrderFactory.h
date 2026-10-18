#ifndef NOWORDERFACTORY_H
#define NOWORDERFACTORY_H

#include "OrderFactory.h"
#include "../models/DeliveryOrder.h"
#include "../models/PickupOrder.h"
#include "../utils/TimeUtils.h"
#include<vector>
#include<string>
#include<iostream>
using namespace std;

class NowOrderFactory : public OrderFactory {
    public:
        Order* createOrder(User* user, Cart* cart, Restaurant* restaurant, const vector<MenuItem>& menuItems, 
                            PaymentStrategy* paymentStrategy, const string& orderType) override {
            if (!user || !cart || !restaurant || menuItems.empty()) {
                cerr << "A user, cart, restaurant, and items are required." << endl;
                return nullptr;
            }
            if (orderType != "Delivery" && orderType != "Pickup") {
                cerr << "Order type must be Delivery or Pickup." << endl;
                return nullptr;
            }
            Order* order = nullptr;
            if(orderType == "Delivery") {
                auto deliveryOrder = new DeliveryOrder();
                deliveryOrder->setUserAddress(user->getAddress());
                order = deliveryOrder;
            } else {
                auto pickupOrder = new PickupOrder();
                pickupOrder->setRestaurantAddress(restaurant->getLocation());
                order = pickupOrder;
            }

            order->setUser(user);
            order->setRestaurant(restaurant);
            order->setItems(menuItems);
            order->setCart(cart);
            order->setPaymentStrategy(paymentStrategy);
            order->setOrderTime(TimeUtils::getCurrentTime());
            return order;
        }
};

#endif