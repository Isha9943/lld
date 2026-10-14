#include<iostream>
#include<string>
#include<vector>
using namespace std;


class Product {
    public:
        string name;
        double price;

        Product(string n, double p) {
            name = n;
            price = p;
        }
};

// SRP not followed
class ShoppingCart {
    private:
        vector<Product> products;

    public:
        void addProduct(Product p) {
            products.push_back(p);
        }

        // 1. Calculate cart total
        double calculateTotal() {
            double total = 0;
            for(auto p : products) {
                total += p.price;
            }
            return total;
        }

        // 2. Print invoice
        void printInvoice(){
            cout<<"Shopping Cart Invoice:" << endl;
            for(auto p : products) {
                cout << p.name << " - $" << p.price << endl;
            }
            cout << "Total: $" << calculateTotal() << endl;
        }

        // 3. Save cart to database
        void saveToDB(){
            cout << "Saving shopping cart to database..." << endl;
        }
};

int main(){
    ShoppingCart* cart = new ShoppingCart();
    cart->addProduct(Product("Laptop", 1200.00));
    cart->addProduct(Product("Mouse", 25.00));
    cart->printInvoice();
    cart->saveToDB();
    return 0;
}