#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<map>
#include<algorithm>
using namespace std;


/*=========================
Product & Product Factory
=========================*/

class Product {
    private:
        int sku;
        string name;
        double price;

    public:
        Product(int sku, string name, double price) {
            this->sku = sku;
            this->name = name;
            this->price = price;
        }

        // Getters and Setters
        int getSku() {
            return sku;
        }

        void setSku(int sku) {
            this->sku = sku;
        }

        string getName() {
            return name;
        }

        void setName(string name) {
            this->name = name;
        }

        double getPrice() {
            return price;
        }

        void setPrice(double price) {
            this->price = price;
        }
};

class ProductFactory {
    public:
        static Product* createProduct(int sku) {
            // In reality product comes from DB
            string name;
            double price;

            // dummy data for now
            if(sku==101) {
                name = "Apple";
                price = 20;
            } else if(sku==102) {
                name = "Banana";
                price = 10;
            }else if (sku==103){
                name = "Chocolate";
                price = 50;
            } else if (sku==201) {
                name= "Tshirt";
                price = 500;
            } else if (sku==202) {
                name = "Jeans";
                price = 1000;
            } else {
                name = "Item"+to_string(sku);
                price = 180;
            }

            return new Product(sku, name, price);
        }
};

/*============================================
Inventory Store (Abstract) & DbInventoryStore
============================================*/

class InventoryStore {
    public:
        virtual ~InventoryStore() {}
        virtual void addProduct(Product* product, int qty) = 0;
        virtual void removeProduct(int sku, int qty) = 0;
        virtual int checkStock(int sku) = 0;
        virtual vector<Product*> listAvailableProducts() = 0;
};

class DbInventoryStore: public InventoryStore {
    private:
        map<int, int> * stock; // SKU -> Quantity
        map<int, Product*> * products; // SKU -> Product

    public:
        DbInventoryStore() {
            stock = new map<int, int>();
            products = new map<int, Product*>();
        }

        ~DbInventoryStore() {
            delete stock;
            delete products;
        }

        void addProduct(Product* prod, int qty) override {
            int sku = prod->getSku();
            if(products->count(sku)==0) {
                // Doeesn't exist
                (*products)[sku] = prod;
                (*stock)[sku] = qty;
            } else {
                delete prod;
            }
            (*stock)[sku] += qty;
        }

        void removeProduct(int sku, int qty) override {
            if(stock->count(sku)==0) {
                return;
            }

            int currentQuantity = (*stock)[sku];
            int remainingQuantity = currentQuantity - qty;
            if(remainingQuantity > 0) {
                (*stock)[sku] = remainingQuantity;
            } else {
                stock->erase(sku);
            }
        }

        int checkStock(int sku) override {
            if(stock->count(sku)==0) {
                return 0;
            }
            return (*stock)[sku];
        }

        vector<Product*> listAvailableProducts() override {
            vector<Product*> availableProducts;
            for(auto &entry : *stock) {
                int sku = entry.first;
                int qty = entry.second;
                if(qty > 0 && products->count(sku) > 0) {
                    availableProducts.push_back((*products)[sku]);
                }
            }
            return availableProducts;
        }
};

/*=========================
Inventory Manager 
=========================*/

class InventoryManager {
    InventoryStore* store;

    public:
        InventoryManager(InventoryStore* store) {
            this->store = store;
        }

        void addStock(int sku, int qty) {
            Product* prod = ProductFactory::createProduct(sku);
            store->addProduct(prod, qty);
            cout<<"[InventoryManager] Added stock for SKU: "<<sku<<" Quantity: "<<qty<<endl;
        }

        void removeStock(int sku, int qty) {
            store->removeProduct(sku, qty);
            cout<<"[InventoryManager] Removed stock for SKU: "<<sku<<" Quantity: "<<qty<<endl;
        }

        int checkStock(int sku) {
            return store->checkStock(sku);
        }

        vector<Product*> listAvailableProducts() {
            return store->listAvailableProducts();
        }
};

/*====================================
Replenish Strategy (Strategy Pattern) 
====================================*/

class ReplenishStrategy {
    public:
        virtual void replenish(InventoryManager* manager, map<int, int> itemsToReplenish) = 0;
        virtual ~ReplenishStrategy() {}

};

class ThresholdReplenishStrategy: public ReplenishStrategy {
    private:
        int threshold;

    public:
        ThresholdReplenishStrategy(int threshold) {
            this->threshold = threshold;
        }

