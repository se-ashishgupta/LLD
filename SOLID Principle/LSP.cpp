#include <iostream>
using namespace std;

// Liskov Substitution Principle: Objects of a superclass should be replaceable with objects of a subclass without affecting the correctness of the program.

class DepositeAccount
{
public:
    virtual void deposite(double amount) = 0;
};

class WithdrawableAccount : public DepositeAccount
{
public:
    virtual void withdraw(double amount) = 0;
};

class SavingAccount : public WithdrawableAccount
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

class CurrentAccount : public WithdrawableAccount
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

class FixedAccount : public DepositeAccount
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
};

class BankClient
{
private:
    vector<DepositeAccount *> depositeAccount;
    vector<WithdrawableAccount *> withdrawableAccount;

public:
    BankClient(vector<DepositeAccount *> depositeAccounts, vector<WithdrawableAccount *> withdrawableAccounts)
    {
        this->depositeAccount = depositeAccounts;
        this->withdrawableAccount = withdrawableAccounts;
    }

    void processTransactions()
    {
        for (DepositeAccount *acc : depositeAccount)
        {
            acc->deposite(1000);
        }

        for (WithdrawableAccount *acc : withdrawableAccount)
        {
            acc->deposite(1000);
            acc->withdraw(500);
        }
    }
};

int main()
{
    vector<DepositeAccount *> depositeAccounts;
    depositeAccounts.push_back(new SavingAccount());
    depositeAccounts.push_back(new CurrentAccount());
    depositeAccounts.push_back(new FixedAccount());

    vector<WithdrawableAccount *> withdrawableAccounts;
    withdrawableAccounts.push_back(new SavingAccount());
    withdrawableAccounts.push_back(new CurrentAccount());

    BankClient *client = new BankClient(depositeAccounts, withdrawableAccounts);
    client->processTransactions();

    return 0;
}