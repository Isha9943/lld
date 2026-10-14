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

class GarlicBread {
    public:
        virtual void prepare() = 0;
        virtual ~GarlicBread() {}
};

class BasicGarlicBread: public GarlicBread {
public:
    void prepare() override {
        cout << "Preparing a basic garlic bread." << endl;
    }
};

class CheeseGarlicBread: public GarlicBread {
public:
    void prepare() override {
        cout << "Preparing a cheese garlic bread." << endl;
    }
};

class BasicWheatGarlicBread: public GarlicBread {
public:
    void prepare() override {
        cout << "Preparing a basic wheat garlic bread." << endl;
    }
};

class CheeseWheatGarlicBread: public GarlicBread {
public:
    void prepare() override {
        cout << "Preparing a cheese wheat garlic bread." << endl;
    }
};




class MealFactory {
public:
    virtual Burger* createBurger(string& type) = 0;
    virtual GarlicBread* createGarlicBread(string& type) = 0;
};

class SinghBurger: public MealFactory {
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

    GarlicBread* createGarlicBread(string& type) override {
        if (type == "basic") {
            return new BasicGarlicBread();
        } else if (type == "cheese") {
            return new CheeseGarlicBread();
        }  else {
            cout << "Unknown garlic bread type: " << type << endl;
            return nullptr;
        }
    }
};

class KingBurger: public MealFactory {
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

    GarlicBread* createGarlicBread(string& type) override {
        if (type == "basic") {
            return new BasicWheatGarlicBread();
        } else if (type == "cheese") {
            return new CheeseWheatGarlicBread();
        }  else {
            cout << "Unknown garlic bread type: " << type << endl;
            return nullptr;
        }
    }
};

int main() {
    string type = "basic";

    MealFactory* singhFactory = new SinghBurger();
    Burger* singhBurger = singhFactory->createBurger(type);
    singhBurger->prepare();
    
    GarlicBread* singhGarlicBread = singhFactory->createGarlicBread(type);
    singhGarlicBread->prepare();

    MealFactory* kingFactory = new KingBurger();
    Burger* kingBurger = kingFactory->createBurger(type);
    kingBurger->prepare();

    GarlicBread* kingGarlicBread = kingFactory->createGarlicBread(type);
    kingGarlicBread->prepare();

    return 0;
}