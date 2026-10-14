#include<iostream>
using namespace std;


class Burger {
    public:
        virtual void prepare() = 0;
        virtual ~Burger() {}
};

class BasicBurger: public Burger {
public:
    void prepare() override {
        cout << "Preparing a basic burger." << endl;
    }
};

class StandardBurger: public Burger {
public:
    void prepare() override {
        cout << "Preparing a standard burger." << endl;
    }
};

class PremiumBurger: public Burger {
public:
    void prepare() override {
        cout << "Preparing a premium burger." << endl;
    }
};

class BurgerFactory {
public:
    Burger* createBurger(const string& type) {
        if (type == "basic") {
            return new BasicBurger();
        } else if (type == "standard") {
            return new StandardBurger();
        } else if (type == "premium") {
            return new PremiumBurger();
        } else {
            cout << "Unknown burger type: " << type << endl;
            return nullptr;
        }
    }
};

int main() {
    string type = "basic";
    BurgerFactory* factory = new BurgerFactory();
    Burger* burger = factory->createBurger(type);
    burger->prepare();
    return 0;
}