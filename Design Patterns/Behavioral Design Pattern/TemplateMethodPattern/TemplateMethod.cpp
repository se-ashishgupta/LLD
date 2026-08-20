#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

class PaymentFlow
{
public:
    virtual void validateRequest() = 0;
    virtual void debitAmount() = 0;
    virtual void calculateFees() = 0;
    virtual void creditAmount() = 0;

    void sendMoney()
    {
        validateRequest();

        debitAmount();

        calculateFees();

        creditAmount();
    }

    void logTransaction()
    {
        cout << "Transaction Completed" << endl;
    }

protected:
    bool requiresOTPAuthentication()
    {
        return false;
    }
};

class BankTransfer : public PaymentFlow
{
    void validateRequest() override
    {
        cout << "Specific Validation Logic for Bank Transfer" << endl;
    }

    void debitAmount() override
    {
        cout << "Specific Debit Amount Logic for Bank Transfer" << endl;
    }

    void calculateFees() override
    {
        cout << "Specific Fee Calculation Logic for Bank Transfer. 0% Fees is applied" << endl;
    }

    void creditAmount() override
    {
        cout << "Specific Credit Amount Logic for Bank Transfer.Full amount is credited." << endl;
    }
};

class MerchantPayment : public PaymentFlow
{
    void validateRequest() override
    {
        cout << "Specific Validation Logic for Merchant Transfer" << endl;
    }

    void debitAmount() override
    {
        cout << "Specific Debit Amount Logic for Merchant Transfer" << endl;
    }

    void calculateFees() override
    {
        cout << "Specific Fee Calculation Logic for Merchant Transfer. 0% Fees is applied" << endl;
    }

    void creditAmount() override
    {
        cout << "Specific Credit Amount Logic for Merchant Transfer. Full amount is credited." << endl;
    }
};

int main()
{
    cout << "###### Template Method Design Pattern ######" << endl;

    // Bank Transfer
    cout << "Bank Transfer" << endl;
    PaymentFlow *bankTrasfer = new BankTransfer();
    bankTrasfer->sendMoney();
    bankTrasfer->logTransaction();

    // Merchant Payment
    cout << "Merchant Payment" << endl;
    PaymentFlow *merchantPayment = new BankTransfer();
    bankTrasfer->sendMoney();
    bankTrasfer->logTransaction();

    return 0;
}