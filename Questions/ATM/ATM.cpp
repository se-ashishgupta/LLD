#include <iostream>
#include <string>
using namespace std;

// ─────────────────────────────────────────────
// Forward declarations
// ─────────────────────────────────────────────
class ATM;
class IdleState;
class HasCardState;
class SelectOperationState;
class CheckBalanceState;
class CashWithdrawalState;

// ─────────────────────────────────────────────
// UserBankAccount
// ─────────────────────────────────────────────
class UserBankAccount
{
private:
    double balance;

public:
    UserBankAccount() : balance(0.0) {}

    void withdrawalBalance(double amount)
    {
        balance -= amount;
    }

    double getBalance() // FIX: was int, losing decimal precision
    {
        return balance;
    }

    void setBalance(double b)
    {
        balance = b;
    }
};

// ─────────────────────────────────────────────
// Card
// ─────────────────────────────────────────────
class Card
{
public:
    static const int PIN_NUMBER = 112211;
    int cardNumber;
    int cvv;
    string expiryDate;
    string holderName;
    UserBankAccount *bankAccount;

    Card() : cardNumber(0), cvv(0), bankAccount(nullptr) {}

    bool isCorrectPINEntered(int pin)
    {
        return pin == PIN_NUMBER;
    }

    double getBankBalance() // FIX: was int
    {
        return bankAccount->getBalance();
    }

    void deductBankBalance(int amount)
    {
        bankAccount->withdrawalBalance(amount);
    }

    void setBankAccount(UserBankAccount *ba)
    {
        bankAccount = ba;
    }
};

// ─────────────────────────────────────────────
// TransactionType
// ─────────────────────────────────────────────
enum class TransactionType
{
    CASH_WITHDRAWAL,
    BALANCE_CHECK,
};

// ─────────────────────────────────────────────
// ATMState – base class with virtual methods
// ─────────────────────────────────────────────
class ATMState
{
public:
    virtual void insertCard(ATM *atm, Card *card)
    {
        cout << "OOPS!! Something went wrong" << endl;
    }
    virtual void authenticatePin(ATM *atm, Card *card, int pin)
    {
        cout << "OOPS!! Something went wrong" << endl;
    }
    virtual void selectOperation(ATM *atm, Card *card, TransactionType txnType)
    {
        cout << "OOPS!! Something went wrong" << endl;
    }
    virtual void cashWithdrawal(ATM *atm, Card *card, int withdrawAmount)
    {
        cout << "OOPS!! Something went wrong" << endl;
    }
    virtual void displayBalance(ATM *atm, Card *card)
    {
        cout << "OOPS!! Something went wrong" << endl;
    }
    virtual void returnCard()
    {
        cout << "OOPS!! Something went wrong" << endl;
    }
    virtual void exit(ATM *atm)
    {
        cout << "OOPS!! Something went wrong" << endl;
    }
    virtual ~ATMState() = default;
};

// ─────────────────────────────────────────────
// ATM  (defined before concrete states so the
//       states can call atm->setCurrentATMState)
// ─────────────────────────────────────────────
class ATM
{
private:
    static ATM atmObject; // eager singleton

    ATMState *currentATMState;
    int noOfTwoThousandNotes;
    int noOfFiveHundredNotes;
    int noOfOneHundredNotes;
    int atmBalance;

    ATM() : currentATMState(nullptr),
            noOfTwoThousandNotes(0),
            noOfFiveHundredNotes(0),
            noOfOneHundredNotes(0),
            atmBalance(0) {}

public:
    ATM(const ATM &) = delete;
    ATM &operator=(const ATM &) = delete;

    static ATM &getATMObject() { return atmObject; }

    ATMState *getCurrentATMState() { return currentATMState; }
    void setCurrentATMState(ATMState *s) { currentATMState = s; }

    int getAtmBalance() { return atmBalance; }
    int getNoOfTwoThousandNotes() { return noOfTwoThousandNotes; }
    int getNoOfFiveHundredNotes() { return noOfFiveHundredNotes; }
    int getNoOfOneHundredNotes() { return noOfOneHundredNotes; }

    void setAtmBalance(int balance, int twoK, int fiveH, int oneH)
    {
        atmBalance = balance;
        noOfTwoThousandNotes = twoK;
        noOfFiveHundredNotes = fiveH;
        noOfOneHundredNotes = oneH;
    }

    void deductATMBalance(int amount) { atmBalance -= amount; }
    void deductTwoThousandNotes(int n) { noOfTwoThousandNotes -= n; }
    void deductFiveHundredNotes(int n) { noOfFiveHundredNotes -= n; }
    void deductOneHundredNotes(int n) { noOfOneHundredNotes -= n; }

    void printCurrentATMStatus()
    {
        cout << "Balance: " << atmBalance << endl;
        cout << "2k Notes: " << noOfTwoThousandNotes << endl;
        cout << "500 Notes: " << noOfFiveHundredNotes << endl;
        cout << "100 Notes: " << noOfOneHundredNotes << endl;
    }
};

// Out-of-class definition for static singleton
ATM ATM::atmObject;

