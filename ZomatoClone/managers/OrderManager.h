#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include "../models/Order.h"
#include <vector>
#include <iostream>
using namespace std;

class OrderManager {
    private:
        vector<Order*> orders; // Non-owning; registered orders must remain alive while in use.

        OrderManager() {
            // Private Constructor
        }
    public:
        OrderManager(const OrderManager&) = delete;
        OrderManager& operator=(const OrderManager&) = delete;

        static OrderManager* getInstance() {
            static OrderManager instance;
            return &instance;
        }

        void addOrder(Order* order) {
            if (!order) {
                cerr << "Cannot add a null order." << endl;
                return;
            }
            orders.push_back(order);
        }

        void listOrders() {
            cout << "Listing all orders:" << endl;
            for (const auto& order : orders) {
                cout << "Order ID: " << order->getOrderId() << ", Type: " << order->getType() << endl;
            }
        }

};

#endif