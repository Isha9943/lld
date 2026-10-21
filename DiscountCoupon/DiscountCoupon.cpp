#include<vector>
#include<string>
#include<mutex>
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;


/*=======================
Discount Strategy (Strategy Pattern)
=======================*/

class DiscountStrategy {
    public:
        virtual double calculate(double baseAmount) = 0;
        virtual ~DiscountStrategy() {}
};

class FlatDiscountStrategy: public DiscountStrategy {
    private: 
        double amount;
    public:
        FlatDiscountStrategy(double amt)  {
            amount = amt;
        }

        double calculate(double baseAmount) override {
            return min(baseAmount, amount);
        }
};

class PercentageDiscountStrategy: public DiscountStrategy {
    private:
        double percent;
    public:
        PercentageDiscountStrategy(double pct) {
            percent = pct;
        }

        double calculate(double baseAmount) override {
            return baseAmount * (percent / 100.0);
        }
};

class PercentageWithCapStrategy: public DiscountStrategy {
    private:
        double percent;
        double cap;
    public:
        PercentageWithCapStrategy(double pct, double capAmt) {
            percent = pct;
            cap = capAmt;
        }

        double calculate(double baseAmount) override {
            return min(baseAmount * (percent / 100.0), cap);
        }
};

enum class StrategyType {
    FLAT,
    PERCENTAGE,
    PERCENTAGE_WITH_CAP
};

/*=======================
Discount Strategy Manager(Singleton)
=======================*/

class DiscountStrategyManager {
    private:
        static DiscountStrategyManager* instance;
        DiscountStrategyManager() {}

    public:
        static DiscountStrategyManager* getInstance() {
            if (!instance) {
                instance = new DiscountStrategyManager();
            }
            return instance;
        }

        DiscountStrategy* getStrategy(StrategyType type, double param1 = 0, double param2 = 0) {
            switch (type) {
                case StrategyType::FLAT:
                    return new FlatDiscountStrategy(param1);
                case StrategyType::PERCENTAGE:
                    return new PercentageDiscountStrategy(param1);
                case StrategyType::PERCENTAGE_WITH_CAP:
                    return new PercentageWithCapStrategy(param1, param2);
                default:
                    return nullptr;
            }
        }
};

DiscountStrategyManager* DiscountStrategyManager::instance = nullptr;

/*=======================
Assuming existing product and cart class
=======================*/
class Product {
    private:
        string name, category;
        double price;
    public: 
        Product(string n, string c, double p) {
            name = n;
            category = c;
            price = p;
        }

        string getName() {
            return name;
        }

        string getCategory() {
            return category;
        }

        double getPrice() {
            return price;
        }

};


class CartItem {
    private:
        Product* product;
        int quantity;
    public:
        CartItem(Product* p, int q) {
            product = p;
            quantity = q;
        }

        Product* getProduct() {
            return product;
        }

        int getQuantity() {
            return quantity;
        }

        double itemTotal() {
            return product->getPrice() * quantity;
        }

        const Product* getProduct() const {
            return product;
        }

};

class Cart {
    private: 
        vector<CartItem*> items;
        double originalTotal;
        double currentTotal;
        bool loyaltyMember;
        string paymentBank;
    public:
        Cart() {
            originalTotal = 0;
            currentTotal = 0;
            loyaltyMember = false;
            paymentBank = "";
        }

        void addProduct(Product* product, int quantity) {
            CartItem* newItem = new CartItem(product, quantity);
            items.push_back(newItem);
            originalTotal += newItem->itemTotal();
            currentTotal += newItem->itemTotal();
        }
        
        double getOriginalTotal() {
            return originalTotal;
        }

        double getCurrentTotal() {
            return currentTotal;
        }

        bool isLoyaltyMember() {
            return loyaltyMember;
        }

        void setLoyaltyMember(bool status) {
            loyaltyMember = status;
        }

