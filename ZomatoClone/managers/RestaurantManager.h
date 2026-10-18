#ifndef RESTAURANTMANAGER_H
#define RESTAURANTMANAGER_H

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cctype>
#include "../models/Restaurant.h"
using namespace std;

class RestaurantManager {
    private:
        vector<Restaurant*> restaurants; // Non-owning; registered restaurants must remain alive while in use.

        RestaurantManager() {
            // private constructor
        }

    public:
        RestaurantManager(const RestaurantManager&) = delete;
        RestaurantManager& operator=(const RestaurantManager&) = delete;

        static RestaurantManager* getInstance() {
            static RestaurantManager instance;
            return &instance;
        }

        void addRestaurant(Restaurant* restaurant) {
            if (!restaurant) {
                cerr << "Cannot add a null restaurant." << endl;
                return;
            }
            restaurants.push_back(restaurant);
        }

        vector<Restaurant*> getRestaurants() {
            return restaurants;
        }

        vector<Restaurant*> searchByLocation(const string& location) {
            vector<Restaurant*> result;
            string query = location;
            auto toLower = [](unsigned char ch) {
                return static_cast<char>(tolower(ch));
            };
            transform(query.begin(), query.end(), query.begin(), toLower);
            for (auto restaurant : restaurants) {
                string rl = restaurant->getLocation();
                transform(rl.begin(), rl.end(), rl.begin(), toLower);
                if (rl == query) {
                    result.push_back(restaurant);
                }
            }
            return result;
        }


};

#endif