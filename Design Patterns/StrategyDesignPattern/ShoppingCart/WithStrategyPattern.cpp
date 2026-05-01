#include <iostream>
using namespace std;

class PaymentStrategy
{
public:
    virtual void pay(double amount) = 0;
    virtual ~PaymentStrategy() {}
};

class CreditCardPayment : public PaymentStrategy
{
private:
    string cardNumber;

public:
    CreditCardPayment(string cardNo) : cardNumber(cardNo) {}
    void pay(double amount) override
    {
        cout << "Paid $" << amount << " using credit card ending in " << cardNumber.substr(cardNumber.size() - 4) << endl;
    }
};

class PaypalPayment : public PaymentStrategy
{
private:
    string email;

public:
    PaypalPayment(string email) : email(email) {}

    void pay(double amount) override
    {
        cout << "Paid $" << amount << " using Paypal account " << email << endl;
    }
};

class UPIPayment : public PaymentStrategy
{
private:
    string upiId;

public:
    UPIPayment(string upiId) : upiId(upiId) {}

    void pay(double amount) override
    {
        cout << "Paid $" << amount << " using UPI ID " << upiId << endl;
    }
};

class ShoppingCart
{
private:
    PaymentStrategy *paymentStrategy = nullptr;

public:
    void setPaymentStrategy(PaymentStrategy *strategy)
    {
        if (paymentStrategy)
            delete paymentStrategy;
        paymentStrategy = strategy;
    }

    void checkout(double amount)
    {
        if (paymentStrategy)
        {
            paymentStrategy->pay(amount);
        }
        else
        {
            cout << "No payment method selected" << endl;
        }
    }

    ~ShoppingCart()
    {
        delete paymentStrategy;
    }
};

int main()
{
    ShoppingCart *cart = new ShoppingCart();

    cart->setPaymentStrategy(new CreditCardPayment("1234-5678-4567"));
    cart->checkout(500);

    cart->setPaymentStrategy(new UPIPayment("sdf123123"));
    cart->checkout(100);

    return 0;
}