        string getPaymentBank() {
            return paymentBank;
        }

        void setPaymentBank(string bank) {
            paymentBank = bank;
        }

        void applyDiscount(double d){
            currentTotal -= d;
            if(currentTotal < 0) {
                currentTotal = 0;
            }
        }

        vector<CartItem*> getItems() {
            return items;
        }
};

/*=======================
Coupon base class (Chain of Responsibility)
=======================*/
class Coupon {
    private:
        Coupon* next;
    public:
        Coupon() {
            next = nullptr;
        }

        virtual ~Coupon() {
            if(next) {
                delete next;
            }
        }

        void setNext(Coupon* n) {
            next = n;
        }

        Coupon* getNext(){
            return next;
        }

        void applyDiscount(Cart* cart) {
            if(isApplicable(cart)){
                double discount = getDiscount(cart);
                cart->applyDiscount(discount);
                cout<<name()<<" applied: "<<discount<<endl;
                if(!isCombinable()){
                    return;
                }
            }
            if(next) {
                next->applyDiscount(cart);
            }
        }

        virtual bool isApplicable(Cart* cart) = 0;
        virtual double getDiscount(Cart* cart) = 0;
        virtual string name() = 0;
        virtual bool isCombinable() {
            return true;
        }
};

/*=======================
Concrete Coupons 
=======================*/

class SeasonalOffer: public Coupon {
    private:    
        double percent;
        string category;
        DiscountStrategy* strat;
    public:
        SeasonalOffer(double pct, string cat) {
            percent = pct;
            category = cat;
            strat = DiscountStrategyManager::getInstance()->getStrategy(StrategyType::PERCENTAGE, percent);
        }

        ~SeasonalOffer() {
            delete strat;
        }

        bool isApplicable(Cart* cart) override {
            for(CartItem* item : cart->getItems()) {
                if(item->getProduct()->getCategory() == category) {
                    return true;
                }
            }
            return false;
        }

        double getDiscount(Cart* cart) override {
            double subtotal = 0.0;
            for(CartItem* item : cart->getItems()) {
                if(item->getProduct()->getCategory() == category) {
                    subtotal += item->itemTotal();
                }
            }
            return strat->calculate(subtotal);
        }

        bool isCombinable() override {
            return true;
        }

        string name() override {
            return "Seasonal Offer "+ to_string(percent) + "% off";
        }

};

class LoyaltyDiscount: public Coupon {
    private:
        double percent;
        DiscountStrategy* strat;
    public:
        LoyaltyDiscount(double pct) {
            percent = pct;
            strat = DiscountStrategyManager::getInstance()->getStrategy(StrategyType::PERCENTAGE, percent);
        }

        ~LoyaltyDiscount() {
            delete strat;
        }

        bool isApplicable(Cart* cart) override {
            return cart->isLoyaltyMember(); 
        }

        double getDiscount(Cart* cart) override {
            return strat->calculate(cart->getCurrentTotal());
        }

        bool isCombinable() override {
            return true;
        }

        string name() override {
            return "Loyalty Discount "+ to_string(percent) + "% off";
        }
};

class BulkPurchaseDiscount: public Coupon {
    private:
        double threshold;
        double flatOff;
        DiscountStrategy* strat;
    public:
        BulkPurchaseDiscount(double thres, double flat) {
            threshold = thres;
            flatOff = flat;
            strat = DiscountStrategyManager::getInstance()->getStrategy(StrategyType::FLAT, flatOff);
        }

        ~BulkPurchaseDiscount() {
            delete strat;
        }

        bool isApplicable(Cart* cart) override {
            if(cart->getOriginalTotal() >= threshold) {
                return true;
            }
            return false;
        }

        double getDiscount(Cart* cart) override {
            return strat->calculate(cart->getOriginalTotal());
        }

        bool isCombinable() override {
            return true;
        }

        string name() override {
            return "Bulk Purchase Discount flat off " + to_string(flatOff);
        }
};

