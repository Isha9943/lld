#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

// Notification & Decorators
class INotification {
    public:
        virtual string getContent() const = 0;
        virtual ~INotification() {};
};

// Concrete Notification: simple text Notification
class SimpleNotification: public INotification {
    private:
        string text;
    public:
        SimpleNotification(const string& msg) {
            text = msg;
        }
        string getContent() const override {
            return text;
        }
};

// Abstract Decorator for Notifications
class INotificationDecorator: public INotification {
    protected:
        INotification* notification;
    public:
        INotificationDecorator(INotification* n)  {
            notification = n;
        }
        

        virtual ~INotificationDecorator() {
            delete notification;
        }
};

// Timestamp Decorator for Notifications
class TimestampDecorator: public INotificationDecorator {
    public:
        TimestampDecorator(INotification* n) : INotificationDecorator(n) {}
        string getContent() const override {
            return "[ 2026-10-19] " + notification->getContent();
        }
};

// Decorator to append signature for the content
class SignatureDecorator: public INotificationDecorator {
    private:
        string signature;
    public:
        SignatureDecorator(INotification* n, const string& sig) : INotificationDecorator(n) {
            signature = sig;
        }
        string getContent() const override {
            return notification->getContent() + " \n-- " + signature + "\n\n";
        }
};

/*===========================
Observer Pattern Components
===========================*/

// Observer Interface: Each observer gets an update with a Notfication Pointer
class IObserver {
    public:
        virtual void update() = 0;
        virtual ~IObserver() {};
};

class IObservable {
    public:
        virtual void addObserver(IObserver* observer) = 0;
        virtual void removeObserver(IObserver* observer) = 0;
        virtual void notifyObservers() = 0;
};

// Concrete Observable
class NotificationObservable: public IObservable {
    private:
        vector<IObserver*> observers;
        INotification* currentNotification;
    public:
        NotificationObservable() {
            currentNotification = nullptr;
        }

        void addObserver(IObserver* observer) override {
            observers.push_back(observer);
        }

        void removeObserver(IObserver* observer) override {
            observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
        }

        void notifyObservers() override {
            for (auto observer : observers) {
                observer->update();
            }
        }

        INotification* getCurrentNotification() const {
            return currentNotification;
        }

        void setCurrentNotification(INotification* notification) {
            currentNotification = notification;
            notifyObservers();
        }

        string getCurrentNotificationContent() const {
            return currentNotification ? currentNotification->getContent() : "";
        }

        ~NotificationObservable() {
            if (currentNotification) {
                delete currentNotification;
            }
        }
};

// Concrete Observer: Logger
class Logger: public IObserver {    
    private:
        NotificationObservable* notificationObservable;
    public:
        Logger(NotificationObservable* obs) {
            notificationObservable = obs;
        }
        void update() override {
            cout << "Logger: " << notificationObservable->getCurrentNotificationContent() << endl;
        }
};

/*===========================
Strategy Pattern Components
===========================*/

class INotificationStrategy {
    public:
        virtual void sendNotification(const string& content) = 0;
};

class EmailStrategy : public INotificationStrategy {
    private:
        string emailAddress;
    public:
        EmailStrategy(const string& email) {
            emailAddress = email;
        }

        void sendNotification(const string& content) override {
            cout << "Sending Email Notification to " << emailAddress << ": " << content << endl;
        }
};

class SMSStrategy: public INotificationStrategy {
    private:
        string phoneNumber;
    public:
        SMSStrategy(const string& phone) {
            phoneNumber = phone;
        }

        void sendNotification(const string& content) override {
            cout << "Sending SMS Notification to " << phoneNumber << ": " << content << endl;
        }
};

class PopUpStrategy: public INotificationStrategy {
    public:
        void sendNotification(const string& content) override {
            cout << "Displaying Pop-Up Notification: " << content << endl;
        }
};


class NotificarionEngine: public IObserver {
    private:
        NotificationObservable* notificationObservable;
        vector<INotificationStrategy*> notificationStrategies;
    public:
        NotificarionEngine(NotificationObservable* obs) {
            notificationObservable = obs;
        }

        void addNotificationStrategy(INotificationStrategy* strategy) {
            notificationStrategies.push_back(strategy);
        }

        void update() override {
            string content = notificationObservable->getCurrentNotificationContent();
            for (auto strategy : notificationStrategies) {
                strategy->sendNotification(content);
            }
        }
};


/* ===========================
Notification service
=========================== */
class NotificationService {
    private:
        NotificationObservable* notificationObservable;
        static NotificationService* instance;
        vector<INotification*> notifications;

        NotificationService(){
            notificationObservable = new NotificationObservable();
        }

    public: 
        static NotificationService* getInstance() {
            if(instance==nullptr)   
                instance = new NotificationService();
            return instance;
        }

        NotificationObservable* getNotificationObservable() {
            return notificationObservable;
        }

        void sendNotification(INotification* notification) {
            notifications.push_back(notification);
            notificationObservable->notifyObservers();
        }

        ~NotificationService() {
            delete notificationObservable;
        }
    

};

NotificationService* NotificationService::instance = nullptr;

int main() {
    // Create Notification Service
    NotificationService* notificationService = NotificationService::getInstance();

    // Get Observable
    NotificationObservable* notificationObservable = notificationService->getNotificationObservable();

    // Create Logger
    Logger* logger = new Logger(notificationObservable);

    // Create Notification Engine
    NotificarionEngine* notificationEngine = new NotificarionEngine(notificationObservable);

    // Add Notification Strategies
    notificationEngine->addNotificationStrategy(new EmailStrategy("random@email.com"));
    notificationEngine->addNotificationStrategy(new SMSStrategy("1234567890"));
    notificationEngine->addNotificationStrategy(new PopUpStrategy());


    // Attach the observers
    notificationObservable->addObserver(logger);
    notificationObservable->addObserver(notificationEngine);

    // Create Notification with decorators
    INotification* notification = new SimpleNotification("This is a test notification.");
    notification = new TimestampDecorator(notification);
    notification = new SignatureDecorator(notification, "Customer Care");

    notificationService->sendNotification(notification);

    delete logger;
    delete notificationEngine;
    delete notification;
    return 0;

}