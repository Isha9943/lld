#include<iostream>
#include<string>
#include<vector>
#include<stdexcept>
using namespace std;

class DepositOnlyAccount {
    public:
        virtual void deposit(double amount) = 0;
};


class WithdrawableAccount: public DepositOnlyAccount {
    public:
        virtual void withdraw(double amount) = 0;
};

class SavingAccount: public WithdrawableAccount {
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

class CurrentAccount: public WithdrawableAccount {
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

class FixedTermAccount: public DepositOnlyAccount {
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
};

class BankClient {
    private:
        vector<DepositOnlyAccount*> depositOnlyAccounts;
        vector<WithdrawableAccount*> withdrawableAccounts;

    public:

        BankClient(vector<WithdrawableAccount*> withdrawableAccounts, vector<DepositOnlyAccount*> depositOnlyAccounts) {
            this->withdrawableAccounts = withdrawableAccounts;
            this->depositOnlyAccounts = depositOnlyAccounts;
        }

        void processTransactions() {
            for(WithdrawableAccount* account : withdrawableAccounts) {
                account->deposit(1000);  // All accounts receive a deposit of $1000
                account->withdraw(500);  // Attempt to withdraw $500 from withdrawable accounts
            }

            for(DepositOnlyAccount* account : depositOnlyAccounts) {
                account->deposit(1000);  // All deposit-only accounts receive a deposit of $1000
            }
        }
};


int main() {
    vector<WithdrawableAccount*> withdrawableAccounts;
    vector<DepositOnlyAccount*> depositOnlyAccounts;

    withdrawableAccounts.push_back(new SavingAccount());
    withdrawableAccounts.push_back(new CurrentAccount());

    depositOnlyAccounts.push_back(new FixedTermAccount());

    BankClient* client = new BankClient(withdrawableAccounts, depositOnlyAccounts);
    client->processTransactions();
    return 0;
}