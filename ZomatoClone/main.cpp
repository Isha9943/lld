#include<iostream>
#include"Zomato.h"

using namespace std;

int main() {
    // Create Zomato facade
    ZomatoApp* app = new ZomatoApp();

    // Simulate a user coming in (happy Flow)
    User* user = new User(101, "John Doe", "Delhi");
    cout<<user->getName() << " has entered the app." << endl;

    // User searches for restaurants in their location
    vector<Restaurant*> restaurants = app->searchRestaurants(user->getAddress());

    if(restaurants.empty()) {
        cout << "No restaurants found in your location." << endl;
    } else {
        cout << "Restaurants found:" << endl;
        for(const Restaurant* res : restaurants) {
            cout << res->getName() << " - " << res->getLocation() << endl;
        }
    }


    // user selects a restaurant
    app->selectRestaurant(user, restaurants[0]); // Selecting the first restaurant from the search results
    cout<<"Selected restaurant: " << restaurants[0]->getName() << " - " << restaurants[0]->getLocation() << endl;

    // User views the menu of the selected restaurant
    vector<MenuItem> menu = restaurants[0]->getMenu(); // Get the menu of the selected restaurant
    for(const MenuItem& item : menu) {
        cout << item.getName() << " - " << item.getPrice() << endl;
    }

    // User adds the items in the cart
    app->addToCart(user, menu[0].getCode());
    app->addToCart(user, menu[1].getCode()); // Adding the second item from the menu to the cart


    // print user cart
    app->printUserCart(user);


    // User places the order
    Order* order = app->checkoutNow(user, "Delivery", new UpiPaymentStrategy("123456789") );

    // user pays for the cart
    app->payForOrder(user, order);


    // cleanup code
    delete app;
    delete user;
    

    return 0;
}