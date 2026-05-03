#include <iostream>
#include <memory>
#include <algorithm>
using namespace std;

// Observer Interface
class StockNotificationObserver
{
public:
    virtual void update() = 0;
    virtual string getNotificationMethod() = 0;
    virtual string getUserId() = 0;

    virtual ~StockNotificationObserver() = default;
};

// Observable Interface
class StockAvailabilityObservable
{
public:
    virtual void addStockObservers(shared_ptr<StockNotificationObserver> observer) = 0;
    virtual void removeStockObservers(shared_ptr<StockNotificationObserver> observer) = 0;
    virtual void notifyStockObservers() = 0;
    virtual bool purchase(int quantity) = 0;
    virtual void restock(int quantity) = 0;

    virtual ~StockAvailabilityObservable() = default;
};

// Concreate Observable
class ProductObservable : public StockAvailabilityObservable
{
private:
    string productId;
    string productName;
    double price;

    //     💣 Interview Killer Line
    //         Say this :
    // “I used weak_ptr inside Observable to avoid cyclic dependency,
    //         since observers may also hold reference back in real systems.”

    vector<weak_ptr<StockNotificationObserver>> stockObservers;
    int stockQuantity;

public:
    ProductObservable(string id, string name, double p, int stock)
    {
        productId = id;
        productName = name;
        price = p;
        stockQuantity = stock;
    }

    void addStockObservers(shared_ptr<StockNotificationObserver> observer) override
    {
        stockObservers.push_back(observer);
        cout << "[+] " << observer->getUserId() << " subscribed for notifcation on " << productName << endl;
    }

    void removeStockObservers(shared_ptr<StockNotificationObserver> observer) override
    {
        stockObservers.erase(
            remove_if(stockObservers.begin(), stockObservers.end(),
                      [&](weak_ptr<StockNotificationObserver> &wp)
                      {
                          auto sp = wp.lock();
                          return !sp || sp == observer;
                      }),
            stockObservers.end());
        cout << "[-] " << observer->getUserId()
             << " unsubscribed from " << productName << endl;
    }

    void notifyStockObservers() override
    {
        if (stockQuantity > 0 && !stockObservers.empty())
        {
            cout << "Notifying " << stockObservers.size() << " subscribers..." << endl;

            // Copy to avoid modifcation during iteration
            vector<weak_ptr<StockNotificationObserver>> updatedList;

            for (auto &wp : stockObservers)
            {
                if (auto sp = wp.lock())
                { // still alive
                    sp->update();
                    updatedList.push_back(sp);
                }
            }

            stockObservers = std::move(updatedList);
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

    unordered_map<string, shared_ptr<StockAvailabilityObservable>> productCatalog;

    productCatalog["ip15"] = make_shared<ProductObservable>("ip15", "Iphone 15", 1250, 10);
    productCatalog["tshirt"] = make_shared<ProductObservable>("tshirt", "Tshirt", 250, 10);

    // Observers
    auto john = make_shared<PushNotifcationObserver>("john123", "DeviceP1");
    auto ashish = make_shared<PushNotifcationObserver>("ashish123", "DeviceP2");
    auto jane = make_shared<EmailNotificationObserver>("jane123", "jane@gmail.com");
    auto amit = make_shared<EmailNotificationObserver>("amit123", "amit@gmail.com");

    // Sell all stock
    auto iphone = productCatalog["tshirt"];
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

    // Cleanup (No need because of auto cleanup)

    return 0;
}