// ─────────────────────────────────────────────
// Chain-of-Responsibility: note dispensers
// ─────────────────────────────────────────────
class CashWithdrawProcessor
{
protected:
    CashWithdrawProcessor *nextProcessor;

public:
    CashWithdrawProcessor(CashWithdrawProcessor *next)
        : nextProcessor(next) {}

    virtual void withdraw(ATM *atm, int remainingAmount)
    {
        if (nextProcessor != nullptr)
            nextProcessor->withdraw(atm, remainingAmount);
    }

    virtual ~CashWithdrawProcessor()
    {
        delete nextProcessor; // recursive cleanup
    }
};

class TwoThousandWithdrawProcessor : public CashWithdrawProcessor
{
public:
    TwoThousandWithdrawProcessor(CashWithdrawProcessor *next)
        : CashWithdrawProcessor(next) {}

    void withdraw(ATM *atm, int remainingAmount) override
    {
        int required = remainingAmount / 2000;
        int balance = remainingAmount % 2000;

        // FIX: original used getNoOfFiveHundredNotes/deductFiveHundredNotes here
        int available = atm->getNoOfTwoThousandNotes();
        if (required <= available)
        {
            atm->deductTwoThousandNotes(required);
            cout << "Dispensing " << required << " x Rs.2000 note(s)" << endl;
        }
        else
        {
            atm->deductTwoThousandNotes(available);
            cout << "Dispensing " << available << " x Rs.2000 note(s)" << endl;
            balance += (required - available) * 2000;
        }

        if (balance != 0)
            CashWithdrawProcessor::withdraw(atm, balance);
    }
};

class FiveHundredWithdrawProcessor : public CashWithdrawProcessor
{
public:
    FiveHundredWithdrawProcessor(CashWithdrawProcessor *next)
        : CashWithdrawProcessor(next) {}

    void withdraw(ATM *atm, int remainingAmount) override
    {
        int required = remainingAmount / 500;
        int balance = remainingAmount % 500;

        int available = atm->getNoOfFiveHundredNotes();
        if (required <= available)
        {
            atm->deductFiveHundredNotes(required);
            cout << "Dispensing " << required << " x Rs.500 note(s)" << endl;
        }
        else
        {
            atm->deductFiveHundredNotes(available);
            cout << "Dispensing " << available << " x Rs.500 note(s)" << endl;
            balance += (required - available) * 500;
        }

        if (balance != 0)
            CashWithdrawProcessor::withdraw(atm, balance);
    }
};

class OneHundredWithdrawProcessor : public CashWithdrawProcessor
{
public:
    OneHundredWithdrawProcessor(CashWithdrawProcessor *next)
        : CashWithdrawProcessor(next) {}

    void withdraw(ATM *atm, int remainingAmount) override
    {
        int required = remainingAmount / 100;
        int balance = remainingAmount % 100;

        // FIX: original used Five-hundred getters/deductors throughout
        int available = atm->getNoOfOneHundredNotes();
        if (required <= available)
        {
            atm->deductOneHundredNotes(required);
            cout << "Dispensing " << required << " x Rs.100 note(s)" << endl;
        }
        else
        {
            atm->deductOneHundredNotes(available);
            cout << "Dispensing " << available << " x Rs.100 note(s)" << endl;
            balance += (required - available) * 100;
        }

        if (balance != 0)
            cout << "Cannot dispense exact change with available notes." << endl;
    }
};

// ─────────────────────────────────────────────
// Concrete ATM States
// (all declared after ATM so they can reference it fully)
// ─────────────────────────────────────────────

// --- IdleState ---
class IdleState : public ATMState
{
public:
    void insertCard(ATM *atm, Card *card) override; // body below (needs HasCardState)
};

// --- HasCardState ---
class HasCardState : public ATMState
{
public:
    HasCardState()
    {
        cout << "Enter your card PIN number" << endl;
    }

    void authenticatePin(ATM *atm, Card *card, int pin) override; // body below

    void returnCard() override
    {
        cout << "Please collect your card" << endl;
    }

    void exit(ATM *atm) override
    {
        returnCard();
        atm->setCurrentATMState(new IdleState());
        cout << "Exit happened" << endl;
    }
};

// --- SelectOperationState ---
class SelectOperationState : public ATMState
{
public:
    SelectOperationState()
    {
        showOperations();
    }

    void selectOperation(ATM *atm, Card *card, TransactionType txnType) override; // body below

    void returnCard() override
    {
        cout << "Please collect your card" << endl;
    }

    void exit(ATM *atm) override
    {
        returnCard();
        atm->setCurrentATMState(new IdleState());
        cout << "Exit happened" << endl;
    }

    void showOperations()
    {
        cout << "Please select an operation:" << endl;
        cout << "  1. CASH_WITHDRAWAL" << endl;
        cout << "  2. BALANCE_CHECK" << endl;
    }
};

// --- CheckBalanceState ---
class CheckBalanceState : public ATMState
{
public:
    void displayBalance(ATM *atm, Card *card) override
    {
        cout << "Your balance is: " << card->getBankBalance() << endl;
        exit(atm);
    }

