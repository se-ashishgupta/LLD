#include <iostream>
#include <vector>
using namespace std;

// Open-Closed Principle: Software entities (classes, modules, functions, etc.) should be open for extension but closed for modification.

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
    vector<Product *> product;

public:
    void addToCart(Product *p)
    {
        this->product.push_back(p);
    }

    const vector<Product *> &getProducts() const
    {
        return product;
    }

    double calculateTotalPrice()
    {
        double total = 0;
        for (auto p : this->getProducts())
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

// Violation of Open-Closed Principle: If we want to add a new type of persistence (e.g., saving to a file), we would need to modify the Persistence class, which violates the Open-Closed Principle. Instead, we should create separate classes for each type of persistence that inherit from a common interface or abstract class, allowing us to extend functionality without modifying existing code.
class Persistence
{
private:
    ShoppingCart *cart;

public:
    Persistence(ShoppingCart *cart)
    {
        this->cart = cart;
    }

    void saveToSQL()
    {
        cout << "Shopping cart saved to SQL DB.." << endl;
    }

    void saveToMongo()
    {
        cout << "Shopping cart saved to Mongo DB.." << endl;
    }

    void saveToFile()
    {
        cout << "Shopping cart saved to File.." << endl;
    }
};

int main()
{

    Product *p1 = new Product("Macbook", 900000);
    Product *p2 = new Product("Keyboard", 20000);

    ShoppingCart *cart = new ShoppingCart();
    cart->addToCart(p1);
    cart->addToCart(p2);

    InvoiceGenerator *invoice = new InvoiceGenerator(cart);
    invoice->generateInvoice();

    Persistence *persistence = new Persistence(cart);

    persistence->saveToSQL();
    persistence->saveToMongo();
    persistence->saveToFile();

    return 0;
}