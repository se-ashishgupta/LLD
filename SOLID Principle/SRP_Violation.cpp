#include <iostream>
using namespace std;

class Product
{
public:
    string name;
    int price;

    Product(string name, int price)
    {
        this->name = name;
        this->price = price;
    }
};

// Single Responsibility Principle: A class should have only one reason to change. and should have only one responsibility.
// Single responsibility principle is violated in the below class as it has multiple responsibilities like calculating total price, generating invoice and saving to database. These responsibilities should be separated into different classes to adhere to the Single Responsibility Principle.

// Violation of Single Responsibility Principle
class ShoppingCart
{
private:
    vector<Product *> products;

public:
    void addProduct(Product *p)
    {
        products.push_back(p);
    }

    const vector<Product *> &getProducts() const
    {
        return products;
    }

    // 1. Calculate total price of products in the cart
    double calculateTotalPrice()
    {
        double total = 0;
        for (auto p : products)
        {
            total += p->price;
        }
        return total;
    }

    // 2. Violation: Generate invoice for the products in the cart (Should be in a separate class)
    void generateInvoice()
    {
        cout << "Invoice:" << endl;
        for (auto p : products)
        {
            cout << p->name << ": $" << p->price << endl;
        }
        cout << "Total: $" << calculateTotalPrice() << endl;
    }

    // 3. Violation: Save cart details to a file (Should be in a separate class)
    void saveToDatabase()
    {
        // Code to save cart details to a database
        cout << "Saving cart details to database..." << endl;
    }
};

int main()
{
    Product *p1 = new Product("Laptop", 1000);
    Product *p2 = new Product("Phone", 500);

    ShoppingCart cart;
    cart.addProduct(p1);
    cart.addProduct(p2);

    cart.generateInvoice();
    cart.saveToDatabase();

    delete p1;
    delete p2;

    return 0;
}