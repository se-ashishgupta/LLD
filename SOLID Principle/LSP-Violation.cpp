#include <iostream>
using namespace std;

// Liskov Substitution Principle: Objects of a superclass should be replaceable with objects of a subclass without affecting the correctness of the program.

class Account
{
public:
    virtual void deposite(double amount) = 0;
    virtual void withdraw(double amount) = 0;
};

class SavingAccount : public Account
{
private:
    double balance;

public:
    SavingAccount()
    {
        balance = 0;
    }

    void deposite(double amount)
    {
        if (amount <= 0)
        {
            cout << "Invalid Amount, Please enter valid amount > 0" << endl;
            return;
        }

        balance += amount;
        cout << "Deposited " << amount << " in Saving account. New Balance: " << balance << endl;
    }

    void withdraw(double amount)
    {
        if (amount <= 0)
        {
            cout << "Invalid Amount, Please enter valid amount > 0" << endl;
            return;
        }

        if (amount > balance)
        {
            cout << "Insufficient Amount in saving account" << endl;
            return;
        }

        balance -= amount;
        cout << "Withdrawn " << amount << " from Saving account. New Balance: " << balance << endl;
    }
};

class CurrentAccount : public Account
{
private:
    double balance;

public:
    CurrentAccount()
    {
        balance = 0;
    }

    void deposite(double amount)
    {
        if (amount <= 0)
        {
            cout << "Invalid Amount, Please enter valid amount > 0" << endl;
            return;
        }

        balance += amount;
        cout << "Deposited " << amount << " in current account. New Balance: " << balance << endl;
    }

    void withdraw(double amount)
    {
        if (amount <= 0)
        {
            cout << "Invalid Amount, Please enter valid amount > 0" << endl;
            return;
        }

        if (amount > balance)
        {
            cout << "Insufficient Amount in current account" << endl;
            return;
        }

        balance -= amount;
        cout << "Withdrawn " << amount << " from current account. New Balance: " << balance << endl;
    }
};

class FixedAccount : public Account
{
private:
    double balance;

public:
    FixedAccount()
    {
        balance = 0;
    }

    void deposite(double amount)
    {
        if (amount <= 0)
        {
            cout << "Invalid Amount, Please enter valid amount > 0" << endl;
            return;
        }

        balance += amount;
        cout << "Deposited " << amount << " in fixed account. New Balance: " << balance << endl;
    }

    void withdraw(double amount)
    {
        throw logic_error("Withdrawal not allowed in fixed account");
    }
};

class BankClient
{
private:
    vector<Account *> account;

public:
    BankClient(vector<Account *> accounts)
    {
        this->account = accounts;
    }

    void processTransactions()
    {
        for (Account *acc : account)
        {
            acc->deposite(1000);

            try
            {
                acc->withdraw(500);
            }
            catch (const std::exception &e)
            {
                cout << "Exception: " << e.what() << endl;
            }
        }
    }
};

int main()
{
    vector<Account *> accounts;
    accounts.push_back(new SavingAccount());
    accounts.push_back(new CurrentAccount());
    accounts.push_back(new FixedAccount());

    BankClient *client = new BankClient(accounts);
    client->processTransactions();

    return 0;
}