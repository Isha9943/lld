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

class BasicWheatBurger: public Burger {
public:
    void prepare() override {
        cout << "Preparing a basic wheat burger." << endl;
    }
};

class StandardWheatBurger: public Burger {
public:
    void prepare() override {
        cout << "Preparing a standard wheat burger." << endl;
    }
};

class PremiumWheatBurger: public Burger {
public:
    void prepare() override {
        cout << "Preparing a premium wheat burger." << endl;
    }
};

class BurgerFactory {
public:
    virtual Burger* createBurger(string& type) = 0;
};

class SinghBurger: public BurgerFactory {
public:
    Burger* createBurger(string& type) override {
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

class KingBurger: public BurgerFactory {
public:
    Burger* createBurger(string& type) override {
        if (type == "basic") {
            return new BasicWheatBurger();
        } else if (type == "standard") {
            return new StandardWheatBurger();
        } else if (type == "premium") {
            return new PremiumWheatBurger();
        } else {
            cout << "Unknown burger type: " << type << endl;
            return nullptr;
        }
    }
};

int main() {
    string type = "basic";

    BurgerFactory* singhFactory = new SinghBurger();
    Burger* singhBurger = singhFactory->createBurger(type);
    singhBurger->prepare();

    BurgerFactory* kingFactory = new KingBurger();
    Burger* kingBurger = kingFactory->createBurger(type);
    kingBurger->prepare();

    return 0;
}