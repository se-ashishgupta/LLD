#include <iostream>
using namespace std;

// Observer Interface
class StockNotificationObserver
{
public:
    virtual void update() = 0;
    virtual string getNotificationMethod() = 0;
    virtual string getUserId() = 0;

    virtual ~StockNotificationObserver() {}
};

// Observable Interface
class StockAvailabilityObservable
{
public:
    virtual void addStockObservers(StockNotificationObserver *observer) = 0;
    virtual void removeStockObservers(StockNotificationObserver *observer) = 0;
    virtual void notifyStockObservers() = 0;
    virtual bool purchase(int quantity) = 0;
    virtual void restock(int quantity) = 0;

    virtual ~StockAvailabilityObservable() {}
};

// Concreate Observable
class IphoneProductObservable : public StockAvailabilityObservable
{
private:
    string productId;
    string productName;
    double price;

    vector<StockNotificationObserver *> stockObservers;
    int stockQuantity;

public:
    IphoneProductObservable(string id, string name, double p, int stock)
    {
        productId = id;
        productName = name;
        price = p;
        stockQuantity = stock;
    }

    void addStockObservers(StockNotificationObserver *observer) override
    {
        stockObservers.push_back(observer);
        cout << "[+] " << observer->getUserId() << " subscribed for notifcation on " << productName << endl;
    }

    void removeStockObservers(StockNotificationObserver *observer) override
    {
        stockObservers.erase(remove(stockObservers.begin(), stockObservers.end(), observer), stockObservers.end());
        cout << "[-] " << observer->getUserId()
             << " unsubscribed from " << productName << endl;
    }

    void notifyStockObservers() override
    {
        if (stockQuantity > 0 && !stockObservers.empty())
        {
            cout << "Notifying " << stockObservers.size() << " subscribers..." << endl;

            // Copy to avoid modifcation during iteration
            vector<StockNotificationObserver *> temp = stockObservers;

            for (auto observer : stockObservers)
            {
                observer->update();
            }
        }
    }

    bool purchase(int quantity) override
    {
        if (stockQuantity >= quantity)
        {
            stockQuantity -= quantity;
            cout << "Purchased success: " << quantity << " units of " << productName << " | Remaining stock: " << stockQuantity << endl;
            return true;
        }
        else
        {
            cout << "Purchased failed: " << productName << " is out of stock! | Available: " << stockQuantity << endl;
            return false;
        }
    }

    void restock(int quantity) override
    {
        bool wasOutOfStock = (stockQuantity == 0);

        stockQuantity += quantity;

        cout << "Restocked: " << productName << " | Added: " << quantity << " | Current stock: " << stockQuantity << endl;

        if (wasOutOfStock && stockQuantity > 0)
        {
            notifyStockObservers();
        }
    }

    // Getters

    string getProductId()
    {
        return productId;
    }

    string getProductName()
    {
        return productName;
    }

    double getPrice()
    {
        return price;
    }

    int getStockQuantoty()
    {
        return stockQuantity;
    }
};

// Email Observer
class EmailNotificationObserver : public StockNotificationObserver
{

private:
    string userId;
    string email;

public:
    EmailNotificationObserver(string id, string email) : userId(id), email(email) {}

    void update() override
    {
        sendMail();
    }

    void sendMail()
    {
        cout << "Email send to: " << email << " - Product is back in the stock" << endl;
    }

    string getNotificationMethod() override
    {
        return "EMAIL";
    }

    string getUserId() override
    {
        return userId;
    }
};

// Push Notiffication Observer

class PushNotifcationObserver : public StockNotificationObserver
{
private:
    string userId;
    string deviceToken;

public:
    PushNotifcationObserver(string id, string dToken) : userId(id), deviceToken(dToken) {}

    void update() override
    {
        sendPushNotification();
    }

    void sendPushNotification()
    {
        cout << "Push Notification send to: " << deviceToken << " - Product is back in the stock" << endl;
    }

    string getNotificationMethod() override
    {
        return "Push Notification";
    }

    string getUserId() override
    {
        return userId;
    }
};

int main()
{
    cout << "===== E-commerce Stock Notification Demo =====\n";

    StockAvailabilityObservable *iphone = new IphoneProductObservable("ip15", "Iphone 15", 1250, 10);

    // Observers
    StockNotificationObserver *john = new PushNotifcationObserver("john123", "DeviceP1");
    auto ashish = new PushNotifcationObserver("ashish123", "DeviceP2");
    StockNotificationObserver *jane = new EmailNotificationObserver("jane123", "jane@gmail.com");
    auto amit = new EmailNotificationObserver("amit123", "amit@gmail.com");

    // Sell all stock
    iphone->purchase(10);

    bool success = iphone->purchase(1);
    if (!success)
    {
        iphone->addStockObservers(john);
        iphone->addStockObservers(ashish);
        iphone->addStockObservers(jane);
        iphone->addStockObservers(amit);
    }

    // Restock
    iphone->restock(20);

    iphone->purchase(1);
    iphone->purchase(1);

    iphone->removeStockObservers(jane);
    iphone->removeStockObservers(john);

    iphone->purchase(18);
    iphone->restock(10);

    iphone->purchase(1);
    iphone->purchase(1);

    iphone->removeStockObservers(ashish);
    iphone->removeStockObservers(amit);

    // Cleanup (important in raw pointer version)
    delete john;
    delete ashish;
    delete jane;
    delete amit;

    return 0;
}