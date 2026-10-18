#include "../factories/NowOrderFactory.h"
#include "../factories/ScheduledOrderFactory.h"
#include "../managers/OrderManager.h"
#include "../managers/RestaurantManager.h"
#include "../services/NotificationService.h"
#include "../strategies/CreditCardPaymentStrategy.h"
#include "../strategies/UpiPaymentStrategy.h"
#include <cassert>
#include <memory>
#include <sstream>

class TestPayment : public PaymentStrategy {
    public:
        double amount = -1;

        void pay(double value) override {
            amount = value;
        }
};

int main() {
    Restaurant restaurant("Spice Kitchen", "Delhi");
    Restaurant otherRestaurant("Cafe", "Mumbai");
    restaurant.addMenuItem(MenuItem("P1", "Pizza", 250));
    restaurant.addMenuItem(MenuItem("D1", "Drink", 50));
    assert(restaurant.getRestaurantId() != otherRestaurant.getRestaurantId());

    User user(1, "Isha", "12 Main Street");
    Cart* cart = user.getCart();
    assert(user.getUserId() == 1);
    assert(cart->isEmpty());
    assert(cart->getTotalCost() == 0);

    std::ostringstream errors;
    auto* previousErrors = std::cerr.rdbuf(errors.rdbuf());
    cart->addItem(restaurant.getMenu()[0]);
    assert(cart->isEmpty());

    cart->setRestaurant(&restaurant);
    assert(cart->isEmpty());
    cart->addItem(restaurant.getMenu()[0]);
    cart->addItem(restaurant.getMenu()[1]);
    assert(cart->getTotalCost() == 300);
    assert(cart->getItems().size() == 2);
    cart->setRestaurant(&otherRestaurant);
    assert(cart->getRestaurant() == &restaurant);

    NowOrderFactory nowFactory;
    ScheduledOrderFactory scheduledFactory("Tomorrow at 7 PM");
    OrderFactory* factory = &nowFactory;
    auto payment = std::make_unique<TestPayment>();
    std::unique_ptr<Order> delivery(factory->createOrder(
        &user, cart, &restaurant, cart->getItems(), payment.get(), "Delivery"));
    assert(delivery);
    TestPayment* recordedPayment = payment.release();
    assert(delivery->getUser() == &user);
    assert(delivery->getCart() == cart);
    assert(delivery->getRestaurant() == &restaurant);
    assert(delivery->getType() == "Delivery");
    assert(delivery->getTotal() == 300);
    assert(!delivery->getOrderTime().empty());
    assert(dynamic_cast<DeliveryOrder*>(delivery.get())->getUserAddress() == user.getAddress());
    assert(delivery->processPayment());
    assert(recordedPayment->amount == 300);

    std::unique_ptr<Order> pickup(nowFactory.createOrder(
        &user, cart, &restaurant, cart->getItems(), nullptr, "Pickup"));
    assert(pickup->getType() == "Pickup");
    assert(dynamic_cast<PickupOrder*>(pickup.get())->getRestaurantAddress() == "Delhi");
    assert(!pickup->processPayment());
    pickup->setPaymentStrategy(new UpiPaymentStrategy("9876543210"));
    assert(pickup->processPayment());
    pickup->setPaymentStrategy(new CreditCardPaymentStrategy("1234567812345678"));
    assert(pickup->processPayment());
    assert(pickup->getOrderId() != delivery->getOrderId());

    factory = &scheduledFactory;
    std::unique_ptr<Order> scheduledDelivery(factory->createOrder(
        &user, cart, &restaurant, cart->getItems(), nullptr, "Delivery"));
    std::unique_ptr<Order> scheduledPickup(factory->createOrder(
        &user, cart, &restaurant, cart->getItems(), nullptr, "Pickup"));
    assert(scheduledDelivery->getType() == "Delivery");
    assert(scheduledPickup->getType() == "Pickup");
    assert(scheduledDelivery->getOrderTime() == "Tomorrow at 7 PM");
    assert(scheduledPickup->getOrderTime() == "Tomorrow at 7 PM");

    for (OrderFactory* invalidFactory : {static_cast<OrderFactory*>(&nowFactory), factory}) {
        assert(!invalidFactory->createOrder(
            nullptr, cart, &restaurant, cart->getItems(), nullptr, "Delivery"));
        assert(!invalidFactory->createOrder(
            &user, nullptr, &restaurant, cart->getItems(), nullptr, "Delivery"));
        assert(!invalidFactory->createOrder(
            &user, cart, nullptr, cart->getItems(), nullptr, "Delivery"));
        assert(!invalidFactory->createOrder(
            &user, cart, &restaurant, {}, nullptr, "Delivery"));
        assert(!invalidFactory->createOrder(
            &user, cart, &restaurant, cart->getItems(), nullptr, "Unknown"));
    }
    ScheduledOrderFactory emptySchedule("");
    assert(!emptySchedule.createOrder(
        &user, cart, &restaurant, cart->getItems(), nullptr, "Delivery"));

    RestaurantManager* restaurants = RestaurantManager::getInstance();
    assert(restaurants == RestaurantManager::getInstance());
    restaurants->addRestaurant(nullptr);
    restaurants->addRestaurant(&restaurant);
    restaurants->addRestaurant(&otherRestaurant);
    assert(restaurants->getRestaurants().size() == 2);
    assert(restaurants->searchByLocation("dELHi").size() == 1);
    assert(restaurants->searchByLocation("MUMBAI")[0] == &otherRestaurant);
    assert(restaurants->searchByLocation("Unknown").empty());

    OrderManager* orders = OrderManager::getInstance();
    assert(orders == OrderManager::getInstance());
    orders->addOrder(nullptr);
    orders->addOrder(delivery.get());
    orders->addOrder(scheduledPickup.get());
    std::ostringstream output;
    auto* previousOutput = std::cout.rdbuf(output.rdbuf());
    orders->listOrders();
    NotificationService::notify(delivery.get());
    NotificationService::notify(scheduledPickup.get());
    NotificationService::notify(nullptr);
    DeliveryOrder incompleteOrder;
    NotificationService::notify(&incompleteOrder);
    std::cout.rdbuf(previousOutput);
    assert(output.str().find("Type: Delivery") != std::string::npos);
    assert(output.str().find("Type: Pickup") != std::string::npos);
    assert(output.str().find("Customer: Isha") != std::string::npos);
    assert(output.str().find("Pizza - 250") != std::string::npos);
    assert(output.str().find("Total: 300") != std::string::npos);
    assert(output.str().find("Tomorrow at 7 PM") != std::string::npos);

    cart->clear();
    assert(cart->isEmpty());
    assert(cart->getRestaurant() == nullptr);
    assert(cart->getTotalCost() == 0);
    assert(delivery->getItems().size() == 2);
    assert(delivery->getTotal() == 300);
    cart->setRestaurant(&otherRestaurant);
    assert(cart->getRestaurant() == &otherRestaurant);
    std::cerr.rdbuf(previousErrors);
    assert(!errors.str().empty());
    std::cout << "All flow tests passed." << std::endl;
}
