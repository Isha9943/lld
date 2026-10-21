#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

/* ==============================
Data Structure for Payment details
=================================*/

struct PaymentRequest {
    string sender;
    string receiver;
    double amount;
    string currency;

    PaymentRequest(const string& sender, const string& receiver, double amount, const string& currency) {
        this->sender = sender;
        this->receiver = receiver;
        this->amount = amount;
        this->currency = currency;
    }
};

/* ==============================
Banking System Interface and Implementations
(Strategy for actual payment logic)
=================================*/

class BankingSystem {
    public: 
        virtual bool processPayment(double amount) = 0;
        virtual ~BankingSystem() {}
};

class PaytmBankingSystem: public BankingSystem {
    public:
        PaytmBankingSystem() {}
        bool processPayment(double amount) override {
            // simulating 20% success rate
            int r = rand()%100;
            return (r < 20); // 20% success rate
        }
};

class RazorpayBankingSystem: public BankingSystem {
    public:
        RazorpayBankingSystem() {}
        bool processPayment(double amount) override {
            // simulating 90% success rate
            int r = rand()%100;
            return (r < 90); // 90% success rate
        }
};


/* ==============================
Payment Gateway Interface (Template Method Pattern)
=================================*/
class PaymentGateway {
    protected:
        BankingSystem* bankingSystem;
    public:
        PaymentGateway() {
            bankingSystem = nullptr;
        }

        virtual ~PaymentGateway() {
            if (bankingSystem) {
                delete bankingSystem;
            }
        }

        // Template Method for defining the standard payment flow
        virtual bool processPayment(PaymentRequest* request) {
            if(!validatePayment(request)){
                cout<<"[Payment Gateway] Validation Failed for "<<request->sender<<".\n";
                return false;
            }

            if(!initiatePayment(request)){
                cout<<"[Payment Gateway] Payment Initiation Failed for "<<request->sender<<".\n";
                return false;
            }

            if(!confirmPayment(request)){
                cout<<"[Payment Gateway] Payment Confirmation Failed for "<<request->sender<<".\n";
                return false;
            }

            return true;
        }

        // Steps to be implemented by concrete payment gateways
        virtual bool validatePayment(PaymentRequest* request) = 0;
        virtual bool initiatePayment(PaymentRequest* request) = 0;
        virtual bool confirmPayment(PaymentRequest* request) = 0;
};

/* ==============================
Concrete Payment Gateway Implementations
=================================*/

class PaytmGateway: public PaymentGateway {
    public:
        PaytmGateway() {
            bankingSystem = new PaytmBankingSystem();
        }

        bool validatePayment(PaymentRequest* request) override {
            cout<<"[Paytm Gateway] Validating Payment for "<<request->sender<<".\n";
            if(request->amount <= 0 || request->currency!="INR") {
                return false;
            }
            return true;
        }

        bool initiatePayment(PaymentRequest* request) override {
            cout<<"[Paytm Gateway] Initiating Payment for "<<request->sender<<".\n";
            return bankingSystem ? bankingSystem->processPayment(request->amount) : false;
        }

        bool confirmPayment(PaymentRequest* request) override {
            cout<<"[Paytm Gateway] Confirming Payment for "<<request->sender<<".\n";
            return true;
        }
};

class RazorpayGateway: public PaymentGateway {
    public:
        RazorpayGateway() {
            bankingSystem = new RazorpayBankingSystem();
        }

        bool validatePayment(PaymentRequest* request) override {
            cout<<"[Razorpay Gateway] Validating Payment for "<<request->sender<<".\n";
            if(request->amount <= 0) {
                return false;
            }
            return true;
        }

        bool initiatePayment(PaymentRequest* request) override {
            cout<<"[Razorpay Gateway] Initiating Payment for "<<request->sender<<".\n";
            return bankingSystem ? bankingSystem->processPayment(request->amount) : false;
        }

        bool confirmPayment(PaymentRequest* request) override {
            cout<<"[Razorpay Gateway] Confirming Payment for "<<request->sender<<".\n";
            return true;
        }
};

/* ==============================
Proxy Class that wraps a Payment Gateway to add retries
=================================*/
class PaymentGatewayProxy: public PaymentGateway {
    private:
        PaymentGateway* realGateway;
        int maxRetries;
    public:
        PaymentGatewayProxy(PaymentGateway* gateway, int retries = 3) {
            realGateway = gateway;
            maxRetries = retries;
        }

