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

class Persistence {
    private:
        ShoppingCart* cart;

    public:
        virtual void save(ShoppingCart* cart) = 0;
};


class SQLPersistence : public Persistence {
    public:
        SQLPersistence() {}
        void save(ShoppingCart* cart) {
            cout << "Saving shopping cart to SQL database..." << endl;
        }
};

class MongoDBPersistence : public Persistence {
    public:
        MongoDBPersistence() {}
        void save(ShoppingCart* cart) {
            cout << "Saving shopping cart to MongoDB..." << endl;
        }
};

class FilePersistence : public Persistence {
    public:
        FilePersistence() {}
        void save(ShoppingCart* cart) {
            cout << "Saving shopping cart to file..." << endl;
        }
};



int main() {
    ShoppingCart* cart = new ShoppingCart();
    ShoppingCartPrinter* printer = new ShoppingCartPrinter(cart);
    Persistence* repositorySQL = new SQLPersistence();
    Persistence* repositoryMongoDB = new MongoDBPersistence();
    Persistence* repositoryFile = new FilePersistence();

    cart->addProduct(new Product("Laptop", 1200.00));
    cart->addProduct(new Product("Mouse", 25.00));
    printer->printInvoice();
    repositorySQL->save(cart);
    repositoryMongoDB->save(cart);
    repositoryFile->save(cart);

    return 0;
}