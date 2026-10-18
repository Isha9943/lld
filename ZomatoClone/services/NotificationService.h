#ifndef NOTIFICATION_SERVICE_H
#define NOTIFICATION_SERVICE_H

#include <string>
#include <iostream>
#include "../models/Order.h"
using namespace std;

class NotificationService {
    public:
        static void notify(Order* order) {
            if (!order || !order->getUser() || !order->getRestaurant()) {
                cerr << "Cannot notify an incomplete order." << endl;
                return;
            }
            cout<<"Notification: New " << order->getType() << " order received." << endl;
            cout<<"------------------------------------------------"<<endl;
            cout<<"Order ID: " << order->getOrderId() << endl;
            cout<<"Customer: "<<order->getUser()->getName() << endl;
            cout<<"Restaurant: "<<order->getRestaurant()->getName() << endl;
            for (const auto& item : order->getItems()) {
                cout<<item.getName()<<" - "<<item.getPrice()<<endl;
            }
            cout<<"Total: "<<order->getTotal()<<endl;
            cout<<"Order time: "<<order->getOrderTime()<<endl;
            cout<<"------------------------------------------------"<<endl;
        }
};

#endif