        ~PaymentGatewayProxy() {
            if(realGateway) {
                delete realGateway;
            }
        }

        bool validatePayment(PaymentRequest* request) override {
            return realGateway ? realGateway->validatePayment(request) : false;
        }

        bool initiatePayment(PaymentRequest* request) override {
            int attempts = 0;
            while(attempts < maxRetries) {
                if(realGateway && realGateway->initiatePayment(request)) {
                    return true;
                }
                attempts++;
                cout<<"[PaymentGatewayProxy] Retry "<<attempts<<" for "<<request->sender<<".\n";
            }
            return false;
        }

        bool confirmPayment(PaymentRequest* request) override {
            return realGateway ? realGateway->confirmPayment(request) : false;
        }

        bool processPayment(PaymentRequest* request) override {
            bool result = false;
            for(int attempt = 0;attempt<maxRetries;attempt++) {
                if(attempt>0) {
                    cout<< "[PaymentGatewayProxy] Retry "<<attempt<<" for "<<request->sender<<".\n";
                }
                result = realGateway ? realGateway->processPayment(request) : false;
                if(result) break;

                if(!result) {
                    cout<< "[PaymentGatewayProxy] Attempt "<<attempt+1<<" failed for "<<request->sender<<".\n";
                }
            }
            return result;
        }
};


/* ==============================
Gateway Factory for creating gateway (Singleton)
=================================*/
enum class GatewayType {
    PAYTM,
    RAZORPAY
};

class GatewayFactory {
    private:
    static GatewayFactory* instance;
    GatewayFactory(){}
    public:
        static GatewayFactory* getInstance() {
            if(!instance) {
                instance = new GatewayFactory();
            }
            return instance;
        }

        PaymentGateway* getGateway(GatewayType type) {
            switch(type) {
                case GatewayType::PAYTM:
                    return new PaymentGatewayProxy(new PaytmGateway(), 3);
                case GatewayType::RAZORPAY:
                    return new PaymentGatewayProxy(new RazorpayGateway(), 1);
                default:
                    return new PaymentGatewayProxy(new RazorpayGateway(), 1);;
            }
        }
};

GatewayFactory* GatewayFactory::instance = nullptr;

/*=======================
Unified Payment API Service  (singleton)
=======================*/
class PaymentService {
    private:
        static PaymentService* instance;
        PaymentGateway* gateway;
        PaymentService() {}

        ~PaymentService() {
            delete gateway;
        }
    public:
        static PaymentService* getInstance() {
            if(!instance) {
                instance = new PaymentService();
            }
            return instance;
        }

        void setGateway(PaymentGateway* newGateway) {
            if(gateway) {
                delete gateway;
            }
            gateway = newGateway;
        }

        bool processPayment(PaymentRequest* request) {
            if(!gateway) {
                cout << "[PaymentService] No payment gateway set.\n";
                return false;
            }
            return gateway->processPayment(request);
        }
};

PaymentService* PaymentService::instance = nullptr;

/*=======================
Controller Class for all client requests (Singleton)
=======================*/

class PaymentController {
    private:
    static PaymentController* instance;

    PaymentController() {}

    public:
        static PaymentController* getInstance() {
            if(!instance) {
                instance = new PaymentController();
            }
            return instance;
        }

        bool handlePayment(GatewayType type, PaymentRequest* request) {
            PaymentGateway* gateway = GatewayFactory::getInstance()->getGateway(type);
            PaymentService::getInstance()->setGateway(gateway);
            return PaymentService::getInstance()->processPayment(request);
        }
};

PaymentController* PaymentController::instance = nullptr;

/*=======================
Main: Client code get through the PaymentController
=======================*/

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    PaymentRequest* req1 = new PaymentRequest("Isha", "Aniket", 100, "INR");

    cout<<"Processing Payment via PayTM\n";
    bool res1 = PaymentController::getInstance()->handlePayment(GatewayType::PAYTM, req1);
    cout << "Result of PayTM payment: " << (res1 ? "Success" : "Failure") << "\n";
    cout<<"====================\n";
    cout<<"Processing Payment via Razorpay\n";
    bool res2 = PaymentController::getInstance()->handlePayment(GatewayType::RAZORPAY, req1);

    cout << "Result of Razorpay payment: " << (res2 ? "Success" : "Failure") << "\n";
    cout<<"====================\n";
}