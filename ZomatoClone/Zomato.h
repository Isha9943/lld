#ifndef ZOMATO_H
#define ZOMATO_H

#include "factories/NowOrderFactory.h"
#include "factories/OrderFactory.h"
#include "factories/ScheduledOrderFactory.h"
#include "managers/RestaurantManager.h"
#include "managers/OrderManager.h"
#include "models/Restaurant.h"
#include "models/User.h"
#include "models/Order.h"
#include "models/Cart.h"
#include "models/MenuItem.h"
#include "models/DeliveryOrder.h"
#include "models/PickupOrder.h"
#include "services/NotificationService.h"
#include "strategies/PaymentStrategy.h"
#include "strategies/CreditCardPaymentStrategy.h"
#include "strategies/UpiPaymentStrategy.h"
#include "utils/TimeUtils.h"


using namespace std;

class ZomatoApp {
    public:
        ZomatoApp() {
            initializeRestaurants();
        }

        void initializeRestaurants() {
            Restaurant* res1 = new Restaurant("Bikaner", "Delhi");
            res1->addMenuItem(MenuItem("P1", "Paneer Butter Masala", 250));
            res1->addMenuItem(MenuItem("P2", "Chole Bhature", 150));

            Restaurant* res2 = new Restaurant("Haldiram", "Kolkata");
            res2->addMenuItem(MenuItem("P3", "Rajma Chawal", 200));
            res2->addMenuItem(MenuItem("P4", "Aloo Paratha", 100));

            Restaurant* res3 = new Restaurant("Domino's", "Chennai");
            res3->addMenuItem(MenuItem("P5", "Margherita Pizza", 300));
            res3->addMenuItem(MenuItem("P6", "Pepperoni Pizza", 350));

            RestaurantManager* restarantManager = RestaurantManager::getInstance();
            restarantManager->addRestaurant(res1);
            restarantManager->addRestaurant(res2);
            restarantManager->addRestaurant(res3);
        }

        
        vector<Restaurant*> searchRestaurants(const string& location) {
            return RestaurantManager::getInstance()->searchByLocation(location);
        }

        void selectRestaurant(User* user, Restaurant* restaurant) {
            Cart* cart = user->getCart();
            cart->setRestaurant(restaurant);
        }

        void addToCart(User* user, const string& itemCode){
            Restaurant* restaurant = user->getCart()->getRestaurant();
            if(!restaurant) {
                cout << "Please select a restaurant first." << endl;
                return;
            }
            
            vector<MenuItem> menuItems = restaurant->getMenu();
            for(const MenuItem& item : menuItems) {
                if(item.getCode() == itemCode) {
                    user->getCart()->addItem(item);
                    return;
                }
            }
            cout << "Item not found in the selected restaurant's menu." << endl;
        }

        Order* checkoutNow(User* user, const string& orderType, PaymentStrategy* paymentStrategy) {
            return checkout(user, orderType, paymentStrategy, new NowOrderFactory());
        }

        Order* checkoutLater(User* user, const string& orderType, PaymentStrategy* paymentStrategy, const string& scheduleTime) {
            return checkout(user, orderType, paymentStrategy, new ScheduledOrderFactory(scheduleTime));
        }

        Order* checkout(User* user, const string& orderType, PaymentStrategy* paymentStrategy, OrderFactory* orderFactory) {
            if(user->getCart()->isEmpty()){
                return nullptr;
            }

            Cart* userCart  = user->getCart();
            Restaurant* restaurant = userCart->getRestaurant();
            vector<MenuItem> itemsOrdered = userCart->getItems();
            

            Order* order = orderFactory->createOrder(user, userCart, restaurant, itemsOrdered, paymentStrategy, orderType);
            OrderManager::getInstance()->addOrder(order);
            return order;
        }

        void payForOrder(User* user, Order* order) {
            bool isPaymentSuccess = order->processPayment();
            if(isPaymentSuccess) {
                NotificationService* notificationService = new NotificationService();
                notificationService->notify(order);
                user->getCart()->clear();
            }
        }

        void printUserCart(User* user) {
            cout<<"Items in cart: " << endl;
            vector<MenuItem> items = user->getCart()->getItems();
            for(const MenuItem& item : items) {
                cout << item.getName() << " - " << item.getCode() << " - " << item.getPrice() << endl;
            }
            cout<<"grand total: " << user->getCart()->getTotalCost() << endl;
        }

};

#endif