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

class ShoppingCart {
    private:
        vector<Product*> products;

    public:
        void addProduct(Product* p) {
            products.push_back(p);
        }

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

class ShoppingCartPrinter {
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

class ShoppingCartRepository {
    private:
        ShoppingCart* cart;

    public:
        ShoppingCartRepository(ShoppingCart* c) {
            cart = c;
        }

        void saveToSQLDB() {
            cout << "Saving shopping cart to SQL database..." << endl;
        }

        void saveToMongoDB() {
            cout << "Saving shopping cart to MongoDB..." << endl;
        }

        void saveToFile() {
            cout << "Saving shopping cart to file..." << endl;
        }
};


int main() {
    ShoppingCart* cart = new ShoppingCart();
    ShoppingCartPrinter* printer = new ShoppingCartPrinter(cart);
    ShoppingCartRepository* repository = new ShoppingCartRepository(cart);

    cart->addProduct(new Product("Laptop", 1200.00));
    cart->addProduct(new Product("Mouse", 25.00));
    printer->printInvoice();
    repository->saveToSQLDB();
    repository->saveToMongoDB();
    repository->saveToFile();

    return 0;
}