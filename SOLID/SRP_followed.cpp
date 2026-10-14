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

// SRP followed
class ShoppingCart {
    private:
        vector<Product*> products;

    public:
        void addProduct(Product* p) {
            products.push_back(p);
        }

        // 1. Calculate cart total
        double calculateTotal() {
            double total = 0;
            for(auto p : products) {
                total += p->price;
            }
            return total;
        }

        const vector<Product*>& getProducts() const {
            return products;
        }
};

class ShoppingCartPrinter{
    private:
        ShoppingCart* cart;

    public:
        ShoppingCartPrinter(ShoppingCart* c) {
            cart = c;
        }

        void printInvoice() {
            cout<<"Shopping Cart Invoice:" << endl;
            for(auto p : cart->getProducts()) {
                cout << p->name << " - $" << p->price << endl;
            }
            cout << "Total: $" << cart->calculateTotal() << endl;
        }
};  

class ShoppingCartStorage{
    private:
        ShoppingCart* cart;

    public:
        ShoppingCartStorage(ShoppingCart* c) {
            cart = c;
        }

        void saveToDB() {
            cout << "Saving shopping cart to database..." << endl;
        }
};

int main(){
    ShoppingCart* cart = new ShoppingCart();
    cart->addProduct(new Product("Laptop", 1200.00));
    cart->addProduct(new Product("Mouse", 25.00));
    ShoppingCartPrinter* printer = new ShoppingCartPrinter(cart);
    printer->printInvoice();    
    ShoppingCartStorage* storage = new ShoppingCartStorage(cart);
    storage->saveToDB();
    return 0;
}