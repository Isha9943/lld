#ifndef CREDIT_CARD_PAYMENT_STRATEGY_H
#define CREDIT_CARD_PAYMENT_STRATEGY_H

#include "PaymentStrategy.h"
#include <iostream>
#include <string>
using namespace std;

class CreditCardPaymentStrategy : public PaymentStrategy {
    private:
        string cardNumber;
    public:
        CreditCardPaymentStrategy(const string& cardNumber) {
            this->cardNumber = cardNumber;
        }

        void pay(double amount) override {
            // Implement credit card payment logic here
            cout << "Paid " << amount << " using credit card: " << cardNumber << endl;
        }
};

#endif