#include <iostream>

using namespace std;

// Complex subsystem classes

// Subsystem A: Inventory Service
class InventoryService
{
public:
    bool checkInventory(int orderId)
    {
        cout << "Checking inventory for order ID: " << orderId << endl;
        // Simulate inventory check
        return true; // Assume inventory is available
    }
};

// Subsystem B: Payment Service
class PaymentService
{
public:
    bool processPayment(int orderId, double amount)
    {
        cout << "Processing payment for order ID: " << orderId << ", Amount: $" << amount << endl;
        // Simulate payment processing
        return true; // Assume payment is successful
    }
};

// Subsystem C: Shipping Service
class ShippingService
{
public:
    void shipOrder(int orderId)
    {
        cout << "Shipping order ID: " << orderId << endl;
        // Simulate shipping process
    }
};

// Subsystem D: Notification Service
class NotificationService
{
public:
    void sendNotification(int orderId)
    {
        cout << "Sending notification for order ID: " << orderId << endl;
        // Simulate sending notification
    }
};

// Facade class
class OrderProcessingFacade
{
private:
    InventoryService inventoryService;
    PaymentService paymentService;
    ShippingService shippingService;
    NotificationService notificationService;

public:
    void processOrder(int orderId, double amount)
    {
        if (!inventoryService.checkInventory(orderId))
        {
            cout << "Inventory not available for order ID: " << orderId << endl;
            return;
        }

        if (!paymentService.processPayment(orderId, amount))
        {
            cout << "Payment failed for order ID: " << orderId << endl;
            return;
        }

        shippingService.shipOrder(orderId);
        notificationService.sendNotification(orderId);

        cout << "Order processing completed for order ID: " << orderId << endl;
    }
};

int main()
{
    cout << "===== Facade Design Pattern =====\n";

    int orderId = 12345;
    double amount = 250.75;

    // Process the order using the facade
    OrderProcessingFacade orderProcessing;
    orderProcessing.processOrder(orderId, amount);

    return 0;
}