        void replenish(InventoryManager* manager, map<int, int> itemsToReplenish) override {
            cout<<"[ThresholdReplenishStrategy] Replenishing items below threshold: "<<threshold<<endl;
            for(auto &entry : itemsToReplenish) {
                int sku = entry.first;
                int qty = entry.second;
                int current = manager->checkStock(sku);
                if(current < threshold) {
                    manager->addStock(sku, qty);
                    cout<<"[ThresholdReplenishStrategy] Replenished SKU: "<<sku<<" with Quantity: "<<qty<<endl;
                }
            }
        }
};


class WeeklyReplenishStrategy: public ReplenishStrategy {
    public:
        void replenish(InventoryManager* manager, map<int, int> itemsToReplenish) override {
            cout<<"[WeeklyReplenishStrategy] Replenishing items for the week"<<endl;
            for(auto &entry : itemsToReplenish) {
                int sku = entry.first;
                int qty = entry.second;
                manager->addStock(sku, qty);
                cout<<"[WeeklyReplenishStrategy] Replenished SKU: "<<sku<<" with Quantity: "<<qty<<endl;
            }
        }
};

/*=========================
DarkStore/ Warehouse
=========================*/

class DarkStore {
    private:
        string name;
        double x, y;
        InventoryManager* inventoryManager;
        ReplenishStrategy* replenishStrategy;

    public:
        DarkStore(string name, double x, double y) {
            this->name = name;
            this->x = x;
            this->y = y;
            
            // We could have made another factory called InventoryFactory to get
            // DbInventoryStore by Enum and hence make it loosely coupled
            inventoryManager = new InventoryManager(new DbInventoryStore());
        }

        ~DarkStore() {
            delete inventoryManager;
            if(replenishStrategy)
                delete replenishStrategy;
        }

        double distanceTo(double ux, double uy) {
            return sqrt((x - ux) * (x - ux) + (y - uy) * (y - uy));
        }

        void runReplenishment(map<int, int> itemsToReplenish) {
            if(replenishStrategy) {
                replenishStrategy->replenish(inventoryManager, itemsToReplenish);
            }
        }

        // Delegation Methods
        vector<Product*> getAllProducts() {
            return inventoryManager->listAvailableProducts();
        }

        int checkStock(int sku) {
            return inventoryManager->checkStock(sku);
        }

        void addStock(int sku, int qty) {
            inventoryManager->addStock(sku, qty);
        }

        void removeStock(int sku, int qty){
            inventoryManager->removeStock(sku, qty);
        }

        // Getters and setters
        void setReplenishStrategy(ReplenishStrategy* strategy) {
            if(replenishStrategy)
                delete replenishStrategy;
            replenishStrategy = strategy;
        }

        string getName() {
            return name;
        }

        double getX() {
            return x;
        }

        double getY() {
            return y;
        }

        InventoryManager* getInventoryManager() {
            return inventoryManager;
        }

};


/*=========================
DarkStore Manager (Singleton)
=========================*/

class DarkStoreManager {
    private:
        static DarkStoreManager* instance;
        vector<DarkStore*> darkStores;

        DarkStoreManager() {
            darkStores = vector<DarkStore*>();
        }

    public:
        static DarkStoreManager* getInstance() {
            if(!instance) {
                instance = new DarkStoreManager();
            }
            return instance;
        }

       void registerDarkStore(DarkStore* store) {
           darkStores.push_back(store);
       }

       vector<DarkStore*> getNearbyDarkStores(double ux, double uy, double maxDistance) {
           vector<pair<double, DarkStore*>> nearbyStores;
           for(auto store : darkStores) {
               double dist = store->distanceTo(ux, uy);
               if(dist <= maxDistance) {
                   nearbyStores.push_back({dist, store});
               }
           }
           sort(nearbyStores.begin(), nearbyStores.end());
           vector<DarkStore*> result;
           for(auto &p : nearbyStores) {
               result.push_back(p.second);
           }
           return result;
       }

       ~DarkStoreManager() {
           for(auto store : darkStores) {
               delete store;
           }
       }
};

DarkStoreManager* DarkStoreManager::instance = nullptr;


/*=========================
User, DeliveryAgent & Cart (Prototypes)
=========================*/
class Cart{
    public:
        vector<pair<Product*, int>> items;

