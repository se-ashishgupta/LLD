#include <iostream>
using namespace std;

enum PaymentMethod
{
    CREDIT_CARD,
    BANANA,
    UNKNOWN
};

class PaymentProcessor
{
public:
    void processPayment(string type, double amount)
    {
        if (type == "cc")
            cout << "Paid $ " << amount << " using credit card" << endl;
        else if (type == "upi")
            cout << "Paid $ " << amount << " using UPI" << endl;
        else if (type == "net_banking")
            cout << "Paid $ " << amount << " using Net Banking" << endl;
        else if (type == "cash")
            cout << "Paid $ " << amount << " using Cash" << endl;

        // Adding another payment method(crypto) requires modifying this class
        // This keeps growing with each new payment method
        // bad design
    }
};

int main()
{
    PaymentProcessor *pp = new PaymentProcessor();

    pp->processPayment("cc", 1000);
    pp->processPayment("net_banking", 1000);
    pp->processPayment("cash", 1000);
    pp->processPayment("upi", 1000);

    return 0;
}