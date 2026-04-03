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
};

class InvoiceGenerator
{
private:
    ShoppingCart *cart;

public:
    InvoiceGenerator(ShoppingCart *cart)
    {
        this->cart = cart;
    }

    void generateInvoice()
    {
        cout << "Invoice:" << endl;
        for (auto p : cart->getProducts())
        {
            cout << p->name << ": $" << p->price << endl;
        }
        cout << "Total: $" << cart->calculateTotalPrice() << endl;
    }
};

class DatabaseManager
{
private:
    ShoppingCart *cart;

public:
    DatabaseManager(ShoppingCart *cart)
    {
        this->cart = cart;
    }

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

    InvoiceGenerator invoiceGen(&cart);
    invoiceGen.generateInvoice();

    DatabaseManager dbManager(&cart);
    dbManager.saveToDatabase();

    delete p1;
    delete p2;

    return 0;
}