        void addItem(int sku, int qty) {
            Product* product = ProductFactory::createProduct(sku);
            items.push_back({product, qty});
            cout<<"[Cart] Added SKU: "<<sku<<" Product: "<<product->getName()<<" Qty: "<<qty<<endl;
        }

        double getTotal() {
            double total = 0;
            for(auto &item : items) {
                total += item.first->getPrice() * item.second;
            }
            return total;
        }

        vector<pair<Product*, int>> getItems() {
            return items;
        }

        ~Cart() {
            for(auto &item : items) {
                delete item.first;
            }
        }
};

class User {
    public:
        string name;
        double x, y;
        Cart* cart; // User owns a cart

        User(string name, double x, double y) {
            this->name = name;
            this->x = x;
            this->y = y;
            this->cart = new Cart();
        }

        ~User() {
            delete cart;
        }

        Cart* getCart() {
            return cart;
        }
};


class DeliveryPartner{
    public:
        string name;

        DeliveryPartner(string name) {
            this->name = name;
        }

        ~DeliveryPartner() {
        }
};


/*=========================
Order & OrderManager (singleton)
=========================*/

class Order{
    public:
        static int nextId;
        int orderId;
        User* user;
        vector<pair<Product*, int>> items;
        vector<DeliveryPartner*> deliveryPartners;
        double totalAmount;

        Order(User* user){
            orderId = nextId++;
            user = user;
            totalAmount = 0;
            
        }
};

int Order::nextId = 1;

class OrderManager{
    private:
        static OrderManager* instance;
        vector<Order*> orders;

        OrderManager() {}   

    public:
        static OrderManager* getInstance() {
            if(!instance) {
                instance = new OrderManager();
            }
            return instance;
        }

        
        void placeOrder(User* user, Cart* cart) {
            cout<<"[OrderManager] Placing order for User: "<<user->name<<endl;
            vector<pair<Product*, int>> items = cart->getItems();
            // 1. Find nearby darkstores within 5 km
            double maxDist=5.0; // 5 km
            vector<DarkStore*> nearbyDarkstores = DarkStoreManager::getInstance()->getNearbyDarkStores(user->x, user->y, maxDist);

            if(nearbyDarkstores.empty()) {
                cout << "[OrderManager] No nearby darkstores found for User: " << user->name << endl;
                return;
            }

            // 2. Check if closest store has all items
            DarkStore* firstStore = nearbyDarkstores.front();

            bool allInFirst = true;
            for(pair<Product*, int> item : items) {
                int sku = item.first->getSku();
                int qty = item.second;

                if(firstStore->checkStock(sku)<qty) {
                    allInFirst = false;
                    break;
                }
            }


            Order* order = new Order(user);

            // One delivery partner required
            if(allInFirst) {
                cout<<"All items are available in the first darkstore."<<endl;

                // Remove the products from the store
                for(pair<Product*, int> item : items) {
                    int sku = item.first->getSku();
                    int qty = item.second;
                    firstStore->removeStock(sku, qty);
                    order->items.push_back({item.first, qty});
                }

                order->totalAmount = cart->getTotal();
                order->deliveryPartners.push_back(new DeliveryPartner("Partner1"));
                cout<<"Order placed successfully with delivery partner: Partner1"<<endl;
            }

            // Multiple delivery partners required
            else {
                cout<<"Spliting orders across stores"<<endl;
                map<int, int> allItems ; // sku ->quantity

                for(pair<Product*, int> item : items) {
                    allItems[item.first->getSku()] = item.second;
                }

                int partnerId = 1;
                for(DarkStore* store: nearbyDarkstores) {
                    if(allItems.empty()) {
                        break;
                    }

                    cout<<"Checking: " << store->getName() << endl;
                    bool assigned = false;
                    vector<int> toErase;
                    for(auto & [sku, qtyNeeded]: allItems) {
                        int available = store->checkStock(sku);
                        if(available<=0) continue;

                        int takenQty = min(available, qtyNeeded);
                        store->removeStock(sku, takenQty);
                        order->items.push_back({ProductFactory::createProduct(sku), takenQty});
                        
                        if(qtyNeeded > takenQty) {
                            allItems[sku] -= takenQty;
                        } else {
                            toErase.push_back(sku);
                        }
                        assigned = true;
                    }

                    // After iterating all SKUs in allItems, we
                    // erase any fully-satisfied SKUs from allItems map
                    for(int sku: toErase) {
                        allItems.erase(sku);
                    }

                    // If atleast one sku was taken from this store, we assign a 
                    // delivery partner
                    if(assigned) {
                        order->deliveryPartners.push_back(new DeliveryPartner("Partner" + to_string(partnerId)));
                        cout<<"Order assigned to delivery partner: Partner" << partnerId << endl;
                    }
                }

                if(!allItems.empty()) {
                    cout<<"Some items could not be fulfilled from nearby stores."<<endl;
                    for(auto & [sku, qtyNeeded]: allItems) {
                        cout<<"SKU: " << sku << ", Quantity needed: " << qtyNeeded << endl;
                    }

                }

                // recompute order total -> totalAmount
                double sum = 0;
                for(auto & [product, qty]: order->items) {
                    sum += product->getPrice() * qty;
                }
                order->totalAmount = sum;
            }

            // Printing order summary
            cout<<"Order Summary:"<<endl;
            for(auto & [product, qty]: order->items) {
                cout<<"Product: " << product->getName() << ", Quantity: " << qty << ", Price: " << product->getPrice() << endl;
            }
            cout<<"Total Amount: " << order->totalAmount << endl;
            for(auto & partner: order->deliveryPartners) {
                cout<<"Delivery Partner: " << partner->name << endl;
            }

            orders.push_back(order);

        }

};

