#include<iostream>
#include<string>
#include<vector>
#include<stdexcept>
using namespace std;

class Account {
    public:
        virtual void deposit(double amount) = 0;
        virtual void withdraw(double amount) = 0;
};


class SavingAccount: public Account {
    private:
        double balance;

    public:
        SavingAccount() {
            balance = 0;
        }

        void deposit(double amount) override {
            balance += amount;
            cout<<"Deposited: $" << amount << " in Saving Account, New Balance: $" << balance << endl;
        }

        void withdraw(double amount) override {
            if(amount <= balance) {
                balance -= amount;
                cout<<"Withdrew: $" << amount << " from Saving Account, New Balance: $" << balance << endl;
            } else {
                cout << "Insufficient balance in Saving Account" << endl;
            }
        }
};

class CurrentAccount: public Account {
    private:
        double balance;

    public:
        CurrentAccount() {
            balance = 0;
        }

        void deposit(double amount) override {
            balance += amount;
            cout<<"Deposited: $" << amount << " in Current Account, New Balance: $" << balance << endl;
        }

        void withdraw(double amount) override {
            if(amount <= balance) {
                balance -= amount;
                cout<<"Withdrew: $" << amount << " from Current Account, New Balance: $" << balance << endl;
            } else {
                cout << "Insufficient balance in Current Account" << endl;
            }
        }
};

class FixedTermAccount: public Account {
    private:
        double balance;

    public:
        FixedTermAccount() {
            balance = 0;
        }

        void deposit(double amount) override {
            balance += amount;
            cout<<"Deposited: $" << amount << " in Fixed Term Account, New Balance: $" << balance << endl;
        }

        void withdraw(double amount) override {
            throw logic_error("Withdrawals are not allowed in Fixed Term Account");
        }
};

class BankClient {
    private:
        vector<Account*> accounts;

    public:

        BankClient(vector<Account*> accounts) {
            this->accounts = accounts;
        }

        void processTransactions() {
            for(Account* account : accounts) {
                account->deposit(1000);  // All accounts receive a deposit of $100
                
                // Assuming all accounts support withdrawls (LSP violation)
                try {
                    account->withdraw(50);  // Attempt to withdraw $50 from each account
                } catch (const logic_error& e) {
                    cout << "Exception: " << e.what() << endl;
                }
            }
        }
};

int main() {
    vector<Account*> accounts;
    accounts.push_back(new SavingAccount());
    accounts.push_back(new CurrentAccount());
    accounts.push_back(new FixedTermAccount());

    BankClient* client = new BankClient(accounts);
    client->processTransactions(); // Throws exception for Fixed Term Account withdrawals
    return 0;
}