class BankingCoupon: public Coupon {
    private:
        string bank;
        double minSpend;
        double percent;
        double offCap;
        DiscountStrategy* strat;
    public:
        BankingCoupon(string bank, double minSpendAmt, double pct, double cap) {
            bank = bank;
            minSpend = minSpendAmt;
            percent = pct;
            offCap = cap;
            strat = DiscountStrategyManager::getInstance()->getStrategy(StrategyType::PERCENTAGE_WITH_CAP, percent, offCap);
        }

        ~BankingCoupon() {
            delete strat;
        }

        bool isApplicable(Cart* cart) override {
            return cart->getPaymentBank() == bank 
            && cart->getOriginalTotal() >= minSpend;
        }

        double getDiscount(Cart* cart) override {
            return strat->calculate(cart->getCurrentTotal());
        }

        bool isCombinable() override {
            return true;
        }

        string name() override {
            return bank + " Banking Offer " + to_string(percent) + "% off";
        }
};

/*=======================
Coupon Manager (singleton)
=======================*/

class CouponManager {
    private:
        static CouponManager* instance;
        Coupon* head;
        mutable mutex mtx;
        CouponManager() {
            head = nullptr;
        }
    public:
        static CouponManager* getInstance() {
            if (!instance) {
                instance = new CouponManager();
            }
            return instance;
        }

        void registerCoupon(Coupon* coupon) {
            lock_guard<mutex> lock(mtx);
            if(!head) {
                head = coupon;
            } else {
                Coupon* cur = head;
                while(cur->getNext()) {
                    cur = cur->getNext();
                }
                cur->setNext(coupon);
            }
        }

        vector<string> getApplicable(Cart* cart) {
            lock_guard<mutex> lock(mtx);
            vector<string> applicableCoupons;
            Coupon* cur = head;
            while(cur) {
                if(cur->isApplicable(cart)) {
                    applicableCoupons.push_back(cur->name());
                }
                cur = cur->getNext();
            }
            return applicableCoupons;
        }

        double applyAll(Cart* cart) {
            lock_guard<mutex> lock(mtx);
            if(head) {
                head->applyDiscount(cart);
            }
            return cart->getCurrentTotal();
        }
};

CouponManager* CouponManager::instance = nullptr;

/*=======================
Main: Client Code
=======================*/
int main() {
    Product* product1 = new Product("Laptop", "Electronics",  100000);
    Product* product2 = new Product("Smartphone", "Electronics",  50000);
    Product* product3 = new Product("Jeans", "Clothing",  2000);
    Product* product4 = new Product("Jacket", "Clothing",  3000);

    Cart* cart = new Cart();
    cart->addProduct(product1, 1);
    cart->addProduct(product2, 1);
    cart->addProduct(product3, 2);
    cart->addProduct(product4,1 );

    cart->setPaymentBank("ABC");
    cart->setLoyaltyMember(true);

    cout<<"Total before discounts: "<<cart->getOriginalTotal()<<endl;
    
    CouponManager* mgr = CouponManager::getInstance();
    mgr->registerCoupon(new SeasonalOffer(10, "Clothing"));
    mgr->registerCoupon(new LoyaltyDiscount( 5));
    mgr->registerCoupon(new BulkPurchaseDiscount(1000, 100));
    mgr->registerCoupon(new BankingCoupon("ABC", 2000, 15, 500));

    vector<string> applicableCoupons = mgr->getApplicable(cart);
    cout<<"Applicable coupons: ";
    for(const auto& coupon : applicableCoupons) {
        cout<<coupon<<" ";
    }
    cout<<endl;

    double finalTotal = mgr->applyAll(cart);
    cout<<"Total after discounts: "<<finalTotal<<endl;

    // Cleanup 
    delete cart;
    delete product1;
    delete product2;
    delete product3;
    delete product4;
    delete mgr;

    return 0;
}