OrderManager* OrderManager::instance = nullptr;
/*=========================
High Level Service Class
=========================*/
class Zepto{
    public:
        static void showAllItems(User* user) {
            cout<<"[Zepto] All available products within 5 KM for " << user->name << endl;

            DarkStoreManager* dsManager = DarkStoreManager::getInstance();
            vector<DarkStore*> nearbyStores = dsManager->getNearbyDarkStores(user->x, user->y, 5.0);

            // Collect each SKU -> price (so we only display each product once)
            map<int, double> skuToPrice;
            map<int, string> skuToName;

            for(DarkStore* darkStore: nearbyStores) {
                vector<Product*> products = darkStore->getAllProducts();

                for(Product* product: products) {
                    int sku = product->getSku();

                    if(skuToPrice.count(sku)==0){
                        skuToPrice[sku] = product->getPrice();
                        skuToName[sku] = product->getName();
                    }
                }

            }
            
            // Display all collected products
            for(auto & [sku, price]: skuToPrice) {
                cout<<"SKU: " << sku << ", Name: " << skuToName[sku] << ", Price: " << price << endl;
            }
        }


        static void initialize() {
            auto dsManager = DarkStoreManager::getInstance();

            // DarkStore A 
            DarkStore* darkStoreA = new DarkStore("DarkStore A", 0, 0);
            darkStoreA->setReplenishStrategy(new ThresholdReplenishStrategy(3));

            cout<<"Adding stocks in DarkStore A" << endl;
            darkStoreA->addStock(101, 5);
            darkStoreA->addStock(102, 2);


            // DarkStore B
            DarkStore* darkStoreB = new DarkStore("DarkStore B", 4, 1);
            darkStoreB->setReplenishStrategy(new ThresholdReplenishStrategy(3));

            cout<<"Adding stocks in DarkStore B" << endl;
            darkStoreB->addStock(101, 3);
            darkStoreB->addStock(103, 7);

            // DarkStore C
            DarkStore* darkStoreC = new DarkStore("DarkStore C", 2, 3);
            darkStoreC->setReplenishStrategy(new ThresholdReplenishStrategy(3));

            cout<<"Adding stocks in DarkStore C" << endl;
            darkStoreC->addStock(301, 4);
            darkStoreC->addStock(201, 6);

            dsManager->registerDarkStore(darkStoreA);
            dsManager->registerDarkStore(darkStoreB);
            dsManager->registerDarkStore(darkStoreC);
        }
};

/*=========================
Main
=========================*/
int main() {
    // 1. Initialize
    Zepto::initialize();

    // 2. A user comes on Platform
    User* user = new User("John Doe", 1, 1);
    cout<<"User " << user->name << " has come on the platform." << endl;

    // 3. Display all available products within 5 KM for the user
    Zepto::showAllItems(user);

    // 4. User adds items to cart
    cout<<"Adding items to cart..." << endl;
    Cart* cart = user->getCart();
    cart->addItem(101, 2);
    cart->addItem(102, 1);
    cart->addItem(103, 3);

    // 5. Place order
    OrderManager::getInstance()->placeOrder(user, user->cart);

    //6. Cleanup
    delete user;
    delete DarkStoreManager::getInstance();

    return 0;
}