    void returnCard() override
    {
        cout << "Please collect your card" << endl;
    }

    void exit(ATM *atm) override
    {
        returnCard();
        atm->setCurrentATMState(new IdleState());
        cout << "Exit happened" << endl;
    }
};

// --- CashWithdrawalState ---
class CashWithdrawalState : public ATMState
{
public:
    CashWithdrawalState()
    {
        cout << "Please enter withdrawal amount" << endl;
    }

    void cashWithdrawal(ATM *atm, Card *card, int amount) override
    {
        if (atm->getAtmBalance() < amount)
        {
            cout << "Insufficient funds in ATM machine" << endl;
        }
        else if (card->getBankBalance() < amount)
        {
            cout << "Insufficient funds in your bank account" << endl;
        }
        else
        {
            card->deductBankBalance(amount);
            atm->deductATMBalance(amount);

            // Chain: 2000 -> 500 -> 100
            CashWithdrawProcessor *chain =
                new TwoThousandWithdrawProcessor(
                    new FiveHundredWithdrawProcessor(
                        new OneHundredWithdrawProcessor(nullptr)));

            chain->withdraw(atm, amount);
            delete chain;

            cout << "Please collect your cash." << endl;
        }
        exit(atm);
    }

    void returnCard() override
    {
        cout << "Please collect your card" << endl;
    }

    void exit(ATM *atm) override
    {
        returnCard();
        atm->setCurrentATMState(new IdleState());
        cout << "Exit happened" << endl;
    }
};

// ─────────────────────────────────────────────
// Method bodies that needed forward declarations
// ─────────────────────────────────────────────
void IdleState::insertCard(ATM *atm, Card *card)
{
    cout << "Card is inserted" << endl;
    atm->setCurrentATMState(new HasCardState());
}

void HasCardState::authenticatePin(ATM *atm, Card *card, int pin)
{
    if (card->isCorrectPINEntered(pin))
    {
        cout << "PIN verified." << endl;
        atm->setCurrentATMState(new SelectOperationState());
    }
    else
    {
        cout << "Invalid PIN. Try again." << endl;
    }
}

void SelectOperationState::selectOperation(ATM *atm, Card *card, TransactionType txnType)
{
    switch (txnType)
    {
    case TransactionType::CASH_WITHDRAWAL:
        atm->setCurrentATMState(new CashWithdrawalState());
        break;
    case TransactionType::BALANCE_CHECK:
        atm->setCurrentATMState(new CheckBalanceState());
        break;
    default:
        cout << "Invalid option" << endl;
        exit(atm);
    }
}

// ─────────────────────────────────────────────
// User
// ─────────────────────────────────────────────
class User
{
private:
    Card *card;

public:
    User() : card(nullptr) {}

    Card *getCard() { return card; }
    void setCard(Card *c) { card = c; }
};

// ─────────────────────────────────────────────
// ATMRoom
// ─────────────────────────────────────────────
class ATMRoom
{
public: // FIX: public so main() can access atm and user
    ATM &atm;
    User *user;

    ATMRoom() : atm(ATM::getATMObject()), user(nullptr) {}

    void initialize()
    {
        // ATM loaded with: 1×2000 + 2×500 + 5×100 = 3500
        atm.setAtmBalance(3500, 1, 2, 5);

        // FIX: set initial state (was never set – would crash on nullptr)
        atm.setCurrentATMState(new IdleState());

        user = createUser();
    }

    User *createUser()
    {
        User *u = new User();
        u->setCard(createCard());
        return u;
    }

    Card *createCard()
    {
        Card *c = new Card();
        c->setBankAccount(createBankAccount());
        return c;
    }

    UserBankAccount *createBankAccount()
    {
        UserBankAccount *ba = new UserBankAccount();
        ba->setBalance(3000);
        return ba;
    }
};

// ─────────────────────────────────────────────
// main
// ─────────────────────────────────────────────
int main()
{
    // FIX: was "ATMRoom *atmRoom;" — uninitialised pointer, never allocated.
    //      Also mixed -> and . access on it. Use a value object instead.
    ATMRoom atmRoom;
    atmRoom.initialize();

    cout << "\n--- Initial ATM Status ---" << endl;
    atmRoom.atm.printCurrentATMStatus();
    cout << endl;

    atmRoom.atm.getCurrentATMState()->insertCard(
        &atmRoom.atm,
        atmRoom.user->getCard());

    atmRoom.atm.getCurrentATMState()->authenticatePin(
        &atmRoom.atm,
        atmRoom.user->getCard(),
        112211);

    atmRoom.atm.getCurrentATMState()->selectOperation(
        &atmRoom.atm,
        atmRoom.user->getCard(),
        TransactionType::CASH_WITHDRAWAL);

    atmRoom.atm.getCurrentATMState()->cashWithdrawal(
        &atmRoom.atm,
        atmRoom.user->getCard(),
        2700);

    cout << "\n--- Final ATM Status ---" << endl;
    atmRoom.atm.printCurrentATMStatus();

